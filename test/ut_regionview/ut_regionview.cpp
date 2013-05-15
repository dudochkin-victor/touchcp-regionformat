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

#include <QtTest/QtTest>
#include <QObject>
#include <QtGui/QGraphicsLinearLayout>
#include <MList>
#include <MContentItem>
#include <MListFilter>
#include <MTextEdit>
#include <MStylableWidget>
#include <MSortFilterProxyModel>
#include "regionmodel-stub.h"
#include "businesslogic.h" 
#include "businesslogic-stub.h"
#include "mlist-fake.h" 
#include "mcontentitem-fake.h" 
#include "mabstractlayoutpolicy-fake.h" 
#include "mlayout-fake.h" 
#include "mlinearlayoutpolicy-fake.h" 
#include "mwidgetcontroller-fake.h" 
#include "regionview.h"
#include "translation.h"
#include "testtablemodel.h"
#include "regioncell.h" 

MStylableWidget::MStylableWidget (QGraphicsItem *)
{

}
void QGraphicsLayoutItem::setSizePolicy (QSizePolicy::Policy, QSizePolicy::Policy, QSizePolicy::ControlType)
{

}

void QGraphicsLinearLayout::insertItem (int, QGraphicsLayoutItem *)
{

}

namespace TextId {
    const char *RegionViewTitle = "RViewTitle";
}


MListFilter::MListFilter(MList*):
    list(0),
    filterEditor(0),
    filterProxy(0),
    filteringEnabled(false),
    d_ptr(0)
{
}

MListFilter::~MListFilter(){
}
void
MListFilter::setEnabled(bool)
{
}
static bool mlistFilterEnabled;
bool
MListFilter::enabled()
{
    return mlistFilterEnabled;
}
void
MListFilter::setFilterRole(int)
{
}

MSortFilterProxyModel *MListFilter::proxy() const
{
    static MSortFilterProxyModel *proxym = new MSortFilterProxyModel();
    return proxym;
}

static bool mWidgetVisible;
void MWidget::setVisible (bool visi) { mWidgetVisible = visi;}

static bool mWidgetOnDisplay;
bool MWidget::isOnDisplay() const
{
    return mWidgetOnDisplay;
}

class Ut_RegionView : public QObject
{
    public:
        Q_OBJECT;

    private slots:
        void initTestCase();
        void cleanupTestCase();
        void init();
        void cleanup();

        void testTitle();
        void testLiveFilteringTextChanged();
        void testFilteringVKB();
        void testHideEmptyTextEdit();
        void testShowTextEdit();
        void testScrollToSelected();
        void testDisplayEnteredSlot();
        void testItemClickedSlot();
        void testBack();
        void testTranslateModelIndex();
        void testUpdateCell();
        void testCreateCell();

    private:
        RegionView *m_rview;
};

void Ut_RegionView::initTestCase()
{
    m_rview = new RegionView();
    QVERIFY(m_rview);
}

void Ut_RegionView::cleanupTestCase()
{
    delete m_rview;
}


void Ut_RegionView::cleanup()
{
}

void Ut_RegionView::init()
{
    MListStub->stubReset();
    BlogicStub->stubReset();
    RegionModelStub->stubReset();
    MWidgetControllerStub->stubReset();
}

void Ut_RegionView::testTitle()
{
    QCOMPARE(m_rview->title(), _(RegionViewTitle));
}

static QString textEditText;

QString MTextEdit::text() const
{
    return textEditText;
}

class RegionContentItemCreator : public MAbstractCellCreator<MContentItem> {
    public:
        MWidget *createCell(const QModelIndex &index, MWidgetRecycler &recycler) const;
        void updateCell(const QModelIndex& _index, MWidget * cell) const __attribute__ ((no_instrument_function));
        void highlightByText(QString text) {
            highlightText = text;
        }
    private:
        QString highlightText;
        friend class Ut_RegionView;
};

void Ut_RegionView::testLiveFilteringTextChanged()
{
    TestTableModel tmodel;
    const QModelIndex findex = tmodel.index(0, 0);
    const QModelIndex lindex = tmodel.index(9, 0);
    const RegionContentItemCreator * cellCreator = static_cast<const RegionContentItemCreator*>(m_rview->m_List->cellCreator());

    MListStub->stubSetReturnValue<const QModelIndex> ("firstVisibleItem", findex);
    MListStub->stubSetReturnValue<const QModelIndex> ("lastVisibleItem", lindex);

    textEditText = "";
    mWidgetOnDisplay = true;
    m_rview->liveFilteringTextChanged();
    QCOMPARE(cellCreator->highlightText, QString(""));

    textEditText = "SubiDubiSalala";
    mWidgetOnDisplay = false;
    m_rview->liveFilteringTextChanged();
   QCOMPARE(cellCreator->highlightText, QString("SubiDubiSalala"));

    textEditText = "SubiDubiSalala";
    mWidgetOnDisplay = true;
    m_rview->liveFilteringTextChanged();
   QCOMPARE(cellCreator->highlightText, QString("SubiDubiSalala"));
}


void Ut_RegionView::testFilteringVKB()
{
    mWidgetOnDisplay = true;
    textEditText = "";

    m_rview->filteringVKB();
    QCOMPARE(mWidgetVisible, true);
}

void Ut_RegionView::testHideEmptyTextEdit()
{
    textEditText = "";
    mlistFilterEnabled = true;
    mWidgetOnDisplay = false;

    m_rview->hideEmptyTextEdit();
}

void Ut_RegionView::testShowTextEdit()
{
    textEditText = "";
    mlistFilterEnabled = true;
    mWidgetOnDisplay = false;

    m_rview->showTextEdit(true);
    QCOMPARE(MWidgetControllerStub->stubLastCallTo("setLayoutPosition").parameter<M::Position> (0),
            M::TopCenterPosition);

}
void Ut_RegionView::testItemClickedSlot()
{
    QSignalSpy sspy(m_rview, SIGNAL(closePage()));
    TestTableModel tmodel;
    QModelIndex indexref = tmodel.index(0, 0, tmodel.index(0, 0));

    m_rview->itemClickedSlot(indexref);

    QCOMPARE(BlogicStub->stubLastCallTo("setRegion").parameter<QString>
            (0), QString("CurrentRegion"));

    QCOMPARE(sspy.count(), 1);
}

void Ut_RegionView::testScrollToSelected()
{
    TestTableModel tmodel;
    QModelIndex indexref = tmodel.index(0, 0, tmodel.index(0, 0));

    /* Setup the stubs */
    BlogicStub->stubSetReturnValue<QString> ("getRegion", "CurrentRegion");
    RegionModelStub->stubSetReturnValue<QModelIndex> ("getIndex", indexref);
    MListStub->stubSetReturnValue<QAbstractItemModel*> ("itemModel", &tmodel);

    m_rview->scrollToSelected();
    QCOMPARE(MListStub->stubLastCallTo("scrollTo").parameter<const QModelIndex> (0),
            indexref);
    QCOMPARE(MListStub->stubLastCallTo("scrollTo").parameter<MList::ScrollHint>
            (1), MList::PositionAtCenterHint);
/*    QCOMPARE(MListStub->stubLastCallTo("selectItem").parameter<QModelIndex> (0),
            indexref);*/
    QCOMPARE(RegionModelStub->stubLastCallTo("getIndex").parameter<QString> (0),
            QString("CurrentRegion"));

}

void Ut_RegionView::testDisplayEnteredSlot()
{
    m_rview->displayEnteredSlot();
}

void Ut_RegionView::testBack()
{
}

void Ut_RegionView::testTranslateModelIndex()
{
    TestTableModel tmodel;
    QModelIndex indexref = tmodel.index(0, 0, tmodel.index(0, 0));

    QModelIndex iRet = m_rview->translateModelIndex(indexref);
    QCOMPARE(iRet, QModelIndex());

    MSortFilterProxyModel *m_SortFilterProxy = new MSortFilterProxyModel();
    m_SortFilterProxy->setSourceModel(&tmodel);
    MListStub->stubSetReturnValue<QAbstractItemModel*> ("itemModel", m_SortFilterProxy);
    iRet = m_rview->translateModelIndex(indexref);
    QCOMPARE(iRet, m_SortFilterProxy->mapFromSource(indexref));
}

void Ut_RegionView::testUpdateCell()
{
    TestTableModel tmodel;
    const QModelIndex findex = tmodel.index(0, 0);
    RegionContentItemCreator * cellCreator = const_cast<RegionContentItemCreator*>(static_cast<const RegionContentItemCreator*>(m_rview->m_List->cellCreator()));
    RegionCell cell;

    cellCreator->highlightText = QString("");
    cellCreator->updateCell(findex, &cell);
    QCOMPARE(cell.title(), QString("CurrentEndonym"));

    cellCreator->highlightText = QString("ndo");
    cellCreator->updateCell(findex, &cell);
    QCOMPARE(cell.title(), QString("CurrentE<b>ndo</b>nym"));
}

void Ut_RegionView::testCreateCell()
{
    TestTableModel tmodel;
    const QModelIndex findex = tmodel.index(0, 0);
    RegionContentItemCreator * cellCreator = const_cast<RegionContentItemCreator*>(static_cast<const RegionContentItemCreator*>(m_rview->m_List->cellCreator()));
    MWidgetRecycler *rec = MWidgetRecycler::instance();
    MWidget *cell = cellCreator->createCell(findex, *rec);

    QVERIFY(cell);
    QVERIFY(dynamic_cast<RegionCell*> (cell));

}

QTEST_APPLESS_MAIN(Ut_RegionView);

#include ".moc/ut_regionview.moc"
