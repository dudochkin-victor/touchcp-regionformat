/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */

#include "stubbase.h" 
#include "infoitem.h" 

/* Stub class.
 * With this class, it is possible to easily check the methods input parameters, and to define the
 * return values. Also it is possible to check the method call.
 *
 * Extend this, with the proxy object, as you need more and more complicated unit tests.
 */
class InfoItemStub : public StubBase {
    public:
};

/*
 * Create Stub instance
 */
InfoItemStub defaultInfoItemStub;
InfoItemStub *InfoItemStub = &defaultInfoItemStub;

/* Proxy object, which calls the stub.
 * Modify if needed
 */

InfoItem::InfoItem(const QString &, QGraphicsWidget *parent) :
    MWidget(parent),
    m_Layout(0),
    m_LayoutPolicy(0),
    m_Title(0),
    m_Content(0)
{
}

InfoItem::~InfoItem()
{
}

void InfoItem::setTitle(const QString &)
{
}

void InfoItem::setContent(const QString &)
{
}


