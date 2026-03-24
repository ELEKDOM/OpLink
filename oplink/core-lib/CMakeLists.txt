# OpLink Core Lib Sources
set(SOURCES
    command/command-names.cpp
    frontendtypes.cpp
    network_tcp/downloadconfigmessage.cpp
    network_tcp/downloadconfigreplymessage.cpp
    network_tcp/message.cpp
    network_tcp/readymessage.cpp
    network_tcp/sessionmessage.cpp
    network_tcp/sessionstartedmessage.cpp
    network_tcp/signinmessage.cpp
    network_tcp/signinreplymessage.cpp
    network_tcp/signoutmessage.cpp
    network_tcp/statevaluemessage.cpp
    network_tcp/submitordermessage.cpp
    observable/highobservable/highobservableconfdocument.cpp
    observable/highobservable/heatingmanager/heatingmanagerconfdocument.cpp
    observable/remote/sessionconfdocument.cpp
    observable/type.cpp
    observable/values.cpp

)

# OpLink Core Lib Headers
set(HEADERS
    olcore-lib_export.h
    olcore-lib_forward.h
    command/command-names.h
    frontendtypes.h
    network_tcp/downloadconfigmessage.h
    network_tcp/downloadconfigreplymessage.h
    network_tcp/message.h
    network_tcp/messagetype.h
    network_tcp/readymessage.h
    network_tcp/sessionmessage.h
    network_tcp/sessionstartedmessage.h
    network_tcp/signinmessage.h
    network_tcp/signinreplymessage.h
    network_tcp/signoutmessage.h
    network_tcp/statevaluemessage.h
    network_tcp/submitordermessage.h
    observable/highobservable/highobservableconfdocument.h
    observable/highobservable/highobservableloaderhook.h
    observable/highobservable/heatingmanager/heatingmanagerconfdocument.h
    observable/highobservable/heatingmanager/heatingmanagerloaderhook.h
    observable/remote/sessionconfdocument.h
    observable/remote/sessionconfhook.h
    observable/type.h
    observable/values.h
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
