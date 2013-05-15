/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */

#include <QDebug>

#include <MLabel>
#include <QtGui/QGraphicsLinearLayout>

#include "debug.h"

#include "infoitem.h"

InfoItem::InfoItem(const QString &name, QGraphicsWidget *parent) :
    MWidget(parent)
{
    setObjectName(name);

    QGraphicsLinearLayout* layout = new QGraphicsLinearLayout(Qt::Vertical);
    setLayout(layout);

    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);

    m_Title = new MLabel();
    m_Title->setObjectName(objectName() + "Title");
    m_Title->setStyleName("CommonTitleInverted");
    m_Title->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    m_Title->setContentsMargins(0, 0, 0, 0);
    layout->addItem(m_Title);

    m_Content = new MLabel();
    m_Content->setObjectName(objectName() + "Content");
    m_Content->setStyleName("CommonSubTitleInverted");
    m_Content->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    m_Content->setContentsMargins(0, 0, 0, 0);
    layout->addItem(m_Content);
}

InfoItem::~InfoItem()
{
}

void InfoItem::setTitle(const QString &title)
{
	m_Title->setText(title);
}

void InfoItem::setContent(const QString &content)
{
	m_Content->setText(content);
}


