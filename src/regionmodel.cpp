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

#include <string>

#include <QObject>
#include <QVariant>
#include <QStringList>
#include <QDebug>

#include <MLocale>

#include "regionmodel.h"
#include "regionconf.h"

#include "debug.h"


RegionModel& RegionModel::instance()
{
    static RegionModel model;
    return model;
}

RegionModel::RegionModel(QObject *parent) :
    MAbstractItemModel(parent)
{
    populateModel();
}

RegionModel::~RegionModel()
{
}

void RegionModel::retranslateList()
{
    m_Data.clear();
    m_LookupRegionNameByLocale.clear();
    m_RegionIndexMap.clear();
    m_GroupLabels.clear();
    m_GroupMap.clear();
    m_Data.clear();
    m_LookupRegionNameByLocale.clear();
    populateModel();
    reset();
}

void RegionModel::populateModel()
{
    RegionConf conf;
    QList<RegionData> regionList = conf.getAvailableRegions();
    foreach(RegionData rd, regionList) {
        int pos = m_Data.size();
        m_Data.append(rd);
        m_LookupRegionNameByLocale.insert(rd.Locale, pos);
    }
}

void RegionModel::fillGroupList()
{
    int i = 0;
    foreach (RegionData rdata, m_Data) {
        QChar label = rdata.UiString[0];
        int groupIndex = m_GroupLabels.indexOf(label);
        if (groupIndex == -1) {
            m_GroupLabels.append(label);
            groupIndex = m_GroupLabels.count() - 1;
        }
        m_GroupMap[groupIndex].append(i);
        QVector<int> indexVec(2);
        indexVec[0] = groupIndex;
        indexVec[1] = m_GroupMap[groupIndex].count() - 1;
        m_RegionIndexMap[rdata.Locale] = indexVec;
        ++i;
    }
}

int RegionModel::groupCount() const
{
    if (m_GroupLabels.isEmpty()) {
        const_cast<RegionModel*>(this)->fillGroupList();
    }

    return m_GroupLabels.count();
}

int RegionModel::rowCountInGroup(int group) const
{
    if (group == -1) {
        return m_Data.count();
    }

    if (m_GroupMap.isEmpty()) {
        const_cast<RegionModel*>(this)->fillGroupList();
    }

    return m_GroupMap[group].count();
}

QString RegionModel::groupTitle(int group) const
{
    if (m_GroupMap.isEmpty()) {
        const_cast<RegionModel*>(this)->fillGroupList();
    }
    if (group > -1 && group < m_GroupLabels.count())
        return m_GroupLabels[group];

    return QString();
}

QVariant RegionModel::itemData(int row, int group, int role) const
{
    if (m_GroupMap.isEmpty()) {
        const_cast<RegionModel*>(this)->fillGroupList();
    }

    int flatIndex = row;
    if (group >= 0 && row >= 0) {
        flatIndex = m_GroupMap[group][row];
    }

    if (m_Data.count() > flatIndex) {
        if ((role == FilterRole) || (role == RegionName)) {
            QString str =  m_Data[flatIndex].UiString;
            return QVariant(str);
        } else if (role == Qt::DisplayRole) {
            QStringList strList;
            strList << m_Data[flatIndex].UiString << m_Data[flatIndex].Locale;

            return QVariant(strList);
        }
    }
    return QVariant();
}

void RegionModel::updateData(const QModelIndex &first, const QModelIndex &last)
{
    emit dataChanged(first, last);
}

QString RegionModel::getRegionName(const QString& locale) const
{
    int row = m_LookupRegionNameByLocale.value(locale);
    QStringList strList = itemData(row, -1, Qt::DisplayRole).toStringList();
    if (strList.isEmpty()) {
        return "";
    }
    return strList[0];
}

QModelIndex RegionModel::getIndex(const QString& locale) const
{
    if (!m_RegionIndexMap.contains(locale)) {
        qWarning() << "locale not in model:" << locale;
        return QModelIndex();
    }

    QVector<int> indexVec = m_RegionIndexMap[locale];
    QModelIndex parent = index(indexVec[0], 0);
    QModelIndex idx = index(indexVec[1], 0, parent);
    return idx;
}


