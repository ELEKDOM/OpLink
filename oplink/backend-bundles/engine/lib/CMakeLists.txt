# Bundle implementation Sources
set(SOURCES
   observableservice.cpp
   serverengine.cpp
   serverenginefactory.cpp
   serverenginelistener.cpp
   states/loadingvirtualequipmentsetsstate.cpp
   states/serverstartingstate.cpp
   states/startingclientsstate.cpp
   states/startinginfrastructuresstate.cpp
)

# Bundle implementation Headers
set(HEADERS
    observableservice.h
    serverengine.h
    serverengine_forward.h
    serverenginefactory.h
    serverenginelistener.h
    states/loadingvirtualequipmentsetsstate.h
    states/serverstartingstate.h
    states/startingclientsstate.h
    states/startinginfrastructuresstate.h
)

qt_add_library(${BUNDLE_IMPL_NAME} STATIC ${SOURCES} ${HEADERS})

target_include_directories(${BUNDLE_IMPL_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${BUNDLE_IMPL_NAME} PUBLIC
    Qt6::Core
    plugframe-core-qt6
    ${OL_LIB_NAME}
    ${OL_BACKEND_LIB_NAME}
)

target_compile_definitions(${BUNDLE_IMPL_NAME}
    PRIVATE
    $<$<CONFIG:Release>:QT_NO_DEBUG_OUTPUT>
)
