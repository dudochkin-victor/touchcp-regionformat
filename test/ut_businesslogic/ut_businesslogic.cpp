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
#include "businesslogic.h" 
#include "mgconfitem-fake.h"
#include "gconfitemprivate-fake.h"
#include "mlocale-fake.h"
#include "signalchecker.h"
#include "regionmodel-stub.h"

static const QString myFavTestStr("subidubidooooo");

class Ut_BusinessLogic : public QObject
{
    public:
        Q_OBJECT;

    private slots:
        void initTestCase();
        void cleanupTestCase();
        void init();
        void cleanup();

        /* Signal checking */
        void testRegionChangedSignal();

        /* Setter/getter tests */
        void testSetGetLcTime();
        void testSetGetLcCollate();
        void testSetGetLcNumeric();
        void testSetGetLcMonetary();
        void testSetGetRegion();
        void testGetRegionName();
        void testGetNumberFormatEndonomyList();
        void testSetNumberFormat();
        void testExamples();
    private:
        BusinessLogic *m_blogic;
        SignalChecker *m_sChecker;
};

void Ut_BusinessLogic::initTestCase()
{
    BusinessLogic &blogic = BusinessLogic::instance();
    m_blogic = &blogic;
    m_sChecker = new SignalChecker(m_blogic);
    m_sChecker->addSignalChecker(SIGNAL(regionChanged()));
    m_sChecker->addSignalChecker(SIGNAL(settingsChanged()));
}

void Ut_BusinessLogic::cleanupTestCase()
{
    delete m_sChecker;
}


void Ut_BusinessLogic::cleanup()
{
    m_sChecker->check();
}

void Ut_BusinessLogic::init()
{
    m_sChecker->check();
}
void Ut_BusinessLogic::testRegionChangedSignal()
{
    m_sChecker->increaseSigCounter(SIGNAL(regionChanged()));
    MGConfItem("/meegotouch/i18n/region").set(myFavTestStr);
    m_sChecker->check();
    m_sChecker->increaseSigCounter(SIGNAL(regionChanged()));
    MGConfItem("/meegotouch/i18n/region").unset();
}

void Ut_BusinessLogic::testSetGetLcTime()
{
    MGConfItem gcitem("/meegotouch/i18n/lc_time");

    QVERIFY(!m_blogic->getLcTime().isNull());
    m_blogic->setLcTime(myFavTestStr);

    QCOMPARE(gcitem.value().toString(), myFavTestStr);
    QCOMPARE(m_blogic->getLcTime(), myFavTestStr);
}

void Ut_BusinessLogic::testSetGetLcCollate()
{
    MGConfItem gcitem("/meegotouch/i18n/lc_collate");

    QVERIFY(!m_blogic->getLcCollate().isNull());
    m_blogic->setLcCollate(myFavTestStr);

    QCOMPARE(gcitem.value().toString(), myFavTestStr);
    QCOMPARE(m_blogic->getLcCollate(), myFavTestStr);
}

void Ut_BusinessLogic::testSetGetLcNumeric()
{
    MGConfItem gcitem("/meegotouch/i18n/lc_numeric");

    QVERIFY(!m_blogic->getLcNumeric().isNull());
    m_blogic->setLcNumeric(myFavTestStr);

    QCOMPARE(gcitem.value().toString(), myFavTestStr);
    QCOMPARE(m_blogic->getLcNumeric(), myFavTestStr);
}

void Ut_BusinessLogic::testSetGetLcMonetary()
{
    MGConfItem gcitem("/meegotouch/i18n/lc_monetary");

    QVERIFY(!m_blogic->getLcMonetary().isNull());
    m_blogic->setLcMonetary(myFavTestStr);

    QCOMPARE(gcitem.value().toString(), myFavTestStr);
    QCOMPARE(m_blogic->getLcMonetary(), myFavTestStr);
}

void Ut_BusinessLogic::testSetGetRegion()
{
    MGConfItem gcmonetary("/meegotouch/i18n/lc_monetary");
    MGConfItem gcnumeric("/meegotouch/i18n/lc_numeric");
    MGConfItem gctime("/meegotouch/i18n/lc_time");
    MGConfItem gccollate("/meegotouch/i18n/lc_collate");
    MGConfItem gcregion("/meegotouch/i18n/region");

    /* reset all at first.... */
    gcmonetary.unset();
    gcnumeric.unset();
    gctime.unset();
    gccollate.unset();
    m_sChecker->check();

   m_sChecker->increaseSigCounter(SIGNAL(regionChanged()));

    m_blogic->setRegion(myFavTestStr);

    QCOMPARE(gcmonetary.value().toString(), myFavTestStr);
    QCOMPARE(gcnumeric.value().toString(), myFavTestStr);
    QCOMPARE(gctime.value().toString(), myFavTestStr);
    QCOMPARE(gccollate.value().toString(), myFavTestStr);
    QCOMPARE(gcregion.value().toString(), myFavTestStr);
    QCOMPARE(m_blogic->getLcMonetary(), myFavTestStr);
    QCOMPARE(m_blogic->getLcNumeric(), myFavTestStr);
    QCOMPARE(m_blogic->getLcTime(), myFavTestStr);
    QCOMPARE(m_blogic->getLcCollate(), myFavTestStr);
    QCOMPARE(m_blogic->getRegion(), myFavTestStr);
}

void Ut_BusinessLogic::testGetRegionName()
{
    RegionModelStub->stubSetReturnValue<QString> ("getRegionName", QString("Ende"));
    QCOMPARE(m_blogic->getRegionName(), QString("Ende"));
}

void Ut_BusinessLogic::testGetNumberFormatEndonomyList()
{
    QCOMPARE(m_blogic->getNumberFormatEndonymList(),  QStringList() << "mcmx" << "mcmx");
}

void Ut_BusinessLogic::testSetNumberFormat()
{
    MGConfItem gcnumeric("/meegotouch/i18n/lc_numeric");

    m_blogic->setNumberFormat(BusinessLogic::LatinNumbers);
    QCOMPARE(gcnumeric.value().toString(), QString("en"));
    QCOMPARE(m_blogic->getLcNumeric(), QString("en"));

    m_blogic->setNumberFormat(BusinessLogic::ArabicNumbers);
    QCOMPARE(gcnumeric.value().toString(), QString("ar"));
    QCOMPARE(m_blogic->getLcNumeric(), QString("ar"));
}

#include <langinfo.h>
char *nl_langinfo (nl_item __item)
{
    Q_UNUSED(__item);
    return NULL;
}

void Ut_BusinessLogic::testExamples()
{
    /* dateExample */
    QCOMPARE(m_blogic->dateExample(), QString("ABCDE; ABCDE")); 

    /* timeExample */
    QCOMPARE(m_blogic->timeExample(), QString("ABCDE; ABCDE")); 

    /* numberExample */
    QCOMPARE(m_blogic->numberExample(), QString("FGHIJ")); 

    /* currencyExample */
    QCOMPARE(m_blogic->currencyExample(10), QString("KLMN")); 
}

QTEST_APPLESS_MAIN(Ut_BusinessLogic);

#include ".moc/ut_businesslogic.moc"
