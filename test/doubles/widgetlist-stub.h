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

#include "stubbase.h" 
#include "widgetlist.h"

/* Stub class.
 * With this class, it is possible to easily check the methods input parameters, and to define the
 * return values. Also it is possible to check the method call.
 *
 * Extend this, with the proxy object, as you need more and more complicated unit tests.
 */
class WidgetListStub : public StubBase {
    public:
};


/*
 * Create Stub instance
 */
WidgetListStub defaultWidgetListStub;
WidgetListStub *WidgetListStub = &defaultWidgetListStub;

/* Proxy object, which calls the stub.
 * Modify if needed
 */

WidgetList::WidgetList(QGraphicsWidget *parent) :
    MWidget(parent),
    m_Layout(0),
    m_PortraitLayoutPolicy(0),
    m_LandscapeLayoutPolicy(0)
{
}

WidgetList::~WidgetList()
{
}

void WidgetList::addWidget(MWidget *)
{
}

void WidgetList::removeWidget(MWidget *)
{
}

void WidgetList::setLayoutMargins(qreal, qreal, qreal, qreal)
{

}
