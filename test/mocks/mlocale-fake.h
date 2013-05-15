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
#ifndef MLOCALE_FAKE_H
#define MLOCALE_FAKE_H

#include <QObject>
#include "qdatetime-fake.h"
#include "mlocale.h"

static QHash<const MLocale*, QString> endonymlist;

MLocale::MLocale(QObject *) :
    d_ptr(0)
{

}

MLocale::MLocale(const QString &local, QObject *) :
    d_ptr(0)
{
    endonymlist[this] = local;
}

MLocale::~MLocale()
{
}

void MLocale::connectSettings()
{

}

void MLocale::disconnectSettings()
{
}

QString MLocale::formatNumber(int ) const
{
    return QString("mcmx");
}

QString MLocale::formatDateTime(const QDateTime &, DateType ,
                           TimeType ,
                           CalendarType )  const
{
    return QString("ABCDE");
}

QString MLocale::formatNumber(double , int ) const
{
    return QString("FGHIJ");
}

QString MLocale::formatCurrency(double , const QString &) const
{
    return QString("KLMN");
}

QString MLocale::countryEndonym() const
{
    return endonymlist[this] + "endonym";
}

#endif
