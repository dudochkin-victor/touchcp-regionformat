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

#ifndef REGIONFORMAT_WIDGETLIST_H
#define REGIONFORMAT_WIDGETLIST_H

#include <MWidget>

class MLinearLayoutPolicy;
class MGridLayoutPolicy;
class MLayout;

class WidgetList : public MWidget {
    Q_OBJECT
    public:
        WidgetList(QGraphicsWidget *parent = 0);
        ~WidgetList();
        void addWidget(MWidget *wgt);
        void removeWidget(MWidget *wgt);
        void setLayoutMargins(qreal left, qreal top, qreal right, qreal bottom);

    private:
        MLayout *m_Layout;
        MLinearLayoutPolicy *m_PortraitLayoutPolicy;
        MGridLayoutPolicy *m_LandscapeLayoutPolicy;
#ifdef UNIT_TEST
        friend class Ut_WidgetList;
#endif
};

#endif

