AUX_SOURCE_DIRECTORY(. SRC_DIR)

#create executable
add_executable(${PROJECT_NAME} ${SRC_DIR})

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARY})
target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} glad)
target_link_libraries(${PROJECT_NAME} json)
target_link_libraries(${PROJECT_NAME} assimp)

if(MSVC)
    set(PROJECT_BIN_EXE ${PROJECT_NAME}.exe)
else()
    set(PROJECT_BIN_EXE ${PROJECT_NAME})
endif(MSVC)
set(SHADER_GENERATOR_FILE shader_generate.py)

if(MSVC)
    add_custom_command (
        TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/src/${CMAKE_BUILD_TYPE}/${PROJECT_BIN_EXE} ${BIN_OUTPUT_PATH}
    )
else()
    add_custom_command (
        TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_BIN_EXE} ${BIN_OUTPUT_PATH}
    )
endif(MSVC)

add_custom_command (
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND  python ${CMAKE_HOME_DIRECTORY}/${SHADER_GENERATOR_FILE}
)
