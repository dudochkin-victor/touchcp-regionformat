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

#include <QtTest/QtTest>
#include <QObject>
#include "debug.h" 
#include <dcpbrief.h>
#include "brief.h" 
#include "translation.h" 
#include "mgconfitem-fake.h"
#include "gconfitemprivate-fake.h"
#include "businesslogic-stub.h" 

namespace TextId {
    const char *BriefTitle = "BriefTitle";
};


class Ut_Brief : public QObject
{
    public:
        Q_OBJECT;

    private slots:
        void initTestCase();
        void cleanupTestCase();
        void init();
        void cleanup();
        void testTexts();

    private:
        Brief *m_brief;
};

void Ut_Brief::initTestCase()
{
    m_brief = new Brief();
    QVERIFY(m_brief);
}

void Ut_Brief::cleanupTestCase()
{
    delete m_brief;
}


void Ut_Brief::cleanup()
{
}

void Ut_Brief::init()
{
}

void Ut_Brief::testTexts()
{
    BlogicStub->stubReset ();
    BlogicStub->stubSetReturnValue<QString> (
        "getRegionName", "CurrentText");
    QCOMPARE(m_brief->titleText(), _(BriefTitle));
    QCOMPARE(m_brief->valueText(), QString("CurrentText"));
}

QTEST_APPLESS_MAIN(Ut_Brief);

#include ".moc/ut_brief.moc"
