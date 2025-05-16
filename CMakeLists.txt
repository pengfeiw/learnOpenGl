cmake_minimum_required(VERSION 3.10.0)
project(LearnOpenGl_CN)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

link_directories(${CMAKE_SOURCE_DIR}/lib)

file(GLOB_RECURSE SRC_CPP_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE SRC_C_FILES ${CMAKE_SOURCE_DIR}/src/*.c)
file(GLOB_RECURSE HEADERS "${CMAKE_SOURCE_DIR}/include/*.h" "${CMAKE_SOURCE_DIR}/src/*.h")

add_executable(LearnOpenGl_CN main.cpp ${SRC_CPP_FILES} ${SRC_C_FILES} ${HEADERS})

target_include_directories(LearnOpenGl_CN PRIVATE "${CMAKE_SOURCE_DIR}/include" "${CMAKE_SOURCE_DIR}/src")

target_link_libraries(LearnOpenGl_CN PRIVATE glfw3 opengl32)
