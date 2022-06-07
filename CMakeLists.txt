cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(Voxeler)

if(WIN32)
add_subdirectory(3rdparty/glfw)
add_subdirectory(3rdparty/glad)
add_subdirectory(3rdparty/assimp)
add_subdirectory(3rdparty/tinyxml2)
endif(WIN32) 

include_directories(3rdparty/)
include_directories(src/fr)
include_directories(src)

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