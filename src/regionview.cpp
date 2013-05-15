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

#include <QDebug>
#include <QSettings>
#include <QModelIndex>
#include <QItemSelectionModel>
#include <QSortFilterProxyModel>
#include <QTimer>
#include <QGraphicsLinearLayout>
#include <MList>
#include <MListFilter>
#include <MSortFilterProxyModel>
#include <MTextEdit>
#include <MApplication>
#include <MContentItem>
#include "translation.h"
#include "businesslogic.h"
#include "regionmodel.h"
#include "regionview.h"
#include "regioncell.h"
#include "titlewidget.h"

#include "debug.h"

class RegionContentItemCreator : public MAbstractCellCreator<RegionCell> {
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
MWidget *RegionContentItemCreator::createCell(const QModelIndex &index, MWidgetRecycler &recycler) const {
        Q_UNUSED(index);
        RegionCell *cell = dynamic_cast<RegionCell*>(recycler.take(RegionCell::staticMetaObject.className()));

        if (cell == NULL) {
            cell = new RegionCell();
            cell->setLayoutPosition(M::CenterPosition);
        }
        updateCell(index, cell);

        return cell;
}

void RegionContentItemCreator::updateCell(const QModelIndex& _index, MWidget * cell) const
{
    if(!cell){ /* happens to be null when shortening filter string */
        return;
    }
    if(!_index.isValid()){ /* happens to be invalid when filtered to be empty */
        return;
    }

    Q_ASSERT(cell != NULL);
    Q_ASSERT(cell->metaObject() != NULL);
    Q_ASSERT(cell->metaObject()->className() != NULL);

    RegionCell* contentItem = qobject_cast<RegionCell *>(cell);
    if (!contentItem) {
        return;
    }
    QVariant data = _index.data(Qt::DisplayRole);
    QStringList strList = data.toStringList();
    if (highlightText == "") {
        contentItem->setTitle(strList[0]);
    } else {
        QString highlightedTitle = strList[0];
        int matchingIndex = highlightedTitle.indexOf(highlightText, 0, Qt::CaseInsensitive);
        if(matchingIndex != -1) {
            highlightedTitle.insert(matchingIndex+highlightText.length(), "</b>");
            highlightedTitle.insert(matchingIndex, "<b>");
        }
        contentItem->setTitle(highlightedTitle);
    }
}

RegionView::RegionView(QGraphicsWidget *parent) :
    DcpWidget(parent),
    m_SelectedItem(-1),
    m_selectCurrentRegionCalled(false)
{
    initWidget();
}

RegionView::~RegionView()
{
}

void RegionView::initWidget()
{
    QGraphicsLinearLayout *mainLayout = new QGraphicsLinearLayout(Qt::Vertical);
    setLayout(mainLayout);

    mainLayout->setContentsMargins(0, 0, 0, 0);
    TitleWidget *titleWidget = new TitleWidget(_(RegionViewTitle));
    mainLayout->addItem(titleWidget);

    m_List = new MList();
    m_List->setContentsMargins(0, 0, 0, 0);
    m_List->setObjectName("RegionViewMList");
    m_List->setStyleName("CommonListInverted");
    RegionContentItemCreator * cellCreator = new RegionContentItemCreator();
    m_List->setCellCreator(cellCreator);

    m_List->setSelectionMode(MList::SingleSelection);

    MAbstractItemModel *itModel = &RegionModel::instance();
    itModel->setGrouped(true);

    m_SortFilterProxy = new MSortFilterProxyModel();
    m_SortFilterProxy->setSortRole(RegionModel::RegionName);
    m_SortFilterProxy->setSortCaseSensitivity(Qt::CaseInsensitive);
    m_SortFilterProxy->setFilterRole(Qt::DisplayRole);
    m_SortFilterProxy->setSourceModel(itModel);
    m_List->setItemModel(m_SortFilterProxy);

    m_List->filtering()->setEnabled(true);
    m_List->filtering()->setFilterRole(RegionModel::RegionName);
    m_List->filtering()->setFilterMode(MListFilter::FilterByApplication);

    m_List->setShowGroups(true);
    m_SortFilterProxy->sort(0, Qt::AscendingOrder);

    // Live filtering part...
    m_List->filtering()->editor()->setVisible(false);
    connect(m_List, SIGNAL(panningStarted()), this, SLOT(hideEmptyTextEdit()));
    connect(m_List->filtering(), SIGNAL(listPannedUpFromTop()), this, SLOT(filteringVKB()));
    connect(m_List->filtering()->editor(), SIGNAL(textChanged()), this, SLOT(liveFilteringTextChanged()));

    mainLayout->addItem(m_List);
    m_List->setShowGroups(true);

    connect(this, SIGNAL(displayEntered()),
            this, SLOT(displayEnteredSlot()));
    connect(this, SIGNAL(displayExited()),
            this, SLOT(displayExitedSlot()));
    connect(m_List, SIGNAL(itemClicked(QModelIndex)),
            this, SLOT(itemClickedSlot(QModelIndex)));
}

void RegionView::liveFilteringTextChanged()
{
    // With HWKB live filtering text edit is hidden when empty and shown when user enters text
    if(m_List->filtering()->editor()->text() == "" && m_List->filtering()->editor()->isOnDisplay())
        QTimer::singleShot(1500, this, SLOT(hideEmptyTextEdit()));
    else if(m_List->filtering()->editor()->text() != "" && !m_List->filtering()->editor()->isOnDisplay())
        showTextEdit(true);

    QRegExp regExp(m_List->filtering()->proxy()->filterRegExp());
    regExp.setPattern('^' + QRegExp::escape(m_List->filtering()->editor()->text()));
    m_List->filtering()->proxy()->setFilterRegExp(regExp);

    RegionContentItemCreator * cellCreator = const_cast<RegionContentItemCreator*>(static_cast<const RegionContentItemCreator*>(m_List->cellCreator()));
    // Highlighting matching live filtering text can be done by
    // passing the text to cell creator and updating visible items
    cellCreator->highlightByText(m_List->filtering()->editor()->text());
    RegionModel *model = qobject_cast<RegionModel*>(m_List->itemModel());
    if (model)
        model->updateData(m_List->firstVisibleItem(), m_List->lastVisibleItem());
    callSelectCurrentRegion();
}

void RegionView::filteringVKB()
{
    // With VKB live filtering text edit is shown when user pans the list up starting from top position
    if(!m_List->filtering()->editor()->isOnDisplay()) {
        showTextEdit(true);
        m_List->filtering()->editor()->setFocus();
    }
}

void RegionView::hideEmptyTextEdit() {
    if(m_List->filtering()->enabled() && m_List->filtering()->editor()->text() == "") {
        showTextEdit(false);
    }
}

void RegionView::showTextEdit(bool show) {
    MTextEdit *textEdit = m_List->filtering()->editor();
    QGraphicsLinearLayout *mlayout = dynamic_cast<QGraphicsLinearLayout*>(layout());
    if (!mlayout) {
        return;
    }

    /* This is a stupid solution, but I could not find other clear solution, to check whether the
     * widget is added to the layout, or not. isVisible() isOnDisplay() returns false, if the page
     * is not visible*/
    MTextEdit *layoutEdit = dynamic_cast<MTextEdit*>(mlayout->itemAt(1));

    if (show && !layoutEdit) {
        textEdit->setVisible(true);
        mlayout->insertItem(1, textEdit);
        m_List->setLayoutPosition(M::TopCenterPosition);
    } else if(!show && layoutEdit) {
        m_List->setFocus();
        textEdit->setVisible(false);
        mlayout->removeAt(1);
        textEdit->setText("");
        callSelectCurrentRegion();
    }
}


QString RegionView::title() const
{
        return QString(_(RegionViewTitle));
}

QModelIndex RegionView::getCurrentRegionIdx()
{
    QString region = BusinessLogic::instance().getRegion();
    qDebug("Region to scroll to : %s",
            qPrintable(region));
    QModelIndex idx = RegionModel::instance().getIndex(region);
    qDebug("Position of %s in the source model is %d %d %d",
            qPrintable(region),
            idx.row(), idx.column(), idx.parent().row());
    QModelIndex tridx = translateModelIndex(idx);
    qDebug("TPosition of %s in the source model is %d %d %d",
            qPrintable(region),
            tridx.row(), tridx.column(), tridx.parent().row());
    return tridx;
}

void RegionView::selectCurrentRegion()
{
    m_selectCurrentRegionCalled = false;
    QModelIndex currentRegionIdx = getCurrentRegionIdx();
    if (currentRegionIdx.isValid()) {
        disconnect(m_List, SIGNAL(itemClicked(QModelIndex)),
                this, SLOT(itemClickedSlot(QModelIndex)));
        m_List->selectItem(currentRegionIdx);
        connect(m_List, SIGNAL(itemClicked(QModelIndex)),
                this, SLOT(itemClickedSlot(QModelIndex)));
    }
}

void RegionView::callSelectCurrentRegion()
{
    if (!m_selectCurrentRegionCalled) {
        QTimer::singleShot(0, this, SLOT(selectCurrentRegion()));
        m_selectCurrentRegionCalled = true;
    }
}

void RegionView::scrollToSelected()
{
    /* We are expected to scroll to the current region. */
    QModelIndex selectedIdx = getCurrentRegionIdx();
    if (selectedIdx.isValid()) {
        m_List->scrollTo(selectedIdx , MList::PositionAtCenterHint);
    }
}

void RegionView::initListView()
{
    scrollToSelected();
    selectCurrentRegion();
}

void RegionView::displayEnteredSlot()
{
    // scrollTo works only in this delayed way
    QTimer::singleShot(0, this, SLOT(initListView()));
    m_List->setIndexDisplayMode(MList::Floating);
    m_List->setFocus();
}

void RegionView::displayExitedSlot()
{
    showTextEdit(false);
}
void RegionView::itemClickedSlot(const QModelIndex &index)
{
    QStringList region = index.data(Qt::DisplayRole).toStringList();
    if (region.count() == 2) {
        /* set selection as default regional settings */
        BusinessLogic::instance().setRegion(region[1]);
        qDebug("Selected Position of %s in the source model is %d %d %d",
                qPrintable(region[0]),
                index.row(), index.column(), index.parent().row());
    }
    emit closePage();
}

bool RegionView::back()
{
    return DcpWidget::back();
}

void RegionView::retranslateUi()
{
    showTextEdit(false);
    RegionModel::instance().retranslateList();
    displayEnteredSlot();

    TitleWidget *title = dynamic_cast<TitleWidget*>(layout()->itemAt(0));

    if (title) {
        title->setText(_(RegionViewTitle));
    }

}
QModelIndex
RegionView::translateModelIndex(const QModelIndex &regionModelIndex)
{
    const QAbstractItemModel *sourceModel = regionModelIndex.model();
    QList<const MSortFilterProxyModel *> modelChain;
    const int maxDepth = 3;
    const QAbstractItemModel *m = m_List->itemModel();
    for (int depth = 0; depth < maxDepth; ++depth) {
        if (m == sourceModel) {
            break;
        }
        const MSortFilterProxyModel *proxyModel = 
            qobject_cast<const MSortFilterProxyModel *>(m);
        if (!proxyModel) {
            break;
        }
        modelChain.append(proxyModel);
        m = proxyModel->sourceModel();
    }
    if (m != sourceModel) {
        qWarning() << "original region model not found in proxy chain";
        return QModelIndex();
    }

    if (modelChain.isEmpty()) {
        // no proxy models in the way
        return regionModelIndex;
    }

    QModelIndex translatedIndex = regionModelIndex;
    for (int i = modelChain.count() - 1; i >= 0; --i) {
         const MSortFilterProxyModel *m = modelChain[i];
         translatedIndex = m->mapFromSource(translatedIndex);
    }

    return translatedIndex;
}
