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

add_custom_command (
    TARGET ${PROJECT_BIN_EXE}
    PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E remove -f ${PROJECT_BIN_EXE}
)

add_custom_command (
    TARGET ${PROJECT_BIN_EXE}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_BIN_EXE} ${BIN_OUTPUT_PATH}
    COMMAND  python ${CMAKE_CURRENT_SOURCE_DIR}/../${SHADER_GENERATOR_FILE}
)

