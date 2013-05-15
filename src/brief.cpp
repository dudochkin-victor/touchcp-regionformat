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
/* vim:set et sw=4 ts=4 sts=4: */

#include "businesslogic.h"
#include "translation.h"
#include "brief.h"

#include "debug.h"

Brief::Brief ()
{
    connect(&BusinessLogic::instance(), 
            SIGNAL(regionChanged()),
            this, SIGNAL(valuesChanged()));
}

QString Brief::titleText() const
{
    return _(BriefTitle);
}

QString Brief::valueText () const
{
    BusinessLogic &l = BusinessLogic::instance();
    return l.getRegionName();
}

