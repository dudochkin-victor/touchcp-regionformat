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
#ifndef REGIONFORMAT_MAINVIEW_H
#define REGIONFORMAT_MAINVIEW_H

#include <QString>
#include <QStringList>
#include <QSizePolicy>
#include <MLocale>
#include <MLabel>
#include <MComboBox>
#include <DcpWidget> 

#include "viewid.h"

class WidgetList;
class InfoItem;
class MContentItem;
class DrillDownItem;

class MainView : public DcpWidget 
{
    Q_OBJECT

public:
    MainView (QGraphicsWidget *parent = 0);
    virtual ~MainView ();

    virtual bool pagePans () const;

signals:
    void refererToChangeWidget(View::Id);

protected:
    void initWidget();
    QString title() const;

private:
    void retranslateUi();
    void refreshNumberFormatCBox();

protected slots:
    void finishMainView();
    void regionCItemClickedSlot();
    void numberCBoxActivatedSlot(int index);
    void regionChangedSlot();
    void settingsChangedSlot();
    void lcTimeChangedSlot();
    void lcCollateChangedSlot();
    void lcNumericChangedSlot();
    void lcMonetaryChangedSlot();

private:
    WidgetList *m_ButtonList;
    WidgetList *m_InfoList;

    DrillDownItem *m_RegionCItem;
    MComboBox    *m_NumberCBox;

    InfoItem *m_DateInfoItem;
    InfoItem *m_TimeInfoItem;
    InfoItem *m_NumberInfoItem;
    InfoItem *m_CurrencyInfoItem;
#ifdef UNIT_TEST
    friend class Ut_MainView;
#endif
};
#endif
