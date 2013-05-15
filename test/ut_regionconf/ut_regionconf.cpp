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
#include "regionconf.h" 

class Ut_RegionConf : public QObject
{
    public:
        Q_OBJECT;

    private slots:
        void initTestCase();
        void cleanupTestCase();
        void init();
        void cleanup();

        void testGetAvailableRegions();

    private:
        RegionConf *m_subject;
};

void Ut_RegionConf::initTestCase()
{
}

void Ut_RegionConf::cleanupTestCase()
{
}


void Ut_RegionConf::cleanup()
{
    delete m_subject;
}

void Ut_RegionConf::init()
{
    m_subject = new RegionConf();
}

/**
  Checks if the regions coming from the config are returned and sorted 
  properly by getAvailableRegions()
  Logical ids are not being translated in this test cases, so we can give 
  arbitrary test data for the region (country) names.
  */
void Ut_RegionConf::testGetAvailableRegions()
{
    QList<QString> testData;
    testData << "Belgium (Dutch)" << "nl_BE" << "Belgium (French)" << "fr_BE" 
        << "Argentina" << "es_AR" << "The Netherlands" << "nl_NL";
    m_subject->setTestConfigData(testData);
    QList<RegionData> rlist = m_subject->getAvailableRegions();
    QList<QString> result;
    foreach (RegionData rdata, rlist) {
        result << rdata.UiString;
        result << rdata.Locale;
    }
    QList<QString> expected;
    expected << "Argentina" << "es_AR" << "Belgium (Dutch)" << "nl_BE" << 
        "Belgium (French)" << "fr_BE" << "The Netherlands" << "nl_NL";
    QCOMPARE(result, expected);
}

QTEST_APPLESS_MAIN(Ut_RegionConf);

#include ".moc/ut_regionconf.moc"
