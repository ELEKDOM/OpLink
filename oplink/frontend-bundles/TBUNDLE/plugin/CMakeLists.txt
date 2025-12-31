qt_add_plugin(oplinkF-TBUNDLE-qt5-(bundle.ver)
    TBUNDLEplugin.cpp TBUNDLEplugin.h
    TBUNDLEserviceinterface.h
)
target_include_directories(oplinkF-TBUNDLE-qt5-(bundle.ver) PRIVATE
    ../../../../../plugframe/core-lib
    ../../../core-lib
    ../lib
)

target_link_directories(oplinkF-TBUNDLE-qt5-(bundle.ver) PRIVATE
    ../lib
)

target_link_libraries(oplinkF-TBUNDLE-qt5-(bundle.ver) PRIVATE
    Qt::Core
    oplinkF-TBUNDLE-qt5-(../bundle.ver)
)

install(TARGETS oplinkF-TBUNDLE-qt5-(bundle.ver)
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    FRAMEWORK DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
