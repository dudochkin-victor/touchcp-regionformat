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

#include <QDebug>

#include <MAction>
#include <MLocale>
#include <mtheme.h>

#include <dcpwidget.h>

#include "translation.h"
#include "brief.h"
#include "regionview.h"
#include "mainview.h"
#include "applet.h"
#include "viewid.h"

#include "debug.h"

#define VIEW_ID_NONE ""
#define VIEW_ID_MAIN "Main"
#define VIEW_ID_REGION "Region"

Q_EXPORT_PLUGIN2(regionformatapplet, Applet)

Applet::Applet ():
    m_LastConstructedView(View::None),
    m_RefererPage(View::None)
{
}

void 
Applet::init ()
{
#ifdef DEBUG
    //qDebug("Installing own message handler...");
    //qInstallMsgHandler(msgHandler);
#endif

}

/* FIXME this is a hack because dcp not supports multiple pages properly. */
/*
 * When a subview is opened from dcp it should return to dcp so needs
 * referer View::None (-1). When a subview is opened from the main
 * view it should return to the main view so needs referer View::Main (>0).
 * It is the caller MainView that able to preset this value correctly.
 */
void Applet::refererToChangeWidgetSlot(View::Id ref)
{
    m_RefererPage = ref;
}

DcpWidget* Applet::constructWidget(int viewId)
{
    DcpWidget *ret = NULL;
    switch(viewId) {
        case View::Region :
            ret = new RegionView(0);
            m_LastConstructedView = View::Region;
            break;
        case View::Main :
        default:
            ret = new MainView(0);
            connect(ret, SIGNAL(refererToChangeWidget(View::Id)),
                    this, SLOT(refererToChangeWidgetSlot(View::Id)));
            m_LastConstructedView = View::Main;
            break;
    }

    return ret;
}

QString Applet::title(void) const
{
    QString msg;
    switch(m_LastConstructedView){
        case View::Region :
            msg = _(RegionViewTitle);
            break;
        case View::Main :
        default:
            msg = _(AppletTitle);
            break;
    }
    return msg;
}

QVector<MAction*> Applet::viewMenuItems(void)
{
    QVector<MAction*> vector;
    return vector;
}

DcpBrief* Applet::constructBrief(int partId)
{
    Q_UNUSED(partId);
    return new Brief();
}

int Applet::partID(const QString& part)
{
    static QMap<QString, int> parts;
    if (parts.isEmpty()){
        parts.insert(VIEW_ID_MAIN, View::Main);
        parts.insert(VIEW_ID_REGION, View::Region);
    }

    int ret = parts[part];

    if(!ret){
        qWarning("Requested part name '%s' is unknown "
                "and no partId belongs to it. Defaulting to main view.",
                qPrintable(part));
        ret = View::Main;
    }

    return ret;
}


