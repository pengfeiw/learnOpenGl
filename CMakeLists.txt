cmake_minimum_required(VERSION 3.12.0)
set(PROJECT_NAME LearnOpenGl_CN)
project(${PROJECT_NAME})

set(RESOURCE_DIR ${CMAKE_SOURCE_DIR}/resources)
set(SHADERS_DIR ${RESOURCE_DIR}/shaders)
set(IMAGES_DIR ${RESOURCE_DIR}/imgs)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

link_directories(${CMAKE_SOURCE_DIR}/lib)

file(GLOB_RECURSE SRC_CPP_FILES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE SRC_C_FILES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/src/*.c)
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/include/*.h" "${CMAKE_SOURCE_DIR}/src/*.h" "${CMAKE_SOURCE_DIR}/include/*.hpp")
file(GLOB_RECURSE RESOURCE_FILES "${RESOURCE_DIR}/*")
file(GLOB_RECURSE SHADER_FILES "${SHADERS_DIR}/*.fs" "${SHADERS_DIR}/*.vs")
file(GLOB_RECURSE IMAGE_FILES "${IMAGES_DIR}/*.jpg" "${IMAGES_DIR}/*.png")

# 添加文件: 源码 + 头文件 + 资源文件
# 添加资源文件是为了让资源文件能够在 visual studio 资源管理器中显示
add_executable(${PROJECT_NAME} main.cpp ${SRC_CPP_FILES} ${SRC_C_FILES} ${HEADERS} ${RESOURCE_FILES})

# 标记资源文件位 VS 的内容文件（不参与编译）
set_source_files_properties(${RESOURCE_FILES} PROPERTIES HEADER_FILE_ONLY TRUE)
# 设置 shader 文件语法，最好能够安装 glsl language 插件
set_source_files_properties(${SHADER_FILES} PROPERTIES LANGUAGE "GLSL")
# 将 shaders 在 ide 中现在到 Shaders 文件夹下，否则在 IDE 中会直接显示在根节点下
message(STATUS "SHADER_FILES=${SHADER_FILES}")
message(STATUS "IMAGE_FILES=${IMAGE_FILES}")
source_group("resources/shaders" FILES ${SHADER_FILES})
source_group("resources/imgs" FILES ${IMAGE_FILES})

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
