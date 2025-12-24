# Bundle implementation Sources
set(SOURCES
    event/mandatorypropertiesmodelloadingevent.cpp
    event/observablemodelsloadingevent.cpp
    event/processorsmodelloadingevent.cpp
    event/specificpropertiesmodelloadingevent.cpp
    observablemodelloader.cpp
    observablemodelloaderemitter.cpp
    observablemodelloaderfactory.cpp
    observablemodelloaderlistener.cpp
)

# Bundle implementation Headers
set(HEADERS
    event/mandatorypropertiesmodelloadingevent.h
    event/observablemodelsloadingevent.h
    event/processorsmodelloadingevent.h
    event/specificpropertiesmodelloadingevent.h
    observablemodelloader.h
    observablemodelloader_forward.h
    observablemodelloaderemitter.h
    observablemodelloaderfactory.h
    observablemodelloaderlistener.h
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
