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
#include "mgconfitem-fake.h"
#include "gconfitemprivate-fake.h"
#include "businesslogic.h"
#include "stubbase.h" 

/* Stub class.
 * With this class, it is possible to easily check the methods input parameters, and to define the
 * return values. Also it is possible to check the method call.
 *
 * Extend this, with the proxy object, as you need more and more complicated unit tests.
 */
class BusinessLogicStub : public StubBase {
    public:
        QString getRegionName() const;
        QString getRegion() const;
        void setRegion(const QString &reg);
};

QString BusinessLogicStub::getRegionName() const
{
    stubMethodEntered ("getRegionName");
    return stubReturnValue<QString> ("getRegionName");
}

QString BusinessLogicStub::getRegion() const
{
    stubMethodEntered ("getRegion");
    return stubReturnValue<QString> ("getRegion");
}

void BusinessLogicStub::setRegion(const QString &reg)
{
    QList<ParameterBase*> params;
    params.append(new Parameter<QString>(reg));
    stubMethodEntered("setRegion", params);
}

/*
 * Create Stub instance
 */
BusinessLogicStub defaultBlogicStub;
BusinessLogicStub *BlogicStub = &defaultBlogicStub;

namespace GConfKey
{
    const QString Region("/meegotouch/i18n/region");
    const QString UserRegion("/meegotouch/i18n/userselectedregion");
    const QString LcTime("/meegotouch/i18n/lc_time");
    const QString LcCollate("/meegotouch/i18n/lc_collate");
    const QString LcNumeric("/meegotouch/i18n/lc_numeric");
    const QString LcMonetary("/meegotouch/i18n/lc_monetary");
}

/* Proxy object, which calls the stub.
 * Modify if needed
 */

BusinessLogic::BusinessLogic () :
    m_RegionGConfItem(GConfKey::Region),
    m_UserRegionGConfItem(GConfKey::UserRegion),
    m_LcTimeGConfItem(GConfKey::LcTime),
    m_LcCollateGConfItem(GConfKey::LcCollate),
    m_LcNumericGConfItem(GConfKey::LcNumeric),
    m_LcMonetaryGConfItem(GConfKey::LcMonetary)
{
}

BusinessLogic::~BusinessLogic()
{
}

BusinessLogic& BusinessLogic::instance()
{
    static BusinessLogic _instance;
    return _instance;
}

void BusinessLogic::setRegion(const QString &reg)
{
    BlogicStub->setRegion(reg);
}

QString BusinessLogic::getRegionName() const
{
    return BlogicStub->getRegionName();
}

void BusinessLogic::regionChangedSlot()
{
}

void BusinessLogic::settingsChangedSlot()
{
}

void BusinessLogic::timeoutSlot()
{

}

QString BusinessLogic::currencyExample(double) const
{
    return QString();
}

QString BusinessLogic::numberExample(double) const
{
    return QString();
}

QString BusinessLogic::dateExample() const
{
    return QString();
}

QString BusinessLogic::timeExample() const
{
    return QString();
}

QStringList BusinessLogic::getNumberFormatEndonymList() const
{
    return QStringList();
}

QString BusinessLogic::getLcNumeric() const
{
    return QString();
}

QString BusinessLogic::getRegion() const
{
    return BlogicStub->getRegion();
}
void BusinessLogic::setNumberFormat(NumberFormat )
{
}
