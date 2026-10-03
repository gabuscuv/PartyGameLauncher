add_executable(${PROJECT_NAME}
    ${CMAKE_CURRENT_LIST_DIR}/PartyGameLauncher.c

)

target_include_directories(${PROJECT_NAME}
PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
)

# ---------------------------------------------------------
# Resources
# ---------------------------------------------------------

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory
        "${CMAKE_SOURCE_DIR}/bin/resources"

    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/resources"
        "${CMAKE_SOURCE_DIR}/bin/resources"

    COMMENT "Copying resources to bin/resources"
)

add_subdirectory(screens)