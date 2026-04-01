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

#ifndef HEATING6MWIDGETCTRL_H
#define HEATING6MWIDGETCTRL_H

#include <QPixmap>
#include "ui/monitoredobservables/widget/monitoredobservablewidgetctrl.h"

class Heating6mWidgetCtrl : public MonitoredObservableWidgetCtrl
{
protected:
    static QString heatingModeName() {return QStringLiteral("heating_mode");}
    static QString heatingMeasName() {return QStringLiteral("heating_m_value");}
    static QString heatingUnitName() {return QStringLiteral("heating_u_value");}

public:
    Heating6mWidgetCtrl(QString observableName,
                        QString observableTitle,
                        QString observableType,
                        QString observableLocalisation);
    ~Heating6mWidgetCtrl() override;

protected:
    MonitoredObservableWidgetView *_createView(quint8 layoutViewType) override;
    void _updateStateValue(const QString &propertyName,
                           const QVariant &value) override;
    void onButtonCmdClicked(QString cmdName) override;

private:
    QPixmap m_pwmComfort;
    QPixmap m_pwmComfort_1;
    QPixmap m_pwmComfort_2;
    QPixmap m_pwmeco;
    QPixmap m_pwmNoFrost;
    QPixmap m_pwmStop;
};

#endif // HEATING6MWIDGETCTRL_H
