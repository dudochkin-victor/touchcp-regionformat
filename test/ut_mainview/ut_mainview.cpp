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
#include <MComboBox>
#include "mabstractlayoutpolicy-fake.h" 
#include "mlayout-fake.h" 
#include "mlinearlayoutpolicy-fake.h" 
#include "mcontentitem-fake.h" 
#include "mcontainer-fake.h" 
#include "mcombobox-fake.h" 
#include "mbasiclistitem-fake.h" 
#include "debug.h" 
#include "mainview.h" 
#include "businesslogic.h" 
#include "widgetlist.h" 
#include "drilldownitem.h" 
#include "drilldownitem-stub.h" 
#include "translation.h" 
#include "businesslogic-stub.h" 
#include "widgetlist-stub.h" 
#include "infoitem-stub.h" 

namespace TextId {
    const char *AppletTitle = "AppletTitle";
    const char *RegionViewTitle = "RegionViewTitle";
    const char *NumberTitle = "NumberTitle";
    const char *CurrencyTitle = "NumberTitle";
    const char *TimeTitle = "NumberTitle";
    const char *SelectNumber = "NumberTitle";
    const char *SelectRegion = "NumberTitle";
    const char *DateTitle = "NumberTitle";
};


class Ut_MainView : public QObject
{
    public:
        Q_OBJECT;

    private slots:
        void initTestCase();
        void cleanupTestCase();
        void init();
        void cleanup();

        void testPagePans();
        void testTitle();
        void testSlots();

    private:
        MainView *m_mview;
};

void Ut_MainView::initTestCase()
{
    m_mview = new MainView();
    QVERIFY(m_mview);
}

void Ut_MainView::cleanupTestCase()
{
    delete m_mview;
}


void Ut_MainView::cleanup()
{
}

void Ut_MainView::init()
{
}

void Ut_MainView::testPagePans()
{
    QCOMPARE(m_mview->pagePans(), false);
}

void Ut_MainView::testTitle()
{
    QCOMPARE(m_mview->title(), qtTrId("AppletTitle"));
}

void Ut_MainView::testSlots()
{
    /* Currently these are only crash tests.... of course, if some of it will be
     * a little bit more complicated, more tests should be added */
    m_mview->regionChangedSlot();
    m_mview->settingsChangedSlot();
    m_mview->lcTimeChangedSlot();
    m_mview->lcCollateChangedSlot();
    m_mview->lcNumericChangedSlot();
    m_mview->lcMonetaryChangedSlot();
    m_mview->regionCItemClickedSlot();
}

QTEST_APPLESS_MAIN(Ut_MainView);

#include ".moc/ut_mainview.moc"
