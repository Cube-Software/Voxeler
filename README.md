<p align="center">
  <img src="logo.png" width="320" height="79">
</p>
Voxeler is an open source blockchain-based Roblox-like 3D game based on <a href="https://github.com/kacperks/Fractal_Engine"> Fractal Engine </a>

# Project setup

## Requirements
* CMake 3.16 +
* G++(Linux)
* Visual Studio 2019 and Desktop C++ Development(Windows)

## Engine's Dependencies
* GLAD https://github.com/Dav1dde/glad
* GLFW https://github.com/glfw/glfw
* assimp https://github.com/assimp/assimp
* TinyXML https://github.com/leethomason/tinyxml2
* imgui https://github.com/ocornut/imgui
* stb https://github.com/nothings/stb
* ImGuizmo https://github.com/CedricGuillemet/ImGuizmo
* libsndfile https://github.com/libsndfile/libsndfile
* sol2 https://github.com/ThePhD/sol2.git

## installing dependencies
* Debian/Ubuntu ` $ sudo apt install -y libglfw3-dev libassimp-dev libtinyxml-dev libsndfile-dev libopenal-dev`
* Fedora ` $ sudo dnf install assimp-devel glfw-devel tinyxml2-devel openal-soft libsndfile`

## installing cmake
* Debian/Ubuntu ` $ sudo apt-get install cmake `
* Fedora ` $ sudo dnf install cmake `

## build
* run `$ cmake -B build'
* then compile it with your fav tool