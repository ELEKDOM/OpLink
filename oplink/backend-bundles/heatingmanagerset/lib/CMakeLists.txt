# Bundle implementation Sources
set(SOURCES
    heatingmanagerset.cpp
    heatingmanagersetfactory.cpp
    heatingmanager/heatingmanagerloader.cpp
)

# Bundle implementation Headers
set(HEADERS
    heatingmanagerset.h
    heatingmanagersetfactory.h
    heatingmanagerset_forward.h
    heatingmanagersetlogchannel.h
    heatingmanager/heatingmanagerloader.h
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
    ${OL_LIB_NAME}
    ${OL_BACKEND_LIB_NAME}
)

target_compile_definitions(${BUNDLE_IMPL_NAME}
    PRIVATE
    $<$<CONFIG:Release>:QT_NO_DEBUG_OUTPUT>
)

