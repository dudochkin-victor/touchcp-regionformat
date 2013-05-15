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
#include <MList>
#include "stubbase.h"

/* Stub class.
 * With this class, it is possible to easily check the methods input parameters, and to define the
 * return values. Also it is possible to check the method call.
 *
 * Extend this, with the proxy object, as you need more and more complicated unit tests.
 */
class MListStub : public StubBase {
    public:
        void scrollTo(const QModelIndex& index, MList::ScrollHint hint);
        void selectItem(const QModelIndex& index);
        QItemSelectionModel* selectionModel() const;
        QAbstractItemModel* itemModel();
        const QModelIndex firstVisibleItem() const;
        const QModelIndex lastVisibleItem() const;
};

void
MListStub::scrollTo(const QModelIndex& index, MList::ScrollHint hint)
{
    QList<ParameterBase*> params;
    params.append(new Parameter<const QModelIndex>(index));
    params.append(new Parameter<MList::ScrollHint>(hint));
    stubMethodEntered("scrollTo", params);
}

void
MListStub::selectItem(const QModelIndex& index)
{
    QList<ParameterBase*> params;
    params.append(new Parameter<QModelIndex>(index));
    stubMethodEntered("selectItem", params);
}

QAbstractItemModel*
MListStub::itemModel()
{
    stubMethodEntered("itemModel");
    return stubReturnValue<QAbstractItemModel*> ("itemModel");
}

QItemSelectionModel*
MListStub::selectionModel() const
{
    stubMethodEntered("selectionModel");
    return stubReturnValue<QItemSelectionModel*> ("selectionModel");
}

const QModelIndex
MListStub::firstVisibleItem() const
{
    stubMethodEntered("firstVisibleItem");
    return stubReturnValue<const QModelIndex> ("firstVisibleItem");
}

const QModelIndex
MListStub::lastVisibleItem() const
{
    stubMethodEntered("lastVisibleItem");
    return stubReturnValue<const QModelIndex> ("lastVisibleItem");
}

/*
 * Create Stub instance
 */
MListStub defaultMListStub;
MListStub *MListStub = &defaultMListStub;

/* Proxy object, which calls the stub.
 * Modify if needed
 */

MList::MList(QGraphicsItem*)
{
}

MList::~MList()
{
}
static MCellCreator* cCreator;

void
MList::setCellCreator(MCellCreator *Creator)
{
    cCreator = Creator;
}

const MCellCreator *
MList::cellCreator() const
{
    return cCreator;
}

void
MList::setHeaderCreator(MCellCreator *)
{
}

void
MList::setSelectionMode(MList::SelectionMode)
{
}

void
MList::setItemModel(QAbstractItemModel*)
{
}

QAbstractItemModel*
MList::itemModel() const
{
    return MListStub->itemModel();
}

void
MList::setShowGroups(bool)
{
}

void MList::setIndexDisplayMode (MList::DisplayMode displayMode)
{
}

void
MList::scrollTo(const QModelIndex& index, MList::ScrollHint hint)
{
    MListStub->scrollTo(index, hint);
}

void
MList::selectItem(const QModelIndex& index)
{
    MListStub->selectItem(index);
}

MListFilter*
MList::filtering() const
{
    return new MListFilter();
}
QItemSelectionModel*
MList::selectionModel() const
{
    return MListStub->selectionModel();
}

const QModelIndex
MList::firstVisibleItem() const
{
    return MListStub->firstVisibleItem();
}

const QModelIndex
MList::lastVisibleItem() const
{
    return MListStub->lastVisibleItem();
}
