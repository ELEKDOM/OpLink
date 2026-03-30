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

#ifndef MONITOREDOBSERVABLEWIDGETVIEW_H
#define MONITOREDOBSERVABLEWIDGETVIEW_H

#include <QWidget>

class MonitoredObservableWidgetView : public QWidget
{
    Q_OBJECT

public:
    explicit MonitoredObservableWidgetView(QWidget *parent = nullptr);
    ~MonitoredObservableWidgetView() override;

public:
    virtual void setTitle(const QString& title);
    virtual void setImg(const QPixmap& img, const QString& propertyName);
    virtual void enableCmdButton(bool enable, const QString& cmdName);
    virtual void setMeasVal(quint32 val);
    virtual void setMeasUnit(const QString& unit);
    virtual void setVal(quint8 idx, double val);

signals:
    void cmdButtonClicked(QString cmdName);
};

class ButtonName
{
public:

    static QString on() {return QStringLiteral("on");}
    static QString off() {return QStringLiteral("off");}
    static QString power() {return QStringLiteral("power");}
    static QString energy() {return QStringLiteral("energy");}
    static QString comfort() {return QStringLiteral("comfort");}
    static QString comfort1() {return QStringLiteral("comfort1");}
    static QString comfort2() {return QStringLiteral("comfort2");}
    static QString eco() {return QStringLiteral("eco");}
    static QString nofrost() {return QStringLiteral("nofrost");}
};

#endif // MONITOREDOBSERVABLEWIDGETVIEW_H
