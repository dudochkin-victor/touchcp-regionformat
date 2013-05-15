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

#include <MWidgetController>
#include "stubbase.h"

/* Stub class.
 * With this class, it is possible to easily check the methods input parameters, and to define the
 * return values. Also it is possible to check the method call.
 *
 * Extend this, with the proxy object, as you need more and more complicated unit tests.
 */
class MWidgetControllerStub : public StubBase {
    public:
        void setLayoutPosition(M::Position pos);
};

void MWidgetControllerStub::setLayoutPosition(M::Position pos)
{
    QList<ParameterBase*> params;
    params.append(new Parameter<M::Position>(pos));
    stubMethodEntered("setLayoutPosition", params);
}

/*
 * Create Stub instance
 */
MWidgetControllerStub defaultMWidgetControllerStub;
MWidgetControllerStub *MWidgetControllerStub = &defaultMWidgetControllerStub;



void MWidgetController::setView(MWidgetView*) {}
MWidgetController::MWidgetController(QGraphicsItem *parent){ QGraphicsItem::setParentItem(parent); }
void MWidgetController::setObjectName (const QString&) {}
void MWidgetController::setStyleName (const QString&) {}
QSizeF MWidgetController::sizeHint(Qt::SizeHint, QSizeF const&) const {return QSizeF();}
MWidgetController::~MWidgetController() {}
void MWidgetController::setLayoutPosition(M::Position pos){ MWidgetControllerStub->setLayoutPosition(pos); }

