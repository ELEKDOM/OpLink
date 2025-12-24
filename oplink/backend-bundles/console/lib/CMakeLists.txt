# Bundle implementation Sources
set(SOURCES
   olcmdprocessor.cpp
   olconsole.cpp
   olconsolefactory.cpp
   submitcmdprocessor.cpp
   subscribecmdprocessor.cpp
   subscribecmdprocessorhook.cpp
   unsubscribecmdprocessor.cpp
)

# Bundle implementation Headers
set(HEADERS
    olcmdprocessor.h
    olconsole.h
    olconsole_forward.h
    olconsolefactory.h
    submitcmdprocessor.h
    subscribecmdprocessor.h
    subscribecmdprocessorhook.h
    unsubscribecmdprocessor.h
)

qt_add_library(${BUNDLE_IMPL_NAME} STATIC ${SOURCES} ${HEADERS})

target_include_directories(${BUNDLE_IMPL_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${BUNDLE_IMPL_NAME} PUBLIC
    Qt6::Core
    plugframe-core-qt6
    console-impl-qt6
    ${OL_LIB_NAME}
    ${OL_BACKEND_LIB_NAME}
)

target_compile_definitions(${BUNDLE_IMPL_NAME}
    PRIVATE
    $<$<CONFIG:Release>:QT_NO_DEBUG_OUTPUT>
)



