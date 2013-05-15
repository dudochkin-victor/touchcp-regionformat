/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */

#include <QtTest/QtTest>
#include <QObject>
#include <QtGui/QGraphicsLinearLayout>
#include <MLabel>
#include "debug.h" 
#include "infoitem.h"
#include "mabstractlayoutpolicy-fake.h" 
#include "mlayout-fake.h" 
#include "mlinearlayoutpolicy-fake.h" 
#include "mwidgetcontroller-fake.h" 
#include "mcontainer-fake.h" 

void QGraphicsLinearLayout::insertItem(int, QGraphicsLayoutItem *)
{
}

MLabel::MLabel(QGraphicsItem *, MLabelModel *)
{
}

void MLinearLayoutPolicy::setSpacing(qreal)
{

}
class Ut_InfoItem : public QObject
{
    public:
        Q_OBJECT;

    private slots:
        void initTestCase();
        void cleanupTestCase();
        void init();
        void cleanup();

    private:
        InfoItem *m_infoitem;
};

void Ut_InfoItem::initTestCase()
{
    /* Simple crash test.... */
    m_infoitem = new InfoItem("test");
    QVERIFY(m_infoitem);
    QVERIFY(m_infoitem->m_Title);
    QVERIFY(m_infoitem->m_Content);
}

void Ut_InfoItem::cleanupTestCase()
{
    delete m_infoitem;
}


void Ut_InfoItem::cleanup()
{
}

void Ut_InfoItem::init()
{
}

QTEST_APPLESS_MAIN(Ut_InfoItem);

#include ".moc/ut_infoitem.moc"
