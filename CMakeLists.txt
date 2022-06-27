cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(Voxeler)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

include_directories(3rdparty/glew/include)
include_directories(3rdparty/sol2/include)
<<<<<<< HEAD
# include_directories(3rdparty/glfw/include)
include_directories(3rdparty/assimp/include)
=======
include_directories(3rdparty/glfw/include)
>>>>>>> 88869030bcc180b7b0dc18cd51ed25a61ad17e42
include_directories(3rdparty/tinyxml2)
include_directories(3rdparty/openal-soft/include)
include_directories(3rdparty/libsndfile/include)

<<<<<<< HEAD
if(WIN32)
# add_subdirectory(3rdparty/glfw)
add_subdirectory(3rdparty/assimp)
=======
if (WIN32) # windows
include_directories(3rdparty/glad/include)
>>>>>>> 88869030bcc180b7b0dc18cd51ed25a61ad17e42
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
# target_link_libraries(${PROJECT_NAME} -lglfw)
target_link_libraries(${PROJECT_NAME} -lGLEW)
target_link_libraries(${PROJECT_NAME} -ltinyxml)
endif()

if (WIN32) # windows
target_link_libraries(${PROJECT_NAME} opengl32)
<<<<<<< HEAD
# target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} glew32s)
=======
target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} glad)
>>>>>>> 88869030bcc180b7b0dc18cd51ed25a61ad17e42
target_link_libraries(${PROJECT_NAME} tinyxml2)
endif(WIN32)