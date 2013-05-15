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
#include <QtGui/QGraphicsLayout>
#include <QtGui/QGraphicsGridLayout>
#include <QtGui/QSizePolicy>
#include <MWidgetController>
#include "drilldownitem.h" 

#include "mbasiclistitem-fake.h" 
#include "mlabel-fake.h" 
#include "mimagewidget-fake.h" 

void QGraphicsLayoutItem::setSizePolicy(QSizePolicy::Policy, QSizePolicy::Policy, QSizePolicy::ControlType)
{

}

static int addItemCalled = 0;
void QGraphicsGridLayout::addItem(QGraphicsLayoutItem *, int, int, int, int, Qt::Alignment)
{
    addItemCalled++;
}

class Ut_DrillDownItem : public QObject
{
    public:
        Q_OBJECT;

    private slots:
        void initTestCase();
        void cleanupTestCase();
        void init();
        void cleanup();

        void testCreateLayout();

};

void Ut_DrillDownItem::initTestCase()
{
}

void Ut_DrillDownItem::cleanupTestCase()
{
}


void Ut_DrillDownItem::cleanup()
{
}

void Ut_DrillDownItem::init()
{
}

void Ut_DrillDownItem::testCreateLayout()
{
    DrillDownItem *item = new DrillDownItem();
    Q_ASSERT(item);

    MLabel subTitle;
    MLabel title;

    MBasicListItemStubI->stubSetReturnValue<MLabel*>("subtitleLabelWidget", &subTitle);
    MBasicListItemStubI->stubSetReturnValue<MLabel*>("titleLabelWidget", &title);

    QGraphicsLayout *layout= item->createLayout();
    Q_ASSERT(layout);
    QCOMPARE(addItemCalled, 3);
}

QTEST_APPLESS_MAIN(Ut_DrillDownItem);

#include ".moc/ut_drilldownitem.moc"
