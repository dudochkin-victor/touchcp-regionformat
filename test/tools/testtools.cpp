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

#include <QString>
#include <QDir>

#include "testtools.h"

QSettings* createQSettingsWithAbsPath(QString fileName)
{
    QSettings *s;
    /* FIXME Could not find better way to use absolute path with QSettings */
    QString oldPath = QDir::currentPath();
    if(!QDir::setCurrent("/")){
        qCritical("Could not change (temporary) current directory to /, "
                "needed to open files:\n\t%s", qPrintable(fileName));
    }
    s = new QSettings(fileName, QSettings::IniFormat);
    QDir::setCurrent(oldPath);
    return s;
}

void parentOf(const QObject *child)
{
    static QString tab;
    QObject *parent = child->parent();
    QString name;

    if(parent)
        name = parent->objectName();
    else
        name = "-";

    qDebug("Parent of %s is %s",
            qPrintable(child->objectName()),
            qPrintable(name)
            );

    if(parent){
        tab.append("\t");
        parentOf(parent);
        tab.chop(1);
    }
}

void printObjectsChildren(const QObject *parent)
{
    static QString tab;
    QString realName;
    QList<QObject*> children;
    QObject *o;
    int size;
    int i;

    realName = parent->objectName();
    if(realName == "")
        realName = "no name";
    qDebug("%s%s",
            qPrintable(tab),
            qPrintable(realName)
          );
   
    children = parent->QObject::children();
    size = children.size();
    
    tab.append("\t");
    for(i=0; i<size; i++){
        o = children.at(i);
        printObjectsChildren(o);
    }
    tab.chop(1);
}

void printItemsChildren(const QGraphicsItem *parent)
{
    static QString tab;
    QString realName;
    QList<QGraphicsItem*> children;
    QGraphicsItem *o;
    int size;
    int i;

    realName = dynamic_cast<const QObject*>(parent)->objectName();
    if(realName == "")
        realName = "no name";
    qDebug("%s%s",
            qPrintable(tab),
            qPrintable(realName)
          );
    
    children = parent->QGraphicsItem::childItems();
    size = children.size();
    
    tab.append("\t");
    for(i=0; i<size; i++){
        o = children.at(i);
        printItemsChildren(o);
    }
    tab.chop(1);
}

