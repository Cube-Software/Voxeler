cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(Voxeler)
set(CXX_STANDARD 17)

if(WIN32)
add_subdirectory(3rdparty/glfw)
add_subdirectory(3rdparty/glad)
add_subdirectory(3rdparty/assimp)
add_subdirectory(3rdparty/tinyxml2)
add_subdirectory(3rdparty/openal-soft)
add_subdirectory(3rdparty/libsndfile)
add_subdirectory(3rdparty/sol2)
endif(WIN32) 

include_directories(3rdparty/sol2/include)
include_directories(3rdparty/glfw/include)
include_directories(3rdparty/assimp/include)
include_directories(3rdparty/tinyxml2)
include_directories(3rdparty/openal-soft/include)
include_directories(3rdparty/libsndfile/include)
include_directories(3rdparty/glad/include)

file(GLOB_RECURSE Sources "src/**.cpp" "src/**.h")

add_executable(${PROJECT_NAME} ${Sources})

if(UNIX AND NOT APPLE) # linux
target_link_libraries(${PROJECT_NAME} -lGL)
target_link_libraries(${PROJECT_NAME} -lglfw)
target_link_libraries(${PROJECT_NAME} -lglad)
target_link_libraries(${PROJECT_NAME} -lassimp)
target_link_libraries(${PROJECT_NAME} -ltinyxml2)
endif()

if (WIN32) # windows
target_link_libraries(${PROJECT_NAME} opengl32)
target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} glad)
target_link_libraries(${PROJECT_NAME} tinyxml2)
target_link_libraries(${PROJECT_NAME} assimp)
endif(WIN32)