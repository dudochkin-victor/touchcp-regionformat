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

#include <langinfo.h>

#include <QDate>
#include <QTime>
#include <MLayout>
#include <MContentItem>
#include <MContainer>
#include <MComboBox>
#include <MLabel>
#include <MLinearLayoutPolicy>
#include <MButton>
#include <MGConfItem>
#include <MStylableWidget>

#include "widgetlist.h"
#include "infoitem.h"
#include "businesslogic.h"
#include "translation.h"
#include "mainview.h"
#include "drilldownitem.h"
#include "titlewidget.h"

#include "debug.h"

#define ARABIC_LANGUAGE "ar"

MainView::MainView (QGraphicsWidget *parent)
    : DcpWidget (parent)
{
    initWidget ();
    QTimer::singleShot(0, this, SLOT(finishMainView()));
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
    MLayout               *mainLayout;
    MLinearLayoutPolicy   *layoutPolicy;


    /*
     * The mainLayout has one layout policy which is vertical.
     */
    mainLayout = new MLayout (this);
    layoutPolicy  = new MLinearLayoutPolicy (mainLayout, Qt::Vertical);
    mainLayout->setLandscapePolicy(layoutPolicy);
    mainLayout->setPortraitPolicy(layoutPolicy);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    /* Header */
    TitleWidget *headerLabel = new TitleWidget(_(AppletTitle));
    layoutPolicy->addItem(headerLabel);

    /*
     * One list for selectable items to set something and one another
     * for only informational items.
     */
    m_ButtonList = new WidgetList();
    layoutPolicy->addItem(m_ButtonList);

    MStylableWidget *sep2 = new MStylableWidget();
    sep2->setStyleName("CommonSpacer");
    layoutPolicy->addItem(sep2);

    MContainer *exampleContainer = new MContainer();
    exampleContainer->setStyleName("CommonTextFrameInverted");
    m_InfoList = new WidgetList(exampleContainer);
    exampleContainer->setCentralWidget(m_InfoList);
    exampleContainer->setHeaderVisible(false);
    layoutPolicy->addItem(exampleContainer);

    /*
     * The region content item opens a view with the list of available regions
     */
    m_RegionCItem = new DrillDownItem();
    m_RegionCItem->setObjectName("RegionCItem");
    m_ButtonList->addWidget(m_RegionCItem);
    m_ButtonList->setLayoutMargins(0, 0, 0, 0);
    connect(m_RegionCItem, SIGNAL(clicked()), 
            this, SLOT (regionCItemClickedSlot()));

    /*
     * Number Combobox to choose number format.
     * FIXME Spec expects us to show it only for relevant/arabic region. Which those are?
     */
    m_NumberCBox = new MComboBox();
    m_NumberCBox->setObjectName("NumberCBox");
    m_NumberCBox->setStyleName("CommonComboBoxInverted");

    /*
     * Information labels to show example of several details
     * of the current regional settings.
     */

    m_DateInfoItem = new InfoItem(QString("DateInfoItem"));
    m_InfoList->addWidget(m_DateInfoItem);

    m_TimeInfoItem = new InfoItem(QString("TimeInfoItem"));
    m_InfoList->addWidget(m_TimeInfoItem);

    m_NumberInfoItem = new InfoItem(QString("NumberInfoItem"));
    m_InfoList->addWidget(m_NumberInfoItem);

    m_CurrencyInfoItem = new InfoItem(QString("CurrencyInfoItem"));
    m_InfoList->addWidget(m_CurrencyInfoItem);

    MStylableWidget *sep3 = new MStylableWidget();
    sep3->setStyleName("CommonSmallSpacer");
    layoutPolicy->addItem(sep3);
}

QString MainView::title() const
{
        return QString(_(AppletTitle));
}

void MainView::finishMainView()
{

    refreshNumberFormatCBox();
    connect(m_NumberCBox, SIGNAL(activated(int)), 
            this, SLOT(numberCBoxActivatedSlot(int)));

    BusinessLogic &bl = BusinessLogic::instance();
    /*
     * Listening for changed system values
     */
    connect(&bl, SIGNAL(regionChanged()),
            this, SLOT(regionChangedSlot()));
    connect(&bl, SIGNAL(settingsChanged()),
            this, SLOT(settingsChangedSlot()));
    retranslateUi ();
    regionChangedSlot();
}

void MainView::settingsChangedSlot()
{
    lcTimeChangedSlot();
    lcNumericChangedSlot();
    lcMonetaryChangedSlot();
    lcCollateChangedSlot();
}

void MainView::regionChangedSlot()
{
    BusinessLogic &bl = BusinessLogic::instance();
    m_RegionCItem->setSubtitle(bl.getRegionName());

    /*
     * Show Number selection ComboBox only for arabic languages
     */
    if(bl.getRegion().left(2) == ARABIC_LANGUAGE){
        m_ButtonList->addWidget(m_NumberCBox);
    } else {
        m_ButtonList->removeWidget(m_NumberCBox);
    }
}

void MainView::lcTimeChangedSlot()
{
    BusinessLogic &bl = BusinessLogic::instance();
    m_DateInfoItem->setContent(bl.dateExample());
    m_TimeInfoItem->setContent(bl.timeExample());
}

void MainView::lcCollateChangedSlot()
{
}

void MainView::lcNumericChangedSlot()
{
    BusinessLogic &bl = BusinessLogic::instance();
    m_NumberInfoItem->setContent(bl.numberExample());
}

void MainView::lcMonetaryChangedSlot()
{
    BusinessLogic &bl = BusinessLogic::instance();
    m_CurrencyInfoItem->setContent(bl.currencyExample());
}

void MainView::regionCItemClickedSlot()
{
    refererToChangeWidget(View::Main);
    emit changeWidget(View::Region);
}

void MainView::numberCBoxActivatedSlot(int index)
{
    /*
     * When we clear the combo box a signal is emitted with -1 as index.  
     */
    if (index < 0) {
        qWarning("Invalid index: %d", index);
        return;
    }

    BusinessLogic &bl = BusinessLogic::instance();
    bl.setNumberFormat( index ?
            BusinessLogic::ArabicNumbers : BusinessLogic::LatinNumbers);
}

void MainView::refreshNumberFormatCBox()
{
    BusinessLogic &bl = BusinessLogic::instance();
    m_NumberCBox->clear();
    m_NumberCBox->addItems(bl.getNumberFormatEndonymList());
    if(bl.getLcNumeric().left(2) == ARABIC_LANGUAGE)
        m_NumberCBox->setCurrentIndex(BusinessLogic::ArabicNumbers);
    else
        m_NumberCBox->setCurrentIndex(BusinessLogic::LatinNumbers);
}

void MainView::retranslateUi()
{
    BusinessLogic &bl = BusinessLogic::instance();

    m_RegionCItem->setTitle(_(SelectRegion));
    m_RegionCItem->setSubtitle(bl.getRegionName());

    m_NumberCBox->setTitle(_(SelectNumber));
    refreshNumberFormatCBox();

    m_DateInfoItem->setTitle(_(DateTitle));
    m_DateInfoItem->setContent(bl.dateExample());

    m_TimeInfoItem->setTitle(_(TimeTitle));
    m_TimeInfoItem->setContent(bl.timeExample());

    m_NumberInfoItem->setTitle(_(NumberTitle));
    m_NumberInfoItem->setContent(bl.numberExample());

    m_CurrencyInfoItem->setTitle(_(CurrencyTitle));
    m_CurrencyInfoItem->setContent(bl.currencyExample());
}

