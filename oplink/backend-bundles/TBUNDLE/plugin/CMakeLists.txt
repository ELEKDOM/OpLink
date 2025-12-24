qt_add_plugin(oplink-TBUNDLE-qt5-(bundle.ver)
    TBUNDLEplugin.cpp TBUNDLEplugin.h
    TBUNDLEserviceinterface.h
)
target_include_directories(oplink-TBUNDLE-qt5-(bundle.ver) PRIVATE
    ../../../../../plugframe/core-lib
    ../../../core-backend-lib
    ../../../core-lib
    ../lib
)

target_link_directories(oplink-TBUNDLE-qt5-(bundle.ver) PRIVATE
    ../lib
)

target_link_libraries(oplink-TBUNDLE-qt5-(bundle.ver) PRIVATE
    Qt::Core
    oplink-TBUNDLE-qt5-(../bundle.ver)
)

install(TARGETS oplink-TBUNDLE-qt5-(bundle.ver)
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    FRAMEWORK DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
