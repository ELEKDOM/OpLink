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


#ifndef OLFMONITOREDOBSERVABLESCONTROLLER_H
#define OLFMONITOREDOBSERVABLESCONTROLLER_H

#include <QHash>
#include "olfconsolecontroller.h"
#include "olcore-lib_forward.h"

namespace elekdom
{
namespace oplink
{
namespace frontend
{
namespace guiconsole
{

enum class PageViewLayout : quint8 {LocalisationListLayout,TypeListLayout};

class OlfMonitoredObservablesController : public OlfConsoleController
{
    Q_OBJECT

private:
    static inline QString StatesMenuName() {return tr("&Tracking");}
    static inline QString StatesPageCtrlName() {return QStringLiteral("Monitoring");}

public:
    OlfMonitoredObservablesController(bundle::OlfConsole& console,PageViewLayout monitoringViewLayout,QObject *parent = nullptr);
    ~OlfMonitoredObservablesController() override;

public slots:
    void onUserLogged();
    void execCmd(QString cmd);

public:
    void sessionStartedOnServer(quint32 sessionId,const QString& profile,quint16 confId);
    void confDownloadedFromServer(quint32 sessionId,const QString& xmlConfig);
    void newObservableStateFromServer(quint32 sessionId,
                                      const QString& observableName,
                                      const QString& propertyName,
                                      const QVariant& value);
    void addMonitoredObservable(monitoredobservable::widget::QspMonitoredObservableWidgetCtrl newly);
    void endOfLoadingViews();
    void closeSession();
    const quint32& sessionId() {return m_sessionIdOnServer;}

public:
    OlfMonitoredObservablesView *viewByName(const QString& pageName);
    void addMonitoredObservablesView(OlfMonitoredObservablesView *pageView);

protected:
    virtual monitoredobservable::MonitoredObservableBuilder *buildWidgetBuilder();
    virtual monitoredobservable::MonitoredObservableBuilder *createMonitoredObservableBuilder(monitoredobservable::PageViewLayoutBuilder *viewsBuilder);
    virtual monitoredobservable::PageViewLayoutBuilder *createLayoutByTypeBuilder();
    virtual monitoredobservable::PageViewLayoutBuilder *createLayoutByLocalisationBuilder();
    virtual core::remote::SessionConfDocument *createProfileConfBrowser(monitoredobservable::MonitoredObservableBuilder& hook);

private:
    bool profileFileExists(const QString& profile);
    void loadConfFile();
    void needDownload();
    bool saveConfFile(const QString& xmlConfig);
    monitoredobservable::widget::QspMonitoredObservableWidgetCtrl monitoredObservable(QString name);

private:
    PageViewLayout                                                               m_monitoringViewLayout;
    quint32                                                                      m_sessionIdOnServer;
    QString                                                                      m_fullProfileFileName;
    core::remote::QspSessionConfDocument                                         m_profileConfBrowser;
    monitoredobservable::QspMonitoredObservableBuilder                           m_widgetBuilder;
    QHash<QString,monitoredobservable::widget::QspMonitoredObservableWidgetCtrl> m_monitoredObservables;
};

} //namespace guiconsole
} //namespace frontend
} //namespace oplink
} //namespace elekdom

#endif // OLFMONITOREDOBSERVABLESCONTROLLER_H
