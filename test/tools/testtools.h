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

#ifndef TESTTOOLS_H
#define TESTTOOLS_H

#include <QGraphicsItem>
#include <QSettings>

QSettings* createQSettingsWithAbsPath(QString fileName);

void parentOf(const QObject *child);
void printObjectsChildren(const QObject *parent);
void printItemsChildren(const QGraphicsItem *parent);

template <class T>
const T findChildItem(QGraphicsItem *parent, const QString &name)
{
    static QString tab;
    QList<QGraphicsItem*> children;
    QGraphicsItem *ret = NULL;
    int size;
    int i;

    if(dynamic_cast<QObject*>(parent)->objectName() == name)
        return dynamic_cast<T>(parent);

    children = parent->QGraphicsItem::childItems();
    size = children.size();

    for(i=0; i<size; i++){
        ret = findChildItem<T>(children.at(i), name);
        if(ret)
            break;
    }

    return dynamic_cast<T>(ret);
}

#endif

