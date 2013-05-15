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
#include "mlayout.h"
#include "stubbase.h"

/* A fake mlayout
 *
 * Can be used to create tests which run without X.
 * It does nothing, handles nothing.
 *
 * If you use it, consider using one of the fake policies:
 * - mgridlayoutpolicy-fake.cpp
 * - mlinearlayoutpolicy-fake.cpp
 *
 */

#include <mabstractlayoutpolicy.h>

/* Stub class.
 * With this class, it is possible to easily check the methods input parameters, and to define the
 * return values. Also it is possible to check the method call.
 *
 * Extend this, with the proxy object, as you need more and more complicated unit tests.
 */
class MLayoutStub : public StubBase {
    public:
};

/*
 * Create Stub instance
 */
MLayoutStub defaultMLayoutStub;
MLayoutStub *MLayoutStub = &defaultMLayoutStub;

/* Proxy object, which calls the stub.
 * Modify if needed
 */

class MLayoutPrivate {

};

MLayout::MLayout(QGraphicsLayoutItem *) :
    d_ptr(new MLayoutPrivate)
{
}

MLayout::~MLayout()
{
    delete d_ptr;
}

void MLayout::setLandscapePolicy(MAbstractLayoutPolicy *policy)
{
    Q_UNUSED(policy);
    //d_ptr->landscapePolicy = policy;
}

void MLayout::setPortraitPolicy(MAbstractLayoutPolicy *policy)
{
    Q_UNUSED(policy);
    //d_ptr->portraitPolicy = policy;
}

int MLayout::count() const
{
    return 0;
}

void MLayout::invalidate()
{
}

static MAbstractLayoutPolicy *poli;
void MLayout::setPolicy(MAbstractLayoutPolicy *Poli)
{
    poli = Poli;
}

MAbstractLayoutPolicy* MLayout::policy() const
{
    return poli;
}
