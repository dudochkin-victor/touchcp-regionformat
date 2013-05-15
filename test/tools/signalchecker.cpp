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

#include <QtTest/QtTest>
#include "signalchecker.h"

class SignalCounter {
    public:
        SignalCounter(QSignalSpy *spy):
            refSigCallCount(0),
            spy(spy)
        {
            QVERIFY(spy->isValid());
        }
        ~SignalCounter()
        {
            delete spy;
        }
        void increaseRefCount()
        {
            ++refSigCallCount;
        }
        int refCount()
        {
            return refSigCallCount;
        }
        void check()
        {
            QCOMPARE(spy->count(), refSigCallCount);
        }

    private:
        int refSigCallCount;
        QSignalSpy *spy;
};

SignalChecker::SignalChecker(QObject *obj): m_objToMonitor(obj)
{
}

SignalChecker::~SignalChecker()
{
    foreach(SignalCounter *sCounter, m_signalHasher)
    {
        delete sCounter;
    }
}
void SignalChecker::addSignalChecker(const char *signal)
{
    QSignalSpy *sSpy;
    SignalCounter *sCounter;

    sSpy = new QSignalSpy(m_objToMonitor, signal);
    sCounter = new SignalCounter(sSpy);

    m_signalHasher[signal] = sCounter;
}

void SignalChecker::check()
{
    foreach(SignalCounter *sCounter, m_signalHasher)
    {
        sCounter->check(); 
    }
}

void SignalChecker::increaseSigCounter(const char *signal)
{
    SignalCounter *sCounter = m_signalHasher[signal];
    sCounter->increaseRefCount();
}

