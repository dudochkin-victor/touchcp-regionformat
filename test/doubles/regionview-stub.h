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
#include "regionview.h" 
#include "stubbase.h" 

/* Stub class.
 * With this class, it is possible to easily check the methods input parameters, and to define the
 * return values. Also it is possible to check the method call.
 *
 * Extend this, with the proxy object, as you need more and more complicated unit tests.
 */
class RegionViewStub : public StubBase {
    public:
        QString title() const;
};

QString RegionViewStub::title() const
{
    stubMethodEntered("title");
    return stubReturnValue<QString> ("title");
}
/*
 * Create Strub instance
 */
RegionViewStub defaultRegionViewStub;
RegionViewStub *regionViewStub = &defaultRegionViewStub;

/* Proxy object, which calls the stub.
 * Modify if needed
 */

RegionView::RegionView(QGraphicsWidget *parent):
    m_List(0),
    m_SelectedItem(0),
    m_SortFilterProxy(0)
{
    Q_UNUSED(parent);
}

RegionView::~RegionView()
{
}

QString RegionView::title() const
{
        return regionViewStub->title();
}

bool RegionView::back()
{
    return true;
}

void RegionView::itemClickedSlot(const QModelIndex &index)
{
    Q_UNUSED(index);
}
void RegionView::displayEnteredSlot()
{
}
void RegionView::displayExitedSlot()
{
}
void RegionView::liveFilteringTextChanged()
{

}

void RegionView::filteringVKB()
{

}

void RegionView::scrollToSelected()
{

}
void RegionView::hideEmptyTextEdit() {
}

void RegionView::retranslateUi()
{

}

QModelIndex RegionView::getCurrentRegionIdx()
{
    return QModelIndex();
}

void RegionView::selectCurrentRegion()
{

}

void RegionView::initListView()
{

}

void RegionView::callSelectCurrentRegion()
{

}

