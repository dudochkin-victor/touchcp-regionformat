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


class TestTableModel: public QAbstractTableModel
{
    public:
        virtual QModelIndex index(int row, int column, QModelIndex parent = QModelIndex());
        virtual int rowCount (
            const QModelIndex &parent = QModelIndex()) const;
        virtual QVariant data (
            const QModelIndex &index,
            int role = Qt::DisplayRole) const;
        virtual int columnCount (const QModelIndex&) const;
};

QModelIndex TestTableModel::index(int row, int column, QModelIndex )
{
    return createIndex(row, column);
}

int TestTableModel::rowCount(const QModelIndex &) const
{
    return 1;
}

int TestTableModel::columnCount(const QModelIndex &) const
{
    return 1;
}

QVariant TestTableModel::data(const QModelIndex &,
            int ) const
{
    QList<QString> strList;
    strList << "CurrentEndonym" << "CurrentRegion";


    return QVariant(QStringList(strList));
}
