# Bundle implementation Sources
set(SOURCES
    observablepublisher.cpp
    observablepublishermessagescodec.cpp
    observablepublisherclientconnection.cpp
    observablepublisherfactory.cpp
)

# Bundle implementation Headers
set(HEADERS
    observablepublisher_logchannel.h
    observablepublisher.h
    observablepublishermessagescodec.h
    observablepublisherclientconnection.h
    observablepublisherfactory.h
)

qt_add_library(${BUNDLE_IMPL_NAME} STATIC ${SOURCES} ${HEADERS})

target_include_directories(${BUNDLE_IMPL_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${BUNDLE_IMPL_NAME} PUBLIC
    Qt6::Core
    Qt6::Xml
    plugframe-core-qt6
    oplink-core-qt6
    oplink-core-backend-qt6
)

target_compile_definitions(${BUNDLE_IMPL_NAME}
    PUBLIC
    $<$<CONFIG:Release>:QT_NO_DEBUG_OUTPUT>
)
