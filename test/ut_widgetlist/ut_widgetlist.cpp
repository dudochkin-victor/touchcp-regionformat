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
#include "mabstractlayoutpolicy-fake.h" 
#include "mlayout-fake.h" 
#include "mgridlayoutpolicy-fake.h" 
#include "mlinearlayoutpolicy-fake.h" 
#include "widgetlist.h" 

void MLinearLayoutPolicy::setSpacing(qreal)
{

}

class Ut_WidgetList : public QObject
{
    public:
        Q_OBJECT;

    private slots:
        void initTestCase();
        void cleanupTestCase();
        void init();
        void cleanup();

        void testAddRemove();

    private:
        WidgetList *m_widgetlist;
};

void Ut_WidgetList::initTestCase()
{
    /* Simple crash test.... */
    m_widgetlist = new WidgetList();
    QVERIFY(m_widgetlist);
}

void Ut_WidgetList::cleanupTestCase()
{
    delete m_widgetlist;
}


void Ut_WidgetList::cleanup()
{
}

void Ut_WidgetList::init()
{
}

void Ut_WidgetList::testAddRemove()
{
    MWidget mw;
    QCOMPARE(m_widgetlist->m_PortraitLayoutPolicy->count(), 0);
    QCOMPARE(m_widgetlist->m_LandscapeLayoutPolicy->count(), 0);

    m_widgetlist->addWidget(&mw);
    QCOMPARE(m_widgetlist->m_PortraitLayoutPolicy->count(), 1);
    QCOMPARE(m_widgetlist->m_LandscapeLayoutPolicy->count(), 1);

    m_widgetlist->removeWidget(&mw);
    QCOMPARE(m_widgetlist->m_PortraitLayoutPolicy->count(), 0);
    QCOMPARE(m_widgetlist->m_LandscapeLayoutPolicy->count(), 0);
}

QTEST_APPLESS_MAIN(Ut_WidgetList);

#include ".moc/ut_widgetlist.moc"
