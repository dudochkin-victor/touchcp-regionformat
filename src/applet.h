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

#ifndef REGIONFORMAT_APPLET_H
#define REGIONFORMAT_APPLET_H

#include "dcpappletif.h"
#include <QObject>

#include "viewid.h"

class DcpWidget;
class MAction;

class Applet : public QObject, public DcpAppletIf 
{
	Q_OBJECT
	Q_INTERFACES(DcpAppletIf)

public:
    Applet ();
    virtual void                init();
    virtual DcpWidget*          constructWidget(int viewId);
    virtual QString             title() const;
    virtual QVector<MAction*>   viewMenuItems();
    virtual DcpBrief*           constructBrief(int partId);
    virtual int                 partID(const QString& part);

private slots:
    void refererToChangeWidgetSlot(View::Id);
private:
    View::Id m_LastConstructedView;
    View::Id m_RefererPage;
#ifdef UNIT_TEST
    friend class Ut_Applet;
#endif

};

#endif

