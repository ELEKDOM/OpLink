// Copyright (C) 2025 ELEKDOM Christophe Mars c.mars@elekdom.fr
// 
// This file is part of OpLink.
// 
// OpLink is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// OpLink is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with PlugFrame. If not, see <https://www.gnu.org/licenses/>.
//

#ifndef SMARTPLUGWIDGETCTRL_H
#define SMARTPLUGWIDGETCTRL_H

#include <QPixmap>
#include "monitoredobservablewidgetctrl.h"

class SmartPlugWidgetCtrl : public MonitoredObservableWidgetCtrl
{
protected:
    static QString output1Name() {return QStringLiteral("output1");}
    static QString measName() {return QStringLiteral("m_value");}
    static QString unitName() {return QStringLiteral("u_value");}

public:
    SmartPlugWidgetCtrl(QString observableName,
                        QString observableTitle,
                        QString observableType,
                        QString observableLocalisation);
    ~SmartPlugWidgetCtrl() override;

protected:
    MonitoredObservableWidgetView *_createView(quint8 layoutViewType) override;
    void _updateStateValue(const QString &propertyName,
                           const QVariant &value) override;
    void onButtonCmdClicked(QString cmdName) override;

private:
    QPixmap m_plugOn;
    QPixmap m_plugOff;
};

#endif // SMARTPLUGWIDGETCTRL_H
