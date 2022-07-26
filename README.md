<p align="center">
  <img src="logo.png" width="320" height="79">
</p>
Voxeler is an open source blockchain-based Roblox-like 3D game based on <a href="https://github.com/kacperks/Fractal_Engine"> Fractal Engine BETA 3.0 </a>

// NOTE : for now we are working on Fractal engine's fork revised for Voxeler //

# Project setup

## Requirements
* CMake 3.16 +
* G++(Linux)
* MinGW (Windows)

## Engine's Dependencies
* tinyxml2 https://github.com/leethomason/tinyxml2
* imgui https://github.com/ocornut/imgui
* stb https://github.com/nothings/stb
* ImGuizmo https://github.com/CedricGuillemet/ImGuizmo
* libsndfile https://github.com/libsndfile/libsndfile
* sol2 https://github.com/ThePhD/sol2.git
* openal-soft https://github.com/kcat/openal-soft.git

## Installing the dependencies
* Debian/Ubuntu ` $ sudo apt install -y libtinyxml-dev libsndfile-dev libopenal-dev`
* Fedora ` $ sudo dnf install tinyxml2-devel openal-soft libsndfile`

## Installing CMake
* Debian/Ubuntu ` $ sudo apt-get install cmake `
* Fedora ` $ sudo dnf install cmake `

## Build
* run ` $ cmake -B build `
* ...and then compile it with your favorite tool
