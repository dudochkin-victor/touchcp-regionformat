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
#ifndef REGIONFORMAT_BUSINESSLOGIC_H
#define REGIONFORMAT_BUSINESSLOGIC_H

#include <QObject>
#include <QStringList>
#include <QTimer>

#include <MGConfItem>

class QString;
class QDate;
class QTime;
class MLocale;

class BusinessLogic : public QObject 
{
    Q_OBJECT

public:
    enum NumberFormat {
        LatinNumbers = 0,
        ArabicNumbers
    };

public:
    static BusinessLogic& instance();
    ~BusinessLogic ();

    void    setRegion(const QString &locale);
    QString getRegion() const;
    QString getRegionName() const;

    void    setLcTime(const QString &locale);
    QString getLcTime() const;

    void    setLcCollate(const QString &locale);
    QString getLcCollate() const;

    void    setLcNumeric(const QString &locale);
    QString getLcNumeric() const;

    void    setLcMonetary(const QString &locale);
    QString getLcMonetary() const;

    QStringList getNumberFormatEndonymList() const;
    void setNumberFormat(NumberFormat fmt);

    QString dateExample() const;
    QString timeExample() const;
    QString numberExample(double f = 1234.56) const;
    QString currencyExample(double f = 1234.56) const;

protected:
    BusinessLogic ();

signals:
    void regionChanged();
    void settingsChanged();
private slots:
    void regionChangedSlot();
    void timeoutSlot();
    void settingsChangedSlot();

private:
    MLocale *m_CurrentLocale;
    QTimer m_Timer;
    MGConfItem m_RegionGConfItem;
    MGConfItem m_UserRegionGConfItem;
    MGConfItem m_LcTimeGConfItem;
    MGConfItem m_LcCollateGConfItem;
    MGConfItem m_LcNumericGConfItem;
    MGConfItem m_LcMonetaryGConfItem;
};

#endif
