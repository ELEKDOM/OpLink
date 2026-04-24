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

#include <QFile>
#include "olfmonitoredobservablescontroller.h"
#include "olfmonitoredobservablesview.h"
#include "olfconsole.h"
#include "observable/remote/sessionconfdocument.h"
#include "gui/guipageview.h"
#include "ui/monitoredobservables/monitoredobservableloader.h"
#include "ui/monitoredobservables/pageviewbuilder/pageviewbylocalisationbuilder.h"
#include "ui/monitoredobservables/pageviewbuilder/pageviewbytypebuilder.h"
#include "ui/monitoredobservables/widget/monitoredobservablewidgetctrl.h"
#include "logger/pflog.h"

OlfMonitoredObservablesController::OlfMonitoredObservablesController(OlfConsole& console,
                                                                     PageViewLayout monitoringViewLayout,
                                                                     QObject *parent):
    OlfConsoleController{console,
                         StatesPageCtrlName(),
                         QStringList{monitoringMenuName(),StatesMenuName()},
                         parent},
    m_monitoringViewLayout{monitoringViewLayout},
    m_sessionIdOnServer{0}
{
    state(State::WaitingForUserLogged);
}

OlfMonitoredObservablesController::~OlfMonitoredObservablesController()
{

}

void OlfMonitoredObservablesController::sessionStartedOnServer(quint32 sessionId,
                                                               const QString &profile,
                                                               quint16 confId)
{
    if (state() == State::WaitingForSessionStarted)
    {
        statusMsg(tr("Session started on server"));
        m_sessionIdOnServer = sessionId;

        // the widget builder depends on the selected view type
        m_widgetBuilder.reset(buildWidgetBuilder());
        m_profileConfBrowser.reset(createProfileConfBrowser(*m_widgetBuilder));

        // need to download the file ?
        if (profileFileExists(profile))  // sets m_fullProfileFileName
        {
            // Test for conf version
            m_profileConfBrowser->load(m_fullProfileFileName);
            if (m_profileConfBrowser->fileLoaded())
            {
                if (m_profileConfBrowser->confId() == confId)
                {
                    loadConfFile();
                }
                else
                {
                    needDownload();
                }
            }
            else
            {
                pfWarning1(bundle().logChannel()) << "Can't load profile file : " << m_fullProfileFileName;
            }
        }
        else
        {
            // file must be downloaded
            needDownload();
        }
    }
}

void OlfMonitoredObservablesController::confDownloadedFromServer(quint32 sessionId, const QString &xmlConfig)
{
    if (state() == State::WaitingForConfUpdate && m_sessionIdOnServer == sessionId)
    {
        statusMsg(tr("profile configuration downloaded from server"));
        if (saveConfFile(xmlConfig))
        {
            loadConfFile();
        }
    }
}

void OlfMonitoredObservablesController::newObservableStateFromServer(quint32 sessionId,
                                                                     const QString &observableName,
                                                                     const QString &propertyName,
                                                                     const QVariant &value)
{
    if(state() == State::SessionInProgress && m_sessionIdOnServer == sessionId)
    {
        QspMonitoredObservableWidgetCtrl mo{monitoredObservable(observableName)};

        if (!mo.isNull())
        {
            mo->updateStateValue(propertyName,value);
        }
    }
}

void OlfMonitoredObservablesController::addMonitoredObservable(QspMonitoredObservableWidgetCtrl newly)
{
    m_monitoredObservables.insert(newly->name(),newly);
    connect(newly.get(),SIGNAL(execCmd(QString)),SLOT(execCmd(QString)));
}

void OlfMonitoredObservablesController::endOfLoadingViews()
{
    const plugframe::GuiPageViewList& vl{viewList()};

    clearStatusMsg();
    // Initialize all view layout
    for (int i = 0; i < vl.size(); i++)
    {
        OlfMonitoredObservablesView *mov{dynamic_cast<OlfMonitoredObservablesView*>(vl.at(i))};

        if (mov)
        {
            mov->pushUpWidgets();
        }
    }
    updateViewsIdx(); // add all new views into the central widget
    currentCtrl();  // show the selected view of this controller
}

void OlfMonitoredObservablesController::closeSession()
{
    // Delete all widgets
    m_monitoredObservables.clear();

    // Delette all views
    clear();

    // Reset state
    state(State::WaitingForUserLogged);
}

OlfMonitoredObservablesView *OlfMonitoredObservablesController::viewByName(const QString &pageName)
{
    OlfMonitoredObservablesView *ret{nullptr};
    const plugframe::GuiPageViewList& list{viewList()};

    for (qsizetype i = 0; i < list.size() && !ret; ++i)
    {
        OlfMonitoredObservablesView *v{dynamic_cast<OlfMonitoredObservablesView*>(list.at(i))};

        if (v->pageName() == pageName)
        {
            ret = v;
        }
    }

    return ret;
}

void OlfMonitoredObservablesController::addMonitoredObservablesView(OlfMonitoredObservablesView *pageView)
{
    addView(pageView);
}

MonitoredObservableLoader *OlfMonitoredObservablesController::buildWidgetBuilder()
{
    PageViewLayoutBuilder *layoutBuilder{nullptr};

    if (m_monitoringViewLayout == PageViewLayout::TypeListLayout)
    {
        layoutBuilder = createLayoutByTypeBuilder();
    }
    else
    {
        layoutBuilder = createLayoutByLocalisationBuilder();
    }

    return createMonitoredObservableBuilder(layoutBuilder);
}

MonitoredObservableLoader *OlfMonitoredObservablesController::createMonitoredObservableBuilder(PageViewLayoutBuilder *viewsBuilder)
{
    return new MonitoredObservableLoader(*this,viewsBuilder);
}

PageViewLayoutBuilder *OlfMonitoredObservablesController::createLayoutByTypeBuilder()
{
    return new PageViewByTypeBuilder;
}

PageViewLayoutBuilder *OlfMonitoredObservablesController::createLayoutByLocalisationBuilder()
{
    return new PageViewByLocalisationBuilder;
}

oplink::SessionConfDocument *OlfMonitoredObservablesController::createProfileConfBrowser(MonitoredObservableLoader& hook)
{
    return new oplink::SessionConfDocument(hook);
}

bool OlfMonitoredObservablesController::profileFileExists(const QString &profile)
{
    m_fullProfileFileName = bundle().getConfDir() + profile + QStringLiteral("-remotemonitoring.xml");

    pfDebug4(bundle().logChannel()) << "Profile Filename : " << m_fullProfileFileName;

    QFile file(m_fullProfileFileName);

    return file.exists();
}

void OlfMonitoredObservablesController::loadConfFile()
{
    state(State::SessionInProgress);
    statusMsg(tr("Load configuration"));

    m_profileConfBrowser->load(m_fullProfileFileName);
    m_profileConfBrowser->browse();

    bundle().sendReadyToServer();
}

void OlfMonitoredObservablesController::needDownload()
{
    state(State::WaitingForConfUpdate);
    statusMsg(tr("Download profile"));
    bundle().sendDownloadConfToServer();
}

bool OlfMonitoredObservablesController::saveConfFile(const QString &xmlConfig)
{
    bool ret;
    QFile file(m_fullProfileFileName);

    ret = file.open(QIODevice::WriteOnly | QIODevice::Text);
    if (ret)
    {
        file.write(xmlConfig.toUtf8());
        file.close();
    }
    return ret;
}

QspMonitoredObservableWidgetCtrl OlfMonitoredObservablesController::monitoredObservable(QString name)
{
    return m_monitoredObservables.value(name);
}

void OlfMonitoredObservablesController::onUserLogged()
{
    if (state() == State::WaitingForUserLogged)
    {
        state(State::WaitingForSessionStarted);
        statusMsg(tr("Waiting for session starting"));
        currentCtrl();
    }
}

void OlfMonitoredObservablesController::execCmd(QString cmd)
{
    if (state() == State::SessionInProgress)
    {
        bundle().sendExecCmdToServer(cmd);
    }
}

