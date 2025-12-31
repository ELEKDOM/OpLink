qt_add_library(oplink-TBUNDLE-qt5-(bundle.ver)
    TBUNDLE.cpp TBUNDLE.h
    TBUNDLE_forward.h
    TBUNDLEbuilder.cpp TBUNDLEbuilder.h
    TBUNDLEfactory.cpp TBUNDLEfactory.h
    TBUNDLEservice.cpp TBUNDLEservice.h
)
target_include_directories(oplink-TBUNDLE-qt5-(bundle.ver) PUBLIC
    ../../../../../plugframe/core-lib
    ../../../core-backend-lib
    ../../../core-lib
    ../plugin
)

target_link_libraries(oplink-TBUNDLE-qt5-(bundle.ver) PUBLIC
    Qt::Core
)

if(CMAKE_BUILD_TYPE STREQUAL Release)
    target_compile_definitions(oplink-TBUNDLE-qt5-(bundle.ver) PUBLIC
        QT_NO_DEBUG_OUTPUT
    )
endif()

install(TARGETS oplink-TBUNDLE-qt5-(bundle.ver)
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    FRAMEWORK DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
