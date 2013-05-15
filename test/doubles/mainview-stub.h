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
#include "mainview.h"
#include "stubbase.h" 

/* Stub class.
 * With this class, it is possible to easily check the methods input parameters, and to define the
 * return values. Also it is possible to check the method call.
 *
 * Extend this, with the proxy object, as you need more and more complicated unit tests.
 */
class MainViewStub : public StubBase {
    public:
};

/*
 * Create Strub instance
 */
MainViewStub defaultMainViewStub;
MainViewStub *MainViewStub = &defaultMainViewStub;

/* Proxy object, which calls the stub.
 * Modify if needed
 */

MainView::MainView (QGraphicsWidget *parent):
    m_ButtonList(0),
    m_InfoList(0),
    m_RegionCItem(0),
    m_NumberCBox(0),
    m_DateInfoItem(0),
    m_TimeInfoItem(0),
    m_NumberInfoItem(0),
    m_CurrencyInfoItem(0)
{
    Q_UNUSED(parent);
}

MainView::~MainView ()
{
}


bool
MainView::pagePans () const
{
    return false;
}

void 
MainView::initWidget()
{
}

void MainView::finishMainView()
{

}

QString MainView::title() const
{
        return QString();
}

void MainView::regionChangedSlot()
{
}

void MainView::settingsChangedSlot()
{
}
void MainView::lcTimeChangedSlot()
{
}

void MainView::lcCollateChangedSlot()
{
}

void MainView::lcNumericChangedSlot()
{
}

void MainView::lcMonetaryChangedSlot()
{
}

void MainView::regionCItemClickedSlot()
{
}

void MainView::numberCBoxActivatedSlot(int index)
{
    Q_UNUSED(index);
}

void MainView::refreshNumberFormatCBox()
{
}

void MainView::retranslateUi()
{
}

