set (LAUNCHER_NAME
     "oplink-server-qt6"
)
message(STATUS "LAUNCHER_NAME = " ${LAUNCHER_NAME})

# Others File only for IDE
add_custom_target(OpLink_backend_other_files
    SOURCES
      run-oplink-backend.sh
      properties.ini
)

qt6_add_executable(${LAUNCHER_NAME})

add_custom_command(TARGET ${LAUNCHER_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
          ${CMAKE_CURRENT_SOURCE_DIR}/run-oplink-backend.sh
          $<TARGET_FILE_DIR:${LAUNCHER_NAME}>/run-oplink-backend.sh
  VERBATIM
)

target_sources(${LAUNCHER_NAME}
  PRIVATE
    "${PF_ROOT_DIR}/plugframe/launchers/consolelauncher/main.cpp"
)

target_include_directories(${LAUNCHER_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${LAUNCHER_NAME}
  PRIVATE
    Qt6::Core
    plugframe-core-qt6
    ${OL_LIB_NAME}
    ${OL_BACKEND_LIB_NAME}
)

target_compile_definitions(${LAUNCHER_NAME}
    PRIVATE
        QT_DEPRECATED_WARNINGS
        $<$<CONFIG:Release>:QT_NO_DEBUG_OUTPUT>
)

set_target_properties(${LAUNCHER_NAME} PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/oplink_backend"
)
