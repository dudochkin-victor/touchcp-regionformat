/* -*- Mode: C; indent-tabs-mode: s; c-basic-offset: 4; tab-width: 4 -*- */
/* vim:set et ai sw=4 ts=4 sts=4: tw=80 cino="(0,W2s,i2s,t0,l1,:0" */

#ifndef REGIONFORMAT_INFOITEM_H
#define REGIONFORMAT_INFOITEM_H

#include <QString>

#include <MWidget>

class MLinearLayoutPolicy;
class MLayout;
class MLabel;

class InfoItem : public MWidget {
    Q_OBJECT
    public:
        InfoItem(const QString &name, QGraphicsWidget *parent = 0);
        ~InfoItem();
	void setTitle(const QString &title);
	void setContent(const QString &content);

    private:
        MLayout *m_Layout;
        MLinearLayoutPolicy *m_LayoutPolicy;

    	MLabel *m_Title;
	    MLabel *m_Content;
#ifdef UNIT_TEST
        friend class Ut_InfoItem;
#endif
};

#endif


