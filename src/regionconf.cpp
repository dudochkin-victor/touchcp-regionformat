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

#include <QList>
#include <QMultiMap>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QtDebug>
#include <MLocale>
#include "regionconf.h"

static const char *RegionConfPath = REGION_CONF_PATH;

RegionConf::RegionConf() {}

RegionConf::~RegionConf() {}

/**
  Parses conf file at REGION_CONF_PATH and generates
  RegionData list based on the current locale. If device language is
  changed this should be called again.
  */
QList<RegionData>
RegionConf::getAvailableRegions() {
    QMap<QString,QString> localeIdRegionMap = readRegionConfig();
    QMap<QString,RegionData> sortMap; // ui string is the key
    QMapIterator<QString,QString> i(localeIdRegionMap);
    while (i.hasNext()) {
        i.next();
        QString localeId = i.key();
        QString regionId = i.value();
        QString regionUiStr = translate(regionId);
        RegionData rdata(localeId, regionUiStr);
        QString sortKey = 
            regionUiStr.toLower().normalized(QString::NormalizationForm_D);
        sortMap.insert(sortKey, rdata);
    }

    QList<RegionData> regionList;
    foreach (RegionData region, sortMap.values()) {
        qDebug() << "found region" << region.UiString;
        regionList.append(region);
    }
    return regionList;
}

/**
  Translate the logicalId to a ui string. For unit tests
  this will return the untranslated logicalId
 */
QString
RegionConf::translate(const QString &logicalId) {
#ifdef UNIT_TEST
    return logicalId;
#else
    return qtTrId(logicalId.toAscii().data());
#endif
}

/**
  Reads the config file and returns a map from locale ids to
  region logical ids
  */
QMap<QString,QString>
RegionConf::readRegionConfig() {
    QMap<QString,QString> localeIdRegionMap;

#ifdef UNIT_TEST
    for (int i = 0; i < m_TestConfigData.size(); i += 2) {
        localeIdRegionMap.insert(m_TestConfigData[i+1], m_TestConfigData[i]);
    }

#else

    QFile confFile(RegionConfPath);
    if (!confFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning("unable to open %s", RegionConfPath);
        return QMap<QString,QString>();
    }

    QTextStream inStream(&confFile);
    while (!inStream.atEnd()) {
        QString line = inStream.readLine();
        QStringList fields = line.split(" ", QString::SkipEmptyParts);
        localeIdRegionMap.insert(fields[1], fields[0]);
    }
    confFile.close();
#endif

    return localeIdRegionMap;
}

#ifdef UNIT_TEST
/**
  Sets the config file content which will be used by getAvailableRegions()
  instead of the real config file.
  \param data contains the fields of the config in logical id1, locale id1,
  logical id2, locale id2... order
 */
void 
RegionConf::setTestConfigData(const QList<QString> &data) {
    m_TestConfigData = data;
}
#endif
