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

#ifndef MIMAGEWIDGET_STUB
#define MIMAGEWIDGET_STUB

#include <MImageWidget>
#include <stubbase.h>
#include <mwidgetcontroller-fake.h>


// 1. DECLARE STUB
class MImageWidgetStub : public StubBase
{
public:
    virtual void MImageWidgetStubConstructor(QGraphicsItem *parent);
    virtual void MImageWidgetStubDestructor();
   virtual void setAspectRatioMode(Qt::AspectRatioMode mode);
    virtual void setImage(const QImage &image);
    virtual void setPixmap(const QPixmap &pixmap);

    MImageWidgetPrivate *d_ptr ;
};

// 2. IMPLEMENT STUB
void MImageWidgetStub::MImageWidgetStubConstructor(QGraphicsItem *parent)
{
    Q_UNUSED(parent);

}
void MImageWidgetStub::MImageWidgetStubDestructor()
{
}

void MImageWidgetStub::setAspectRatioMode(Qt::AspectRatioMode mode)
{
    QList<ParameterBase *> params;
    params.append(new Parameter<Qt::AspectRatioMode>(mode));
    stubMethodEntered("setAspectRatioMode", params);
}

void MImageWidgetStub::setImage(const QImage &image)
{
    QList<ParameterBase *> params;
    params.append(new Parameter<QImage>(image));
    stubMethodEntered("setImage", params);
}

void MImageWidgetStub::setPixmap(const QPixmap &pixmap)
{
    QList<ParameterBase *> params;
    params.append(new Parameter<QPixmap>(pixmap));
    stubMethodEntered("setPixmap", params);
}


// 3. CREATE A STUB INSTANCE
MImageWidgetStub gDefaultMImageWidgetStub;
MImageWidgetStub *gMImageWidgetStub = &gDefaultMImageWidgetStub;


// 4. CREATE A PROXY WHICH CALLS THE STUB
MImageWidget::MImageWidget(QGraphicsItem *parent)
{
    gMImageWidgetStub->MImageWidgetStubConstructor(parent);
}

MImageWidget::MImageWidget(const QString &imageName, QGraphicsItem *parent)
{
    Q_UNUSED(imageName);
    gMImageWidgetStub->MImageWidgetStubConstructor(parent);
}

MImageWidget::MImageWidget(const QImage *image, QGraphicsItem *parent)
{
    Q_UNUSED(image);
    gMImageWidgetStub->MImageWidgetStubConstructor(parent);
}

MImageWidget::MImageWidget(const QPixmap *pixmap, QGraphicsItem *parent)
{
    Q_UNUSED(pixmap);
    gMImageWidgetStub->MImageWidgetStubConstructor(parent);
}

MImageWidget::~MImageWidget()
{
    gMImageWidgetStub->MImageWidgetStubDestructor();
}

void MImageWidget::setAspectRatioMode(Qt::AspectRatioMode mode)
{
    gMImageWidgetStub->setAspectRatioMode(mode);
}

void MImageWidget::setImage(const QImage &image)
{
    gMImageWidgetStub->setImage(image);
}

void MImageWidget::setImage(const QString &)
{
}

void MImageWidget::setPixmap(const QPixmap &pixmap)
{
    gMImageWidgetStub->setPixmap(pixmap);
}


#endif
