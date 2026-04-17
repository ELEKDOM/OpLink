# Bundle implementation Sources
set(SOURCES
    olfconsole.cpp
    olfconsolefactory.cpp
    ui/olfconsolecontroller.cpp
    ui/olfconsoleview.cpp
    ui/olflogincontroller.cpp
    ui/olfloginview.cpp
    ui/olfmonitoredobservablescontroller.cpp
    ui/olfmonitoredobservablesview.cpp
    ui/monitoredobservables/monitoredobservableloader.cpp
    ui/monitoredobservables/pageview/pageviewlistlayout.cpp
    ui/monitoredobservables/pageview/viewlistlayout.cpp
    ui/monitoredobservables/pageviewbuilder/pageviewbylocalisationbuilder.cpp
    ui/monitoredobservables/pageviewbuilder/pageviewbytypebuilder.cpp
    ui/monitoredobservables/pageviewbuilder/pageviewlayoutbuilder.cpp
    ui/monitoredobservables/pageviewbuilder/pageviewlistlayoutbuilder.cpp
    ui/monitoredobservables/widget/monitoredobservablewidgetctrl.cpp
    ui/monitoredobservables/widget/monitoredobservablewidgetbuilder.cpp
    ui/monitoredobservables/widget/monitoredobservablewidgetview.cpp
    ui/monitoredobservables/widget/monitoredobservablewidgetlistview.cpp
    ui/monitoredobservables/widget/homeautomation/homeautomationwidgetbuilder.cpp
    ui/monitoredobservables/widget/homeautomation/controller/heating6mwidgetctrl.cpp
    ui/monitoredobservables/widget/homeautomation/controller/lightingwidgetctrl.cpp
    ui/monitoredobservables/widget/homeautomation/controller/smartplugwidgetctrl.cpp
    ui/monitoredobservables/widget/homeautomation/controller/temperaturehumiditywidgetctrl.cpp
    ui/monitoredobservables/widget/homeautomation/controller/windowsensorwidgetctrl.cpp
    ui/monitoredobservables/widget/homeautomation/view/heating6mwidgetlistview.cpp
    ui/monitoredobservables/widget/homeautomation/view/lightingwidgetlistview.cpp
    ui/monitoredobservables/widget/homeautomation/view/smartplugwidgetlistview.cpp
    ui/monitoredobservables/widget/homeautomation/view/temperaturehumiditywidgetlistview.cpp
    ui/monitoredobservables/widget/homeautomation/view/windowsensorwidgetlistview.cpp
    ui/monitoredobservables/widget/homeautomation/view/tempdoublespinbox.cpp
    ui/monitoredobservables/widget/homeautomation/heatingmanager/heatingmanagerwidgetbuilder.cpp
    ui/monitoredobservables/widget/homeautomation/heatingmanager/controller/heatingmanagerwidgetctrl.cpp
    ui/monitoredobservables/widget/homeautomation/heatingmanager/controller/heatingmanagerpwwidgetctrl.cpp
    ui/monitoredobservables/widget/homeautomation/heatingmanager/controller/heatingmanagerpwtwidgetctrl.cpp
    ui/monitoredobservables/widget/homeautomation/heatingmanager/view/heatingmanagerwidgetlistview.cpp
    ui/monitoredobservables/widget/homeautomation/heatingmanager/view/heatingmanagerpwwidgetlistview.cpp
    ui/monitoredobservables/widget/homeautomation/heatingmanager/view/heatingmanagerpwtwidgetlistview.cpp
    ui/monitoredobservables/widget/homeautomation/heatingmanager/view/heatingroomwidgetlistview.cpp
    ui/monitoredobservables/widget/homeautomation/heatingmanager/view/heatingroompwtwidgetlistview.cpp
    ui/monitoredobservables/widget/homeautomation/heatingmanager/view/heatingroompwwidgetlistview.cpp
)

# Bundle implementation Headers
set(HEADERS
    olfconsole.h
    olfconsole_forward.h
    olfconsolefactory.h
    olfconsolelogchannel.h
    ui/olfconsolecontroller.h
    ui/olfconsoleview.h
    ui/olflogincontroller.h
    ui/olfloginview.h
    ui/olfmonitoredobservablescontroller.h
    ui/olfmonitoredobservablesview.h
    ui/monitoredobservables/monitoredobservableloader.h
    ui/monitoredobservables/pageview/pageviewlistlayout.h
    ui/monitoredobservables/pageview/viewlistlayout.h
    ui/monitoredobservables/pageviewbuilder/pageviewbylocalisationbuilder.h
    ui/monitoredobservables/pageviewbuilder/pageviewbytypebuilder.h
    ui/monitoredobservables/pageviewbuilder/pageviewlayoutbuilder.h
    ui/monitoredobservables/pageviewbuilder/pageviewlistlayoutbuilder.h
    ui/monitoredobservables/widget/monitoredobservablewidgetctrl.h
    ui/monitoredobservables/widget/monitoredobservablewidgetbuilder.h
    ui/monitoredobservables/widget/monitoredobservablewidgetview.h
    ui/monitoredobservables/widget/monitoredobservablewidgetlistview.h
    ui/monitoredobservables/widget/homeautomation/homeautomationwidgetbuilder.h
    ui/monitoredobservables/widget/homeautomation/controller/heating6mwidgetctrl.h
    ui/monitoredobservables/widget/homeautomation/controller/lightingwidgetctrl.h
    ui/monitoredobservables/widget/homeautomation/controller/smartplugwidgetctrl.h
    ui/monitoredobservables/widget/homeautomation/controller/temperaturehumiditywidgetctrl.h
    ui/monitoredobservables/widget/homeautomation/controller/windowsensorwidgetctrl.h
    ui/monitoredobservables/widget/homeautomation/view/heating6mwidgetlistview.h
    ui/monitoredobservables/widget/homeautomation/view/lightingwidgetlistview.h
    ui/monitoredobservables/widget/homeautomation/view/smartplugwidgetlistview.h
    ui/monitoredobservables/widget/homeautomation/view/temperaturehumiditywidgetlistview.h
    ui/monitoredobservables/widget/homeautomation/view/windowsensorwidgetlistview.h
    ui/monitoredobservables/widget/homeautomation/view/tempdoublespinbox.h
    ui/monitoredobservables/widget/homeautomation/heatingmanager/heatingmanagerwidgetbuilder.h
    ui/monitoredobservables/widget/homeautomation/heatingmanager/controller/heatingmanagerwidgetctrl.h
    ui/monitoredobservables/widget/homeautomation/heatingmanager/controller/heatingmanagerpwwidgetctrl.h
    ui/monitoredobservables/widget/homeautomation/heatingmanager/controller/heatingmanagerpwtwidgetctrl.h
    ui/monitoredobservables/widget/homeautomation/heatingmanager/view/heatingmanagerwidgetlistview.h
    ui/monitoredobservables/widget/homeautomation/heatingmanager/view/heatingmanagerpwwidgetlistview.h
    ui/monitoredobservables/widget/homeautomation/heatingmanager/view/heatingmanagerpwtwidgetlistview.h
    ui/monitoredobservables/widget/homeautomation/heatingmanager/view/heatingroomwidgetlistview.h
    ui/monitoredobservables/widget/homeautomation/heatingmanager/view/heatingroompwtwidgetlistview.h
    ui/monitoredobservables/widget/homeautomation/heatingmanager/view/heatingroompwwidgetlistview.h
)

# Bundle implementation Forms
set(FORMS
    ui/loginview.ui
    ui/monitoredobservables/pageview/pageviewlistlayout.ui
    ui/monitoredobservables/pageview/viewlistlayout.ui
    ui/monitoredobservables/widget/homeautomation/view/heating6mwidgetlistview.ui
    ui/monitoredobservables/widget/homeautomation/view/lightingwidgetlistview.ui
    ui/monitoredobservables/widget/homeautomation/view/smartplugwidgetlistview.ui
    ui/monitoredobservables/widget/homeautomation/view/temperaturehumiditywidgetlistview.ui
    ui/monitoredobservables/widget/homeautomation/view/windowsensorwidgetlistview.ui
    ui/monitoredobservables/widget/homeautomation/heatingmanager/view/heatingmanagerwidgetlistview.ui
    ui/monitoredobservables/widget/homeautomation/heatingmanager/view/heatingroomwidgetlistview.ui
)

qt_add_library(${BUNDLE_IMPL_NAME} STATIC ${SOURCES} ${HEADERS}  ${FORMS}
    ui/monitoredobservables/widget/homeautomation/view/tempdoublespinbox.ui)

target_include_directories(${BUNDLE_IMPL_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${BUNDLE_IMPL_NAME} PUBLIC
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Xml
    plugframe-core-qt6
    guiconsole-impl-qt6
    ${OL_LIB_NAME}
)

target_compile_definitions(${BUNDLE_IMPL_NAME}
    PRIVATE
    $<$<CONFIG:Release>:QT_NO_DEBUG_OUTPUT>
)



