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

#ifndef REGIONFORMAT_REGIONVIEW_H
#define REGIONFORMAT_REGIONVIEW_H

#include <DcpWidget>

class MList;
class QModelIndex;
class QItemSelectionModel;
class MSortFilterProxyModel;

class RegionView : public DcpWidget {
    Q_OBJECT

    public:
        RegionView(QGraphicsWidget *parent = 0);
        virtual ~RegionView();

    public slots:
        bool back();
    // For live filtering
        void liveFilteringTextChanged();
        void filteringVKB();
        void hideEmptyTextEdit();
 
    protected:
        void initWidget();
        QString title() const;
        virtual void retranslateUi();
    private:
        void showTextEdit(bool show);
        void scrollToSelected();
        QModelIndex getCurrentRegionIdx();
        QModelIndex translateModelIndex(const QModelIndex &regionModelIndex);
        void callSelectCurrentRegion();


    private slots:
        void displayEnteredSlot();
        void displayExitedSlot();
        void initListView();
        void itemClickedSlot(const QModelIndex &index);
        void selectCurrentRegion();

    private:
        MList *m_List;
        int m_SelectedItem;
        MSortFilterProxyModel *m_SortFilterProxy;
        bool m_selectCurrentRegionCalled;

#ifdef UNIT_TEST
        friend class Ut_RegionView;
#endif
};

#endif


