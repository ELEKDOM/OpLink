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

#ifndef MONITOREDOBSERVABLELOADER_H
#define MONITOREDOBSERVABLELOADER_H

#include <QString>
#include <QSharedPointer>
#include <QList>
#include "observable/remote/sessionconfhook.h"
#include "ui/monitoredobservables/pageviewbuilder/pageviewlayoutbuilder.h"
#include "ui/monitoredobservables/widget/monitoredobservablewidgetbuilder.h"
#include "olfconsole_forward.h"

///
/// \brief The MonitoredObservableLoader class
/// Loads the widgets representing the monitored observables from the XML document containing
/// the configuration to be loaded.
/// The widgets are created and assignated to a view via the 'viewsBuilder'
/// Note:
/// The creation of widgets is delegated to the builders of "technical domains"
///
class MonitoredObservableLoader : public oplink::SessionConfHook
{
public:
    MonitoredObservableLoader(OlfMonitoredObservablesController& controller,
                               PageViewLayoutBuilder *viewsBuilder);
    ~MonitoredObservableLoader() override;

public:
    QString getFamilyName(const QString& observableType);

protected:
    void browseBegin() override;
    void browseEnd() override;
    void beginObservableDeclaration(QString observableName,
                                    QString observableTitle,
                                    QString observableType,
                                    QString observableLocalisation) override;
    void endObservableDeclaration() override;
    void propertyDeclaration(QString propertyName) override;

protected:
    virtual void loadBuilders();
    void addWidgetBuilder(MonitoredObservableWidgetBuilder *newlyBuilder);

private:
    virtual MonitoredObservableWidgetCtrl *createWidget(QString observableName,
                                                        QString observableTitle,
                                                        QString observableType,
                                                        QString observableLocalisation);
private:
    OlfMonitoredObservablesController&         m_controller;
    QspPageViewLayoutBuilder                   m_viewsBuilder;
    QspMonitoredObservableWidgetCtrl           m_creatingWidget;
    QList<QspMonitoredObservableWidgetBuilder> m_widgetBuilders;
};
using QspMonitoredObservableBuilder = QSharedPointer<MonitoredObservableLoader>;
#endif // MONITOREDOBSERVABLELOADER_H
