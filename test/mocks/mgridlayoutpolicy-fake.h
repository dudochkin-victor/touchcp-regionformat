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
#include <mgridlayoutpolicy.h>
#include "stubbase.h" 

/* Stub class.
 * With this class, it is possible to easily check the methods input parameters, and to define the
 * return values. Also it is possible to check the method call.
 *
 * Extend this, with the proxy object, as you need more and more complicated unit tests.
 */
class MGridLayoutStub : public StubBase {
    public:
};

/*
 * Create Stub instance
 */
MGridLayoutStub defaultMGridLayoutStub;
MGridLayoutStub *MGridLayoutStub = &defaultMGridLayoutStub;

/*
 * Fake GridLayoutPolicy.
 * It makes you able to launch the tests without X.
 *
 * ! It does not handle the list of items currently.
 * ! If you use this, you will also need to use mabstractlayoutpolicy-fake.cpp
 */

/* Proxy object, which calls the stub.
 * Modify if needed
 */

class MGridLayoutPolicyPrivate
{
public:
    QMap<QPair<int, int>, QGraphicsLayoutItem*> items;
};

static QHash<const MGridLayoutPolicy*, MGridLayoutPolicyPrivate*> priv;
MGridLayoutPolicy::MGridLayoutPolicy(MLayout* p)
    : MAbstractLayoutPolicy(p)
{
    priv[this] = new MGridLayoutPolicyPrivate;
}

MGridLayoutPolicy::~MGridLayoutPolicy(){}

QGraphicsLayoutItem* MGridLayoutPolicy::itemAt(int row, int col) const
{
    return priv[this]->items[QPair<int, int>(row, col)];
}

int MGridLayoutPolicy::columnCount() const
{
    return priv[this]->items.count(); // FALSE!! this is all of the items
}

void MGridLayoutPolicy::removeAt(int i)
{
    MAbstractLayoutPolicy::removeAt(i);
}

void MGridLayoutPolicy::addItem(QGraphicsLayoutItem* item, int row, int col, int, int, Qt::Alignment)
{
    QPair<int, int> key(row, col);
    //priv[this]->items[QPair<int, int>(row, col)] = item;
    priv[this]->items[key] = item;
    MAbstractLayoutPolicy::addItem(item);
}

