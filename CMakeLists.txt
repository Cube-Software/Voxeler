cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(Voxeler)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

include_directories(3rdparty/glew/include)
include_directories(3rdparty/sol2/include)
# include_directories(3rdparty/glfw/include)
include_directories(3rdparty/assimp/include)
include_directories(3rdparty/tinyxml2)
include_directories(3rdparty/openal-soft/include)
include_directories(3rdparty/libsndfile/include)

if (WIN32) # windows
include_directories(3rdparty/glad/include)
add_subdirectory(3rdparty/openal-soft)
add_subdirectory(3rdparty/libsndfile)
add_subdirectory(3rdparty/sol2)
add_subdirectory(3rdparty/tinyxml2)
add_subdirectory(3rdparty/glad)
endif(WIN32)

file(GLOB_RECURSE Sources "src/app.cpp" "src/engine/**.cpp" "src/engine/**.hpp")

add_executable(${PROJECT_NAME} ${Sources})

if(UNIX AND NOT APPLE) # linux
target_link_libraries(${PROJECT_NAME} -lGL)
target_link_libraries(${PROJECT_NAME} -lGLEW)
target_link_libraries(${PROJECT_NAME} -ltinyxml)
endif()

if (WIN32) # windows
target_link_libraries(${PROJECT_NAME} opengl32)
target_link_libraries(${PROJECT_NAME} glew32s)
target_link_libraries(${PROJECT_NAME} glad)
target_link_libraries(${PROJECT_NAME} tinyxml2)
endif(WIN32)