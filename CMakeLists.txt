cmake_minimum_required(VERSION 3.17)
project(engine_test)

set(CMAKE_CXX_STANDARD 14)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/CMake")

find_package(glew REQUIRED)
find_package(glfw REQUIRED)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(Png REQUIRED)

include_directories(SYSTEM ${GLEW_INCLUDE_DIRS})
include_directories(SYSTEM ${GLFW_INCLUDE_DIRS})

include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

set(PROJECT_HEADERS_DIR ${PROJECT_SOURCE_DIR}/include)
set(PROJECT_SOURCES_DIR ${PROJECT_SOURCE_DIR}/src)

file(GLOB_RECURSE HEADERS ${PROJECT_HEADERS_DIR}/*.h)
file(GLOB_RECURSE SOURCES ${PROJECT_SOURCES_DIR}/*.cpp)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES} include/window/window.h src/window/window.cpp include/window/events.h src/window/events.cpp include/graphics/shader.h src/graphics/shader.cpp include/graphics/texture.h src/graphics/texture.cpp include/loaders/png_loader.h src/loaders/png_loader.cpp include/window/camera.h src/window/camera.cpp)

include_directories(${PROJECT_HEADERS_DIR})
include_directories(SYSTEM ${PNG_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} ${GLEW_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${GLFW_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
target_link_libraries(${PROJECT_NAME} ${PNG_LIBRARIES})

file(COPY ${GLEW_LIBRARY} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${GLFW_LIBRARY} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})