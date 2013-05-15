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
#include <QObject>
#include "mlocale-fake.h"
#include "regionconf-stub.h"
#include "regionmodel.h"
#include "testtablemodel.h"

class Ut_RegionModel : public QObject
{
    public:
        Q_OBJECT;

    private slots:
        void initTestCase();
        void cleanupTestCase();
        void init();
        void cleanup();

        void testConstruct();
        void testGroupCount();
        void testItemData();
        void testRowCountInGroup();
        void testGroupTitle();
        void testUpdateData();

    private:
};

void Ut_RegionModel::initTestCase()
{
}

void Ut_RegionModel::cleanupTestCase()
{
}


void Ut_RegionModel::cleanup()
{
}

void Ut_RegionModel::init()
{
    // RegionConf stub must set before creating RegionModel instance.
    // the resulting order supposed to be Finland, Germany, United Kingdom
    RegionData rGB("en_GB", "United Kingdom");
    RegionData rDE("de_DE", "Germany");
    RegionData rFI("fi_FI", "Finland");
    QList<RegionData> rdlist;
    rdlist << rGB << rDE << rFI;
    RConfStub->stubReset();
    RConfStub->stubSetReturnValue<QList <RegionData> >("getAvailableRegions",
                                                       rdlist);
}

void Ut_RegionModel::testConstruct()
{
    RegionModel &rmodel = RegionModel::instance();

    QVERIFY(&rmodel == &(RegionModel::instance()));

    // see values in init()
    QCOMPARE(rmodel.m_Data.count(), 3);
    QCOMPARE(rmodel.m_LookupRegionNameByLocale.count(), 3);
    QCOMPARE(rmodel.getRegionName("de_DE"), QString("Germany"));
}

void Ut_RegionModel::testGroupCount()
{
    RegionModel &model = RegionModel::instance();
    model.setGrouped(true);
    QCOMPARE(model.groupCount(), model.m_GroupLabels.count());
}

void Ut_RegionModel::testRowCountInGroup()
{
    RegionModel &model = RegionModel::instance();
    model.setGrouped(true);
    QCOMPARE(model.rowCountInGroup(-1), model.m_Data.count());
    for (int i=0;i < model.m_GroupMap.keys().count(); i++)
        QCOMPARE(model.rowCountInGroup(i), model.m_GroupMap[i].count());
}

void Ut_RegionModel::testGroupTitle()
{
    RegionModel &model = RegionModel::instance();
    model.setGrouped(true);
    for (int i=0;i < model.m_GroupLabels.count(); i++)
        QCOMPARE(model.groupTitle(i), QString(model.m_GroupLabels[i]));
    int badIdx = model.m_GroupLabels.count();
    QCOMPARE(model.groupTitle(badIdx), QString());
    badIdx = -1;
    QCOMPARE(model.groupTitle(badIdx), QString());
}

void Ut_RegionModel::testUpdateData()
{
    RegionModel &model = RegionModel::instance();
    model.setGrouped(true);
    QSignalSpy spy(&model, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)));
    model.updateData(QModelIndex(), QModelIndex());
    QCOMPARE(spy.count(), 1);
    model.updateData(QModelIndex(), QModelIndex());
    QCOMPARE(spy.count(), 2);
}

void Ut_RegionModel::testItemData()
{
    RegionModel &rmodel = RegionModel::instance();
    QList<QString> strList;
    strList << "Germany" << "de_DE";

    /* Not valid idx */
    QVERIFY(rmodel.itemData(5, -1, RegionModel::FilterRole).isNull());

    /* Valid idx, but not supported role */
    QVERIFY(rmodel.itemData(1, -1, Qt::SizeHintRole).isNull());

    /* FilterRole */
    QCOMPARE(rmodel.itemData(1, -1, RegionModel::FilterRole), QVariant(QString("Germany")));

    /* DisplayRole */
    QCOMPARE(rmodel.itemData(1, -1, Qt::DisplayRole), QVariant(QStringList(strList)));

    /* Columns */
    QCOMPARE(rmodel.itemData(1, -1, 0), QVariant(QStringList(strList)));

    /* Check getIndex */
    QModelIndex idx = rmodel.index(0, 0, rmodel.index(1, 0));
    QCOMPARE(rmodel.getIndex("de_DE"), idx);

    QCOMPARE(rmodel.getIndex("deDE"), QModelIndex());
}

QTEST_APPLESS_MAIN(Ut_RegionModel);

#include ".moc/ut_regionmodel.moc"
