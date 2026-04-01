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
    ui/monitoredobservables/widget/homeautomation/view/heating6mwidgetview.cpp
    ui/monitoredobservables/widget/homeautomation/view/lightingwidgetview.cpp
    ui/monitoredobservables/widget/homeautomation/view/smartplugwidgetview.cpp
    ui/monitoredobservables/widget/homeautomation/view/temperaturehumiditywidgetview.cpp
    ui/monitoredobservables/widget/homeautomation/view/windowsensorwidgetview.cpp
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
    ui/monitoredobservables/widget/homeautomation/view/heating6mwidgetview.h
    ui/monitoredobservables/widget/homeautomation/view/lightingwidgetview.h
    ui/monitoredobservables/widget/homeautomation/view/smartplugwidgetview.h
    ui/monitoredobservables/widget/homeautomation/view/temperaturehumiditywidgetview.h
    ui/monitoredobservables/widget/homeautomation/view/windowsensorwidgetview.h
)

# Bundle implementation Forms
set(FORMS
    ui/loginview.ui
    ui/monitoredobservables/pageview/pageviewlistlayout.ui
    ui/monitoredobservables/pageview/viewlistlayout.ui
    ui/monitoredobservables/widget/homeautomation/view/heating6mwidgetview.ui
    ui/monitoredobservables/widget/homeautomation/view/lightingwidgetview.ui
    ui/monitoredobservables/widget/homeautomation/view/smartplugwidgetview.ui
    ui/monitoredobservables/widget/homeautomation/view/temperaturehumiditywidgetview.ui
    ui/monitoredobservables/widget/homeautomation/view/windowsensorwidgetview.ui
)

qt_add_library(${BUNDLE_IMPL_NAME} STATIC ${SOURCES} ${HEADERS}  ${FORMS})

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



