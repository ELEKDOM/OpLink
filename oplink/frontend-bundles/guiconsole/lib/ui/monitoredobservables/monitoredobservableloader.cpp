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

#include "monitoredobservableloader.h"
#include "ui/olfmonitoredobservablescontroller.h"
#include "ui/monitoredobservables/pageviewbuilder/pageviewlayoutbuilder.h"
#include "ui/monitoredobservables/widget/homeautomation/homeautomationwidgetbuilder.h"
#include "olfconsolelogchannel.h"
#include "logger/pflog.h"

MonitoredObservableLoader::MonitoredObservableLoader(OlfMonitoredObservablesController& controller,
                                                       PageViewLayoutBuilder *viewsBuilder):
    m_controller{controller}
{
    m_viewsBuilder.reset(viewsBuilder);
    m_viewsBuilder->setBuilder(this);
}

MonitoredObservableLoader::~MonitoredObservableLoader()
{

}

QString MonitoredObservableLoader::getFamilyName(const QString &observableType)
{
    QString ret;

    for (auto i = 0; i < m_widgetBuilders.size() && ret.isEmpty(); i++)
    {
        ret = m_widgetBuilders[i]->getFamilyName(observableType);
    }

    return ret;
}

void MonitoredObservableLoader::browseBegin()
{
    loadBuilders();
}

void MonitoredObservableLoader::browseEnd()
{
    m_controller.endOfLoadingViews();
}

void MonitoredObservableLoader::beginObservableDeclaration(QString observableName,
                                                           QString observableTitle,
                                                           QString observableType,
                                                           QString observableLocalisation)
{
    m_creatingWidget.reset(buildWidget(observableName,
                                        observableTitle,
                                        observableType,
                                        observableLocalisation));
    if (m_creatingWidget.isNull())
    {
        pfWarning1(s_OplinkGuiConsoleLogChannel) << QObject::tr("Type d'observable %1 non reconnu. Widget non créé pour l'observable %2 !").arg(observableType,observableName);
    }
}

void MonitoredObservableLoader::endObservableDeclaration()
{
    if(!m_creatingWidget.isNull())
    {
        m_viewsBuilder->assignWidgetView(m_controller,m_creatingWidget);
        m_controller.addMonitoredObservable(m_creatingWidget);
    }
}

void MonitoredObservableLoader::loadBuilders()
{
    // by default, only one builder for home automation widgets
    addWidgetBuilder(new HomeAutomationWidgetBuilder);
}

void MonitoredObservableLoader::addWidgetBuilder(MonitoredObservableWidgetBuilder *newlyBuilder)
{
    QspMonitoredObservableWidgetBuilder ptrBuilder{newlyBuilder};

    m_widgetBuilders.append(ptrBuilder);
}

MonitoredObservableWidgetCtrl *MonitoredObservableLoader::buildWidget(QString observableName,
                                                                      QString observableTitle,
                                                                      QString observableType,
                                                                      QString observableLocalisation)
{
    MonitoredObservableWidgetCtrl *ret{nullptr};

    for (auto i = 0; i < m_widgetBuilders.size() && ret == nullptr; i++)
    {
        ret = m_widgetBuilders[i]->buildWidget(observableName,
                                               observableTitle,
                                               observableType,
                                               observableLocalisation);
    }

    return ret;
}
