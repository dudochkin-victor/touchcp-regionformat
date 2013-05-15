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
#include "brief.h" 
#include "stubbase.h" 

/* Stub class.
 * With this class, it is possible to easily check the methods input parameters, and to define the
 * return values. Also it is possible to check the method call.
 *
 * Extend this, with the proxy object, as you need more and more complicated unit tests.
 */
class BriefStub : public StubBase {
    public:
};

/*
 * Create Stub instance
 */
BriefStub defaultBriefStub;
BriefStub *BriefStub = &defaultBriefStub;

/* Proxy object, which calls the stub.
 * Modify if needed
 */

Brief::Brief()
{
}

QString Brief::titleText() const
{
    return QString();
}

QString Brief::valueText() const
{
    return QString();
}

