cmake_minimum_required(VERSION 3.12.0)
set(PROJECT_NAME LearnOpenGl_CN)
project(${PROJECT_NAME})

set(RESOURCE_DIR ${CMAKE_SOURCE_DIR}/resources)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

link_directories(${CMAKE_SOURCE_DIR}/lib)

file(GLOB_RECURSE SRC_CPP_FILES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE SRC_C_FILES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/src/*.c)
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/include/*.h" "${CMAKE_SOURCE_DIR}/src/*.h")

add_executable(${PROJECT_NAME} main.cpp ${SRC_CPP_FILES} ${SRC_C_FILES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/include" "${CMAKE_SOURCE_DIR}/src")

target_link_libraries(${PROJECT_NAME} PRIVATE glfw3 opengl32)

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/debug
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/release
)

# copy resource directory to target directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${RESOURCE_DIR}
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
    COMMENT "Copying resources to executable directory"
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${RESOURCE_DIR}
    ${CMAKE_BINARY_DIR}/resources
    COMMENT "Copying resources to build directory"
)
