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

#ifndef REGIONFORMAT_REGIONMODEL_H
#define REGIONFORMAT_REGIONMODEL_H

#include <MAbstractItemModel>
#include <QMap>
#include "regionconf.h"

class QModelIndex;
class QAbstractTableModel;

class RegionModel : public MAbstractItemModel {
    Q_OBJECT

    public:
        static RegionModel& instance();
        ~RegionModel();
        void retranslateList();
        int groupCount() const;
        int rowCountInGroup(int group) const;
        QString groupTitle(int group) const;
        QVariant itemData(int row, int group, int role = Qt::DisplayRole) const;
        void updateData(const QModelIndex &first, const QModelIndex &last);

        QString getRegionName(const QString& locale) const;
        QModelIndex getIndex(const QString& locale) const;

        enum Columns {
            Locale = 0,
            RegionName,
            NumberOfColumns
        };

        enum ItemDataRole {
            FilterRole = Qt::UserRole+1
        };

    protected:
        RegionModel(QObject *parent = 0);

    private:
        void populateModel();
        void fillGroupList();

    private:
        QMap< QString,QVector<int> > m_RegionIndexMap;
        QList<QChar>                    m_GroupLabels;
        QMap<int, QList<int> >        m_GroupMap;
        QList<RegionData> m_Data;
        QMap<QString, int> m_LookupRegionNameByLocale;
        friend class Ut_RegionModel;
};

#endif

