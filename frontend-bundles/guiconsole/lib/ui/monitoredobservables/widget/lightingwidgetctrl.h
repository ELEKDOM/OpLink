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


#ifndef LIGHTINGWIDGETCTRL_H
#define LIGHTINGWIDGETCTRL_H

#include <QPixmap>
#include "monitoredobservablewidgetctrl.h"

namespace elekdom
{
namespace oplink
{
namespace frontend
{
namespace guiconsole
{
namespace monitoredobservable
{
namespace widget
{

class LightingWidgetCtrl : public MonitoredObservableWidgetCtrl
{
protected:
    static QString stateName() {return QStringLiteral("state");}

public:
    LightingWidgetCtrl(QString observableName,
                       QString observableTitle,
                       QString observableType,
                       QString observableLocalisation);
    ~LightingWidgetCtrl() override;

protected:
    MonitoredObservableWidgetView *_createView(quint8 layoutViewType) override;
    void _updateStateValue(const QString &propertyName,
                           const QVariant &value) override;
    void onButtonCmdClicked(QString cmdName) override;

private:
    QPixmap m_lightOn;
    QPixmap m_lightOff;
};

} //namespace widget
} //namespace monitoredobservable
} //namespace guiconsole
} //namespace frontend
} //namespace oplink
} //namespace elekdom
#endif // LIGHTINGWIDGETCTRL_H
