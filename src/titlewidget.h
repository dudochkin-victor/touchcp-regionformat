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

#ifndef TITLEWIDGET_H
#define TITLEWIDGET_H

#include <MStylableWidget>
#include <MLabel>
#include <QtGui/QGraphicsLinearLayout>

class TitleWidget: public MStylableWidget
{
public:
    TitleWidget(QString const &text, QGraphicsItem *parent = NULL) :
        MStylableWidget(parent)
    {
        setStyleName("CommonXLargeHeaderPanelInverted");
        QGraphicsLinearLayout* layout = new QGraphicsLinearLayout(Qt::Vertical);
        layout->setContentsMargins(0, 0, 0, 0);
        m_titleLabel = new MLabel(text);
        m_titleLabel->setStyleName("CommonXLargeHeaderInverted");
        layout->addItem (m_titleLabel);
        MStylableWidget *sep = new MStylableWidget();
        sep->setStyleName("CommonSmallSpacer");
        layout->addItem(sep);
        setLayout(layout);
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    }
    void setText(QString const &text)
    {
        m_titleLabel->setText(text);
    }

protected:
    friend class Ut_TitleWidget;
private:
    MLabel *m_titleLabel;
};

#endif
