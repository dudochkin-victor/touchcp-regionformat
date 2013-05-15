/***************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Karoliina T. Salminen <karoliina.t.salminen@nokia.com>
**
** This file is part of duicontrolpanel-regionformatapplet.
**
**
** This program is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation
** and appearing in the file LICENSE.LGPL included in the packaging
** of this file.
**
****************************************************************************/
/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */
#if 0
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <signal.h>
#include <execinfo.h>
#include <cxxabi.h>

#include "debug.h"

#define BACKTRACE_SIZE 64

void _nothing(){}

void msgHandler(QtMsgType type, const char *msg)
{
    switch (type) {
        case QtDebugMsg:
            fprintf(stderr, "QDEBUG %s\n", msg);
            break;

        case QtWarningMsg:
            fprintf(stderr, "%sWARNING%s %s\n",
                    VT_YELLOW VT_TA_BOLD, VT_NORMAL, msg);
            break;

        case QtCriticalMsg:
            fprintf(stderr, "%sCRITICAL%s %s\n",
                    VT_RED VT_TA_BOLD, VT_NORMAL, msg);
            break;

        case QtFatalMsg:
            fprintf(stderr, "%sFATAL%s %s\n",
                    VT_RED VT_TA_UNDERSCORE VT_TA_BOLD, VT_NORMAL, msg);
            fflush(stderr);
            abort();
    }

    fflush (stderr);
}

const char* demangle(const char* symbol) {
        size_t size;
    int status;
    char* result;
    static char temp[4096];

    if(sscanf(symbol, "%*[^'(']%*[^'_']%4095[^')''+']", temp) == 1)
        if(NULL != (result = abi::__cxa_demangle(temp, NULL, &size, &status)))
            return result;

    return symbol;
}

void runtimeBacktrace()
{
    void* addresses[BACKTRACE_SIZE];
    size_t size;
    size = backtrace(addresses, BACKTRACE_SIZE);
    char** symbols = backtrace_symbols(addresses, size);
    size_t i;
	fprintf(stderr, "--- Start Backtrace ---\n");
    for (i = 0; i < size; ++i)
        fprintf(stderr, "%03u %s\n", i, demangle(symbols[i]));
	fprintf(stderr, "---- End Backtrace ----\n");
    free(symbols);
}

void termHandler(int signum)
{
	switch (signum) {
		case SIGILL:
		case SIGSEGV:
		case SIGBUS:
		case SIGABRT:
		case SIGFPE:
			break;
		default:
			raise(signum);
			exit(1);
			break;
	}

    void runtimeBacktrace();
	fprintf(stderr, "Terminating because of signal %d\n", signum);
	exit(1);
}

void initTermHandler()
{
	fprintf(stderr, "Termination handler set up\n");
	signal(SIGILL, termHandler);
	signal(SIGSEGV, termHandler);
	signal(SIGBUS, termHandler);
	signal(SIGABRT, termHandler);
	signal(SIGFPE, termHandler);
}

#ifdef RUNTIME_BACKTRACE

#ifndef APP_NAME
#error Please define APP_NAME on command line to be used as prefix for function call debug messages.
#endif

extern "C" {
    void __cyg_profile_func_enter (void *this_fn, void *call_site) __attribute__ ((no_instrument_function));
    void __cyg_profile_func_exit (void *this_fn, void *call_site) __attribute__ ((no_instrument_function));
    void pushRunTime(long int t) __attribute__ ((no_instrument_function));
    long int popRunTime() __attribute__ ((no_instrument_function));
};

const char* functionName(void *functionPtr)
{
    char** symbols = backtrace_symbols(&functionPtr, 1);
    const char* ret = demangle(symbols[0]);
    free(symbols);
    return ret;
}

struct runTime {
    clock_t time;
    int callId;
    struct runTime *prev;
};

static struct runTime *runTimeStack = NULL;
static int level = 0;
static int callCounter = 0;

void pushRunTime(clock_t t, int callId)
{
    struct runTime *rt = (struct runTime*)malloc(sizeof(struct runTime));
    rt->time = t;
    rt->callId = callId;
    if(runTimeStack){
        rt->prev = runTimeStack;
        runTimeStack = rt;
    } else {
        rt->prev = NULL;
        runTimeStack = rt;
    }
}

clock_t popRunTime(int &callId)
{
    if(runTimeStack){
        struct runTime *rt = runTimeStack;
        runTimeStack = rt->prev;
        int t = rt->time;
        callId = rt->callId;
        free(rt);
        return t;
    }
    return -1;
}

void __cyg_profile_func_enter (void *this_fn, void *call_site)
{
    Q_UNUSED(call_site);
    char timeStr[10];

    level++;
    callCounter++;

    time_t t = time(NULL);
    strftime(timeStr, 10, "%H:%M:%S", localtime(&t));

    pushRunTime(clock(), callCounter);

    fprintf(stderr, "%s%16s%s %s%10s%s %5d %3d %s",
            VT_YELLOW, APP_NAME, VT_NORMAL,
            VT_BLUE, timeStr, VT_NORMAL,
            callCounter, level,
            functionName(this_fn));
    fprintf(stderr, "\n");

    fflush (stderr);
}

void __cyg_profile_func_exit (void *this_fn, void *call_site)
{
    Q_UNUSED(call_site);

    int callId;
    double d = clock() - popRunTime(callId);
    d /= CLOCKS_PER_SEC;
    fprintf(stderr, "%s%16s%s %s%9.3fs%s %5d %3d %s",
            VT_YELLOW, APP_NAME, VT_NORMAL,
            VT_MAGENTA, d, VT_NORMAL,
            callId, level,
            functionName(this_fn));
    fprintf(stderr, "\n");

    level--;

    fflush (stderr);
}

#endif
#endif
