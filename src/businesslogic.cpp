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

#include "langinfo.h"

#include <QString>
#include <QStringList>
#include <QLocale>
#include <QTimer>
#include <QTime>
#include <QDate>

#include <MLocale>
#include <MGConfItem>

#include "regionmodel.h"
#include "businesslogic.h"

#include "debug.h"

/* GConf keys to be used:
 *                              MLocale main settings
 * ┌────────────────────┬───────────────────────────────────┬─────────────────────────┐
 * │    gconf key       │            description            │      example value      │
 * │/meegotouch/i18n/...│                                   │                         │
 * ├────────────────────┼───────────────────────────────────┼─────────────────────────┤
 * │  .../lc_time       │for date, time, and calendar       │ar@calendar=islamic      │
 * ├────────────────────┼───────────────────────────────────┼─────────────────────────┤
 * │  .../lc_collate    │for sorting                        │de_DE@collation=phonebook│
 * ├────────────────────┼───────────────────────────────────┼─────────────────────────┤
 * │  .../lc_numeric    │formatting of numbers              │hi                       │
 * ├────────────────────┼───────────────────────────────────┼─────────────────────────┤
 * │  .../lc_monetary   │for formatting of amounts of money │fi_FI@currency=EUR       │
 * └────────────────────┴───────────────────────────────────┴─────────────────────────┘
 *                      Regionformatapplet / Suw private keys
 * ┌────────────────────┬───────────────────────────────────┬─────────────────────────┐
 * │    gconf key       │            description            │      example value      │
 * │/meegotouch/i18n/...│                                   │                         │
 * ├────────────────────┼───────────────────────────────────┼─────────────────────────┤
 * │  .../region        │user/suw choosen base region       │en_US                    │
 * └────────────────────┴───────────────────────────────────┴─────────────────────────┘
 */

const QString NumberFormatLocaleLatin("en");
const QString NumberFormatLocaleArabic("ar");
const QString FallbackRegion("en_GB");

namespace GConfKey
{
    const QString Region("/meegotouch/i18n/region");
    const QString UserRegion("/meegotouch/i18n/userselectedregion");
    const QString LcTime("/meegotouch/i18n/lc_time");
    const QString LcCollate("/meegotouch/i18n/lc_collate");
    const QString LcNumeric("/meegotouch/i18n/lc_numeric");
    const QString LcMonetary("/meegotouch/i18n/lc_monetary");
}

BusinessLogic::BusinessLogic () :
    m_RegionGConfItem(GConfKey::Region),
    m_UserRegionGConfItem(GConfKey::UserRegion),
    m_LcTimeGConfItem(GConfKey::LcTime),
    m_LcCollateGConfItem(GConfKey::LcCollate),
    m_LcNumericGConfItem(GConfKey::LcNumeric),
    m_LcMonetaryGConfItem(GConfKey::LcMonetary)
{
    if(getRegion().isEmpty())
        setRegion(FallbackRegion);

    /* MLocale is a singleton, so it is enough to create only one, and use this if needed */
    m_CurrentLocale = new MLocale();
    /* ... and this should follow the regionchanges */
    m_CurrentLocale->connectSettings();
    connect(m_CurrentLocale, SIGNAL(settingsChanged()),
            this, SLOT(settingsChangedSlot()));

    /* In case of region change, 4 settingsChanged() signal will be emitted by MLocale, but as less
     * as possible should be forwarded
     */
    connect(&m_Timer, SIGNAL(timeout()),
            this, SLOT(timeoutSlot()));
    m_Timer.setInterval(100);
    m_Timer.setSingleShot(true);

    /* Do not monitor the other GConf keys, they will be monitored by MLocale.
     * Note: this was needed, because at first this object's gconf items were informed about the
     * change, and only after that the MLocale's GConf keys, and only after this the MLocale object
     * produced the right formats
     */
    connect(&m_RegionGConfItem, SIGNAL(valueChanged()),
            this, SLOT(regionChangedSlot()));
}

BusinessLogic::~BusinessLogic()
{
    m_CurrentLocale->disconnectSettings();
    delete m_CurrentLocale;
}

BusinessLogic& BusinessLogic::instance()
{
    static BusinessLogic _instance;
    return _instance;
}

void BusinessLogic::timeoutSlot()
{
    emit settingsChanged();
}

void BusinessLogic::settingsChangedSlot()
{
    m_Timer.start();
}
void BusinessLogic::regionChangedSlot()
{
    emit regionChanged();
}

void BusinessLogic::setRegion(const QString &locale)
{
    qDebug("Setting %s to %s",
            qPrintable(GConfKey::Region),
            qPrintable(locale));
    m_RegionGConfItem.set(locale);
    m_UserRegionGConfItem.set(true);
    setLcTime(locale);
    setLcCollate(locale);
    setLcNumeric(locale);
    setLcMonetary(locale);
}

QString BusinessLogic::getRegion() const
{
    QString ret = m_RegionGConfItem.value().toString();
    return ret;
}

QString BusinessLogic::getRegionName() const
{
    QString reg = getRegion();
    RegionModel &model = RegionModel::instance();
    QString ret = model.getRegionName(reg);
    qDebug("RegionName for region %s : %s",
            qPrintable(reg),
            qPrintable(ret));
    return ret;
}

void BusinessLogic::setLcTime(const QString &locale)
{
    qDebug("Setting %s to %s",
            qPrintable(GConfKey::LcTime),
            qPrintable(locale));
    m_LcTimeGConfItem.set(locale);
}

QString BusinessLogic::getLcTime() const
{
    return m_LcTimeGConfItem.value().toString();
}

void BusinessLogic::setLcCollate(const QString &locale)
{
    qDebug("Setting %s to %s",
            qPrintable(GConfKey::LcCollate),
            qPrintable(locale));
    m_LcCollateGConfItem.set(locale);
}

QString BusinessLogic::getLcCollate() const
{
    return m_LcCollateGConfItem.value().toString();
}

void BusinessLogic::setLcNumeric(const QString &locale)
{
    qDebug("Setting %s to %s",
            qPrintable(GConfKey::LcNumeric),
            qPrintable(locale));
    m_LcNumericGConfItem.set(locale);
}

QString BusinessLogic::getLcNumeric() const
{
    return m_LcNumericGConfItem.value().toString();
}

void BusinessLogic::setLcMonetary(const QString &locale)
{
    qDebug("Setting %s to %s",
            qPrintable(GConfKey::LcMonetary),
            qPrintable(locale));
    m_LcMonetaryGConfItem.set(locale);
}

QString BusinessLogic::getLcMonetary() const
{
    return m_LcMonetaryGConfItem.value().toString();
}

QStringList BusinessLogic::getNumberFormatEndonymList() const
{
    MLocale locLatin(NumberFormatLocaleLatin);
    MLocale locArabic(NumberFormatLocaleArabic);
    QStringList numberFormatEndonyms;
    /* The order is synchronized with NumberFormat enumeration. */
    numberFormatEndonyms
        << locLatin.formatNumber(12345) /* latin numbers */
        << locArabic.formatNumber(12345); /* hindi numbers */
    return numberFormatEndonyms;
}

void BusinessLogic::setNumberFormat(NumberFormat fmt)
{
    switch(fmt){
        case LatinNumbers :
            setLcNumeric(NumberFormatLocaleLatin);
            break;
        case ArabicNumbers :
            /* default region which should be arabic at this point */
            setLcNumeric(NumberFormatLocaleArabic);
            break;
        default :
            break;
    }
}

/*!
 * Returns a string that can be used as an example to show how a date value will
 * be printed using the current region settings.
 */
QString BusinessLogic::dateExample() const
{

    QString ret = m_CurrentLocale->formatDateTime(QDateTime::currentDateTime(),
            MLocale::DateFull, MLocale::TimeNone);
    ret += "; ";
    ret += m_CurrentLocale->formatDateTime(QDateTime::currentDateTime(),
            MLocale::DateShort, MLocale::TimeNone);

    return ret;
}

/*!
 * Returns a string that can be used as an example to show how a time value will
 * be shown with the current region settings.
 */
QString BusinessLogic::timeExample() const
{

    QString ret = m_CurrentLocale->formatDateTime(QDateTime::currentDateTime(),
            MLocale::DateNone, MLocale::TimeShort);
    ret += "; ";
    ret += m_CurrentLocale->formatDateTime(QDateTime::currentDateTime().addSecs(12 * 60 * 60),
            MLocale::DateNone, MLocale::TimeShort);

    return ret;
}

/*!
 * Returns a string that can be used as an example string that shows how a
 * number will be printed with the current region settings.
 */
QString BusinessLogic::numberExample(double f) const
{
    return m_CurrentLocale->formatNumber(f, 2);
}

/*!
 * Returns a string that can be used as an example string for the region to
 * demonstrate how a currency will be printed. 
 */
QString BusinessLogic::currencyExample(double f) const
{
    // Empty currency symbol seems to work, though it's undocumented.
    return m_CurrentLocale->formatCurrency (f, "");
}

