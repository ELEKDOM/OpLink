# OpLink Core Lib Sources
set(SOURCES
    command/command-names.cpp
    observable/remote/sessionconfdocument.cpp
    observable/type.cpp
    observable/values.cpp
    observable/propertyid.cpp
)

# OpLink Core Lib Headers
set(HEADERS
    olcore-lib_export.h
    command/command-names.h
    network/channel/messagetype.h
    network/channel/codectype.h
    observable/remote/sessionconfdocument.h
    observable/remote/sessionconfhook.h
    observable/type.h
    observable/values.h
    observable/propertyid.h
    observable/heatingmanagermodelnames.h
)

qt_add_library(${OL_LIB_NAME} SHARED ${SOURCES} ${HEADERS})

set_target_properties(${OL_LIB_NAME}
                      PROPERTIES
                      VERSION ${OL_LIB_VERSION}
                      SOVERSION ${OL_LIB_VERSION_MAJOR}
)

target_include_directories(${OL_LIB_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${OL_LIB_NAME}
    PRIVATE
        Qt6::Core
        Qt6::Xml
        plugframe-core-qt6
)

# For Export Declaration
target_compile_definitions(${OL_LIB_NAME}
    PUBLIC
        OLCORE_LIBRARY
)

# Disable Debug Log for Release
target_compile_definitions(${OL_LIB_NAME}
    PUBLIC
        $<$<CONFIG:Release>:QT_NO_DEBUG_OUTPUT>
)
