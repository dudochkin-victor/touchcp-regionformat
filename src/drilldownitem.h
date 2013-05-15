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

#ifndef DRILLDOWNITEM_H
#define DRILLDOWNITEM_H

#include <MBasicListItem>
class QGraphicsLayout;
class DrillDownItem: public MBasicListItem
{
    Q_OBJECT
public:
    DrillDownItem(QGraphicsItem *parent = NULL);
    virtual ~DrillDownItem();

protected:
    virtual QGraphicsLayout *createLayout();
    friend class Ut_DrillDownItem;
};

#endif
