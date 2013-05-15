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
#include "mainview.h" 
#include <dcpbrief.h>
#include "applet.h" 
#include "regionview.h" 
#include "regionview-stub.h" 
#include "mainview-stub.h" 
#include "brief-stub.h" 
#include "brief.h" 
#include "translation.h" 
#include "viewid.h"

bool MTheme::loadCSS (const QString &, InsertMode)
{
    return true;
}

namespace TextId {
    const char *AppletTitle = "AppletTitle";
    const char *RegionViewTitle = "RegionViewTitle";
};


class Ut_Applet : public QObject
{
    public:
        Q_OBJECT;

    private slots:
        void initTestCase();
        void cleanupTestCase();
        void init();
        void cleanup();

        void testInit();
        void testConstructWidgetTitle();
        void testViewMenuItems();
        void testConstructBrief();
        void testPartId();

    private:
        Applet *m_applet;
};

void Ut_Applet::initTestCase()
{
    m_applet = new Applet();
    QVERIFY(m_applet);
}

void Ut_Applet::cleanupTestCase()
{
    delete m_applet;
}


void Ut_Applet::cleanup()
{
}

void Ut_Applet::init()
{
}

void Ut_Applet::testInit()
{
    QVERIFY(m_applet);
    /* Currently it is only a crash test.... */
    m_applet->init();
}

void Ut_Applet::testConstructWidgetTitle()
{
    /* Check whether it creates the right widget */
    DcpWidget *dcpWidget = m_applet->constructWidget(View::Region);
    QVERIFY(qobject_cast<RegionView*>(dcpWidget));
    QCOMPARE(m_applet->m_LastConstructedView, View::Region);
    QCOMPARE(m_applet->title(), _(RegionViewTitle));
    delete dcpWidget;

    dcpWidget = m_applet->constructWidget(View::Main);
    QVERIFY(qobject_cast<MainView*>(dcpWidget));
    QCOMPARE(m_applet->m_LastConstructedView, View::Main);
    QCOMPARE(m_applet->title(), _(AppletTitle));
    delete dcpWidget;
}


void Ut_Applet::testViewMenuItems()
{
    /* Only a basic test */
    QVERIFY(m_applet->viewMenuItems().isEmpty());
}

void Ut_Applet::testConstructBrief()
{
    QVERIFY(qobject_cast<Brief*>(m_applet->constructBrief(2)));
}

void Ut_Applet::testPartId()
{
    QCOMPARE(m_applet->partID("Main"), int(View::Main));
    QCOMPARE(m_applet->partID("ABCD"), int(View::Main));
    QCOMPARE(m_applet->partID("Region"), int(View::Region));
}
QTEST_APPLESS_MAIN(Ut_Applet);

#include ".moc/ut_applet.moc"
