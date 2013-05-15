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

#include <QObject>
#include <QVariant>
#include "stubbase.h"
#include "regionmodel.h"

/* Stub class.
 * With this class, it is possible to easily check the methods input parameters, and to define the
 * return values. Also it is possible to check the method call.
 *
 * Extend this, with the proxy object, as you need more and more complicated unit tests.
 */
class RegionModelStub : public StubBase {
    public:
        QModelIndex getIndex(const QString& str);
        QString groupTitle(int group) const;
        QVariant itemData(int row, int group, int role) const;
        QString getRegionName(const QString &region) const;
        int rowCountInGroup(int group) const;
        int groupCount() const;
        void updateData(const QModelIndex &first, const QModelIndex &last);
};

QModelIndex RegionModelStub::getIndex(const QString& str)
{
    QList<ParameterBase*> params;
    params.append(new Parameter<QString>(str));
    stubMethodEntered("getIndex", params);

    return stubReturnValue<QModelIndex> ("getIndex");
}

QString RegionModelStub::groupTitle(int group) const
{
    QList<ParameterBase*> params;
    params.append(new Parameter<int>(group));
    stubMethodEntered("groupTitle", params);

    return stubReturnValue<QString> ("groupTitle");

}
QVariant RegionModelStub::itemData(int row, int group, int role) const
{
    QList<ParameterBase*> params;
    params.append(new Parameter<int>(row));
    params.append(new Parameter<int>(group));
    params.append(new Parameter<int>(role));
    stubMethodEntered("itemData", params);

    return stubReturnValue<QVariant> ("itemData");
}

QString RegionModelStub::getRegionName(const QString &region) const
{
    QList<ParameterBase*> params;
    params.append(new Parameter<QString>(region));
    stubMethodEntered("getRegionName", params);

    return stubReturnValue<QString> ("getRegionName");
}

int RegionModelStub::rowCountInGroup(int group) const
{
    QList<ParameterBase*> params;
    params.append(new Parameter<int>(group));
    stubMethodEntered("rowCountInGroup", params);

    return stubReturnValue<int> ("rowCountInGroup");
}

int RegionModelStub::groupCount() const
{
    stubMethodEntered("groupCount");

    return stubReturnValue<int> ("groupCount");
}

void RegionModelStub::updateData(const QModelIndex &first, const QModelIndex &last)
{
    QList<ParameterBase*> params;
    params.append(new Parameter<const QModelIndex>(first));
    params.append(new Parameter<const QModelIndex>(last));
    stubMethodEntered("updateData", params);
}

/*
 * Create Stub instance
 */
RegionModelStub defaultRegionModelStub;
RegionModelStub *RegionModelStub = &defaultRegionModelStub;

/* Proxy object, which calls the stub.
 * Modify if needed
 */

RegionModel& RegionModel::instance()
{
    static RegionModel model;
    return model;
}

RegionModel::RegionModel(QObject *parent) :
    MAbstractItemModel(parent)
{
}

RegionModel::~RegionModel()
{
}

QVariant RegionModel::itemData(int row, int group, int role) const
{
    return RegionModelStub->itemData(row, group, role);
}

QString RegionModel::getRegionName(const QString &reg) const
{
    return RegionModelStub->getRegionName(reg);
}

QModelIndex RegionModel::getIndex(const QString& str) const
{
    return RegionModelStub->getIndex(str);
}

int RegionModel::rowCountInGroup(int group) const
{
    return RegionModelStub->rowCountInGroup(group);
}

QString RegionModel::groupTitle(int group) const
{
    return RegionModelStub->groupTitle(group);
}

int RegionModel::groupCount() const
{
    return RegionModelStub->groupCount();
}

void RegionModel::updateData(const QModelIndex &first, const QModelIndex &last)
{
    RegionModelStub->updateData(first, last);
}

void RegionModel::retranslateList()
{

}

