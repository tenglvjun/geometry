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
    add_custom_command (
        TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo ${EXECUTABLE_OUTPUT_PATH}/${CMAKE_BUILD_TYPE}/${PROJECT_BIN_EXE}
        COMMAND ${CMAKE_COMMAND} -E copy ${EXECUTABLE_OUTPUT_PATH}/${CMAKE_BUILD_TYPE}/${PROJECT_BIN_EXE} ${EXECUTABLE_OUTPUT_PATH}
    )
endif(MSVC)


