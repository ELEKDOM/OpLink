# Bundle implementation Sources
set(SOURCES
    modelregisterservice.cpp
    observablebuilderservice.cpp
    observablemodelregister.cpp
    observablemodelregisterfactory.cpp
    observablemodelregisterserviceimplementation.cpp
)

# Bundle implementation Headers
set(HEADERS
    modelregisterservice.h
    observablebuilderservice.h
    observablemodelregister.h
    observablemodelregister_forward.h
    observablemodelregisterfactory.h
    observablemodelregisterserviceimplementation.h
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

