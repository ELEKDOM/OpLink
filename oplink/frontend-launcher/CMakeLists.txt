set (LAUNCHER_NAME
     "oplink-guiclient-qt6"
)
message(STATUS "LAUNCHER_NAME = " ${LAUNCHER_NAME})

qt6_add_executable(${LAUNCHER_NAME})

add_custom_command(TARGET ${LAUNCHER_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
          ${CMAKE_CURRENT_SOURCE_DIR}/run-oplink-frontend.sh
          $<TARGET_FILE_DIR:${LAUNCHER_NAME}>/run-oplink-frontend.sh
  VERBATIM
)

target_sources(${LAUNCHER_NAME}
  PRIVATE
    "${PF_ROOT_DIR}/plugframe/launchers/guilauncher/main.cpp"
)

target_include_directories(${LAUNCHER_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${LAUNCHER_NAME}
  PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    plugframe-core-qt6
    plugframe-gui-qt6
    ${OL_LIB_NAME}
    ${OL_BACKEND_LIB_NAME}
)

target_compile_definitions(${LAUNCHER_NAME}
    PRIVATE
        QT_DEPRECATED_WARNINGS
        $<$<CONFIG:Release>:QT_NO_DEBUG_OUTPUT>
)

set_target_properties(${LAUNCHER_NAME} PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/oplink_frontend"
)

# Others File only for IDE
add_custom_target(OpLink_frontend_other_files
    SOURCES
    run-oplink-frontend.sh
    "properties.ini"
    elekdom.qss
)

# Resources:
set(oplink-frontend_resources_resource_files
    "img/app_icon16.png"
    "img/app_icon32.png"
    "img/app_icon48.png"
    "img/app_icon128.png"
    "img/elekdom_logo.png"
    "img/light_on.png"
    "img/light_off.png"
    "img/comfort.png"
    "img/comfort_1.png"
    "img/comfort_2.png"
    "img/eco.png"
    "img/minus.png"
    "img/nofreeze.png"
    "img/plug_off.png"
    "img/plug_on.png"
    "img/plus.png"
    "img/stop.png"
    "img/window_closed.png"
    "img/window_open.png"
)

qt6_add_resources(${LAUNCHER_NAME}
    PREFIX
       "/"
    FILES
        ${oplink-frontend_resources_resource_files}
)
