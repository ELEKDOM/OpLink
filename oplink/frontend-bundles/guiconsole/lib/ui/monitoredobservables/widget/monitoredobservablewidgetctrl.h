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

#ifndef MONITOREDOBSERVABLEWIDGETCTRL_H
#define MONITOREDOBSERVABLEWIDGETCTRL_H

#include "olfconsole_forward.h"

#include <QObject>
#include <QString>
#include <QVariant>
#include <QHash>
#include <QSharedPointer>

class MonitoredObservableWidgetCtrl : public QObject
{
    Q_OBJECT

public:
    explicit MonitoredObservableWidgetCtrl(QString observableName,
                                  QString observableTitle,
                                  QString observableType,
                                  QString observableLocalisation,
                                  QObject *parent = nullptr);
    virtual ~MonitoredObservableWidgetCtrl();

public:
    virtual void createStates() = 0;
    const QString& observableType() {return m_observableType;}
    const QString& observableLocalisation() {return m_observableLocalisation;}
    MonitoredObservableWidgetView *createView(quint8 layoutViewType);
    void updateStateValue(const QString &propertyName,
                          const QVariant &value);
    const QString& name() {return m_observableName;}

public slots:
    virtual void onButtonCmdClicked(QString cmdName) = 0;

signals:
    void execCmd(QString cmd);

protected:
    void addState(const QString &propertyName);
    virtual MonitoredObservableWidgetView *_createView(quint8 layoutViewType) = 0;
    virtual void _updateStateValue(const QString &propertyName,
                                   const QVariant &value) = 0;
    MonitoredObservableWidgetView *view() {return m_view;}
    const QString& observableName(){return m_observableName;}

protected:
    virtual void extendedConnect();

private:
    QString                        m_observableName;
    QString                        m_observableTitle;
    QString                        m_observableType;
    QString                        m_observableLocalisation;
    QHash<QString,bool>            m_monitoredStates;  // only to retrieve states by name !
    MonitoredObservableWidgetView *m_view;
};
using QspMonitoredObservableWidgetCtrl = QSharedPointer<MonitoredObservableWidgetCtrl>;
#endif // MONITOREDOBSERVABLEWIDGETCTRL_H
