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

#include "regionconf.h"
#include "stubbase.h"

class RegionConfStub : public StubBase {
    public:
        QList<RegionData> getAvailableRegions();
};

QList<RegionData> RegionConfStub::getAvailableRegions()
{
    stubMethodEntered("getAvailableRegions");
    return stubReturnValue< QList<RegionData> >("getAvailableRegions");
}

RegionConfStub defaultRConfStub;
RegionConfStub *RConfStub = &defaultRConfStub;

RegionConf::RegionConf() {}
RegionConf::~RegionConf() {}

QList<RegionData> RegionConf::getAvailableRegions()
{
    return RConfStub->getAvailableRegions();
}
