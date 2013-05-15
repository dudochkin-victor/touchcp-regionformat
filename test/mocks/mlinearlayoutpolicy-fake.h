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
#include <mlinearlayoutpolicy.h>
#include "stubbase.h" 

/* Stub class.
 * With this class, it is possible to easily check the methods input parameters, and to define the
 * return values. Also it is possible to check the method call.
 *
 * Extend this, with the proxy object, as you need more and more complicated unit tests.
 */
class MLinearLayoutStub : public StubBase {
    public:
};

/*
 * Create Stub instance
 */
MLinearLayoutStub defaultMLinearLayoutStub;
MLinearLayoutStub *MLinearLayoutStub = &defaultMLinearLayoutStub;

/* Fake Linear layout policy
 *
 * With this source you can fake the linear layout policy,
 * so it will only handle a list of items for you, and it will not require
 * you to use X for testing.
 *
 * ! If you use this, you will also need to use mabstractlayoutpolicy-fake.cpp
 */

/* Proxy object, which calls the stub.
 * Modify if needed
 */

MLinearLayoutPolicy::MLinearLayoutPolicy(MLayout* p, Qt::Orientation):
    MAbstractLayoutPolicy(p)
{ }

MLinearLayoutPolicy::~MLinearLayoutPolicy(){}
void MLinearLayoutPolicy::addItem(QGraphicsLayoutItem* item)
{
    MAbstractLayoutPolicy::addItem(item);
}

void MLinearLayoutPolicy::addItem(QGraphicsLayoutItem* item, Qt::Alignment)
{
    addItem(item);
}

void MLinearLayoutPolicy::removeAt(int pos)
{
    MAbstractLayoutPolicy::removeAt(pos);
}
