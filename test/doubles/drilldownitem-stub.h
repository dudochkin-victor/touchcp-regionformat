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

#include "drilldownitem.h"

#include <MLabel>
#include <MImageWidget>

#include <QtGui/QGraphicsGridLayout>

DrillDownItem::DrillDownItem(QGraphicsItem *parent)
    : MBasicListItem(MBasicListItem::TitleWithSubtitle, parent)
{

}

DrillDownItem::~DrillDownItem()
{

}

QGraphicsLayout *DrillDownItem::createLayout()
{
    return 0;
}

// vim: sw=4 sts=4 et tw=100
