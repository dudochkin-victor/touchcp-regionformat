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

#include <QDebug>

#include <MLayout>
#include <MButton>
#include <MLinearLayoutPolicy>
#include <MGridLayoutPolicy>
#include <MApplication>
#include <MApplicationWindow>

#include "debug.h"

#include "widgetlist.h"

WidgetList::WidgetList(QGraphicsWidget *parent) :
    MWidget(parent)
{
    m_Layout = new MLayout();

    m_PortraitLayoutPolicy = new MLinearLayoutPolicy(m_Layout, Qt::Vertical);
    m_LandscapeLayoutPolicy = new MGridLayoutPolicy(m_Layout);

    m_Layout->setLandscapePolicy(m_LandscapeLayoutPolicy);
    m_Layout->setPortraitPolicy(m_PortraitLayoutPolicy);
    m_LandscapeLayoutPolicy->setSpacing(0);
    m_PortraitLayoutPolicy->setSpacing(0);
    setLayout(m_Layout);
}

WidgetList::~WidgetList()
{
}

void WidgetList::setLayoutMargins(qreal left, qreal top, qreal right, qreal bottom)
{
    m_Layout->setContentsMargins(left, top, right, bottom);
}

void WidgetList::addWidget(MWidget *wgt)
{
    wgt->setContentsMargins(0, 0, 0, 0);
    if(m_PortraitLayoutPolicy->indexOf(wgt) < 0){
        wgt->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        int i = m_PortraitLayoutPolicy->count();
        m_PortraitLayoutPolicy->addItem(wgt);
        m_LandscapeLayoutPolicy->addItem(wgt, i/2, i%2);
    }
}

void WidgetList::removeWidget(MWidget *wgt)
{
    if(0 <= m_PortraitLayoutPolicy->indexOf(wgt)){
        m_PortraitLayoutPolicy->removeItem(wgt);
        m_LandscapeLayoutPolicy->removeItem(wgt);
    }
}

