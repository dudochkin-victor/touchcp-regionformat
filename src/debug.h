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
#ifndef DEBUG_H
#define DEBUG_H

#include <QtDebug>

#ifdef NO_COLOR
#define VT_GRAPHICS_MODE(code) ""
#else
#define VT_GRAPHICS_MODE(code) "\e\["#code"m"
#endif

#define VT_NORMAL           VT_GRAPHICS_MODE(0)
#define VT_TA_BOLD          VT_GRAPHICS_MODE(1)
#define VT_TA_UNDERSCORE    VT_GRAPHICS_MODE(4)
#define VT_TA_BLINK         VT_GRAPHICS_MODE(5)
#define VT_TA_REVERSE       VT_GRAPHICS_MODE(7)
#define VT_TA_CONCEALED     VT_GRAPHICS_MODE(8)

#define VT_BLACK         VT_GRAPHICS_MODE(30)
#define VT_RED           VT_GRAPHICS_MODE(31)
#define VT_GREEN         VT_GRAPHICS_MODE(32)
#define VT_YELLOW        VT_GRAPHICS_MODE(33)
#define VT_BLUE          VT_GRAPHICS_MODE(34)
#define VT_MAGENTA       VT_GRAPHICS_MODE(35)
#define VT_CYAN          VT_GRAPHICS_MODE(36)
#define VT_WHITE         VT_GRAPHICS_MODE(37)

#define VT_BG_BLACK         VT_GRAPHICS_MODE(40)
#define VT_BG_RED           VT_GRAPHICS_MODE(41)
#define VT_BG_GREEN         VT_GRAPHICS_MODE(42)
#define VT_BG_YELLOW        VT_GRAPHICS_MODE(43)
#define VT_BG_BLUE          VT_GRAPHICS_MODE(44)
#define VT_BG_MAGENTA       VT_GRAPHICS_MODE(45)
#define VT_BG_CYAN          VT_GRAPHICS_MODE(46)
#define VT_BG_WHITE         VT_GRAPHICS_MODE(47)

void initTermHandler();
void runtimeBacktrace();
void msgHandler(QtMsgType type, const char *msg);

#endif

