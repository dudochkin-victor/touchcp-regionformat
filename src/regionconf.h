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

#ifndef REGIONCONF_H__
#define REGIONCONF_H__

#include <QList>

class RegionData {
    public:
        RegionData(const QString &locale_, const QString &uiString_) 
            : Locale(locale_), UiString(uiString_) {}
        ~RegionData() {}

        QString Locale; //! localeId of the region
        QString UiString; //! localized ui string that should be shown
                          //! in region settings view
};

class RegionConf {
    public:
        RegionConf();
        virtual ~RegionConf();

        QList<RegionData> getAvailableRegions();
#ifdef UNIT_TEST
        void setTestConfigData(const QList<QString> &data);
#endif

    private:
        QMap<QString,QString> readRegionConfig();
        QString translate(const QString &logicalId);

#ifdef UNIT_TEST
        QList<QString> m_TestConfigData;
#endif
};


#endif // REGIONCONF_H__
