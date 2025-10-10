QT       += gui \
            widgets \
            xml

TEMPLATE = lib
CONFIG  += staticlib

BUNDLE_VERSION = $$cat(../bundle.ver)
TARGET = oplinkF-guiconsole-qt5-$${BUNDLE_VERSION}

SOURCES += \
         olfconsole.cpp \
         olfconsolefactory.cpp \
         ui/monitoredobservables/pageview/pageviewlistlayout.cpp \
         ui/monitoredobservables/pageview/viewlistlayout.cpp \
         ui/monitoredobservables/pageviewbuilder/monitoredobservablebuilder.cpp \
         ui/monitoredobservables/pageviewbuilder/pageviewbylocalisationbuilder.cpp \
         ui/monitoredobservables/pageviewbuilder/pageviewbytypebuilder.cpp \
         ui/monitoredobservables/pageviewbuilder/pageviewlayoutbuilder.cpp \
         ui/monitoredobservables/pageviewbuilder/pageviewlistlayoutbuilder.cpp \
         ui/monitoredobservables/widget/heating6mwidgetctrl.cpp \
         ui/monitoredobservables/widget/lightingwidgetctrl.cpp \
         ui/monitoredobservables/widget/monitoredobservablewidgetctrl.cpp \
         ui/monitoredobservables/widget/smartplugwidgetctrl.cpp \
         ui/monitoredobservables/widget/temperaturehumiditywidgetctrl.cpp \
         ui/monitoredobservables/widget/view/heating6mwidgetview.cpp \
         ui/monitoredobservables/widget/view/lightingwidgetview.cpp \
         ui/monitoredobservables/widget/view/monitoredobservablewidgetview.cpp \
         ui/monitoredobservables/widget/view/smartplugwidgetview.cpp \
         ui/monitoredobservables/widget/view/temperaturehumiditywidgetview.cpp \
         ui/monitoredobservables/widget/view/widgetlistview.cpp \
         ui/monitoredobservables/widget/view/windowsensorwidgetview.cpp \
         ui/monitoredobservables/widget/windowsensorwidgetctrl.cpp \
         ui/olfconsolecontroller.cpp \
         ui/olfconsoleview.cpp \
         ui/olflogincontroller.cpp \
         ui/olfloginview.cpp \
         ui/olfmonitoredobservablescontroller.cpp \
         ui/olfmonitoredobservablesview.cpp

HEADERS += \
         olfconsole.h \
         olfconsole_forward.h \
         olfconsolefactory.h \
         ui/monitoredobservables/pageview/pageviewlistlayout.h \
         ui/monitoredobservables/pageview/viewlistlayout.h \
         ui/monitoredobservables/pageviewbuilder/monitoredobservablebuilder.h \
         ui/monitoredobservables/pageviewbuilder/pageviewbylocalisationbuilder.h \
         ui/monitoredobservables/pageviewbuilder/pageviewbytypebuilder.h \
         ui/monitoredobservables/pageviewbuilder/pageviewlayoutbuilder.h \
         ui/monitoredobservables/pageviewbuilder/pageviewlistlayoutbuilder.h \
         ui/monitoredobservables/widget/heating6mwidgetctrl.h \
         ui/monitoredobservables/widget/lightingwidgetctrl.h \
         ui/monitoredobservables/widget/monitoredobservablewidgetctrl.h \
         ui/monitoredobservables/widget/smartplugwidgetctrl.h \
         ui/monitoredobservables/widget/temperaturehumiditywidgetctrl.h \
         ui/monitoredobservables/widget/view/heating6mwidgetview.h \
         ui/monitoredobservables/widget/view/lightingwidgetview.h \
         ui/monitoredobservables/widget/view/monitoredobservablewidgetview.h \
         ui/monitoredobservables/widget/view/smartplugwidgetview.h \
         ui/monitoredobservables/widget/view/temperaturehumiditywidgetview.h \
         ui/monitoredobservables/widget/view/widgetlistview.h \
         ui/monitoredobservables/widget/view/windowsensorwidgetview.h \
         ui/monitoredobservables/widget/windowsensorwidgetctrl.h \
         ui/olfconsolecontroller.h \
         ui/olfconsoleview.h \
         ui/olflogincontroller.h \
         ui/olfloginview.h \
         ui/olfmonitoredobservablescontroller.h \
         ui/olfmonitoredobservablesview.h

# include dir for compilation
INCLUDEPATH +=  \
        ../plugin \
        ../../../core-lib \
        ../../../../../plugframe/core-lib \
        ../../../../../plugframe/bundles/guiconsole/lib

CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT

FORMS += \
    ui/loginview.ui \
    ui/monitoredobservables/pageview/pageviewlistlayout.ui \
    ui/monitoredobservables/pageview/viewlistlayout.ui \
    ui/monitoredobservables/widget/view/heating6mwidgetview.ui \
    ui/monitoredobservables/widget/view/lightingwidgetview.ui \
    ui/monitoredobservables/widget/view/smartplugwidgetview.ui \
    ui/monitoredobservables/widget/view/temperaturehumiditywidgetview.ui \
    ui/monitoredobservables/widget/view/windowsensorwidgetview.ui
