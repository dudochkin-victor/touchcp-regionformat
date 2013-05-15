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
#include <mbasiclistitem.h>
#include "stubbase.h" 

#ifndef MBASICLISTITEM_STUB
#define MBASICLISTITEM_STUB


/* Stub class.
 * With this class, it is possible to easily check the methods input parameters, and to define the
 * return values. Also it is possible to check the method call.
 *
 * Extend this, with the proxy object, as you need more and more complicated unit tests.
 */
class MBasicListItemStub : public StubBase {
    public:
        MLabel *titleLabelWidget();
        MLabel *subtitleLabelWidget();
        MImageWidget *imageWidget();
};

MLabel *MBasicListItemStub::titleLabelWidget()
{
    stubMethodEntered("titleLabelWidget");
    return stubReturnValue<MLabel*> ("titleLabelWidget");
}

MLabel *MBasicListItemStub::subtitleLabelWidget()
{
    stubMethodEntered("subtitleLabelWidget");
    return stubReturnValue<MLabel*> ("subtitleLabelWidget");
}

MImageWidget *MBasicListItemStub::imageWidget()
{
    stubMethodEntered("imageWidget");
    return stubReturnValue<MImageWidget*> ("imageWidget");
}
/*
 * Create Stub instance
 */
MBasicListItemStub defaultMBasicListItemStub;
MBasicListItemStub *MBasicListItemStubI = &defaultMBasicListItemStub;

/* Proxy object, which calls the stub.
 * Modify if needed
 */

MBasicListItem::MBasicListItem(MBasicListItem::ItemStyle, QGraphicsItem *)
{

}

MBasicListItem::~MBasicListItem()
{

}

void MBasicListItem::setImageWidget(MImageWidget *)
{

}

MImageWidget *MBasicListItem::imageWidget()
{
    return MBasicListItemStubI->imageWidget();
}

void MBasicListItem::setTitle(const QString &)
{

}

void MBasicListItem::setSubtitle(const QString &)
{

}
MLabel *MBasicListItem::subtitleLabelWidget()
{
    return MBasicListItemStubI->subtitleLabelWidget();
}

MLabel *MBasicListItem::titleLabelWidget()
{
    return MBasicListItemStubI->titleLabelWidget();
}

#endif
