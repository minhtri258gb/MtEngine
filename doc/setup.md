
# Application
VsCode
Python
MSYS2

# CMD
Download and Install Python
> pip install meson
> pip install ninja
> meson setup bin
> ninja || meson compile
> ninja test || meson test

# Library
- MSYS2:
	- pacman -S mingw64/mingw-w64-x86_64-assimp
	- pacman -S mingw64/mingw-w64-x86_64-freetype
	- pacman -S mingw64/mingw-w64-x86_64-glfw
	- pacman -S mingw64/mingw-w64-x86_64-glm
	- pacman -S mingw64/mingw-w64-x86_64-bullet
- bass:
	- link: https://www.un4seen.com/
	- download: bass24.zip
	- bass24.zip/x64/bass.dll -> ./bin/bass.dll
	- bass24.zip/c/x64/bass.lib -> ./lib/bass.lib
	- bass24.zip/c/bass.h -> ./inc/bass/bass.h
- stb:
	- https://github.com/nothings/stb/blob/master/stb_image.h
	- move: ./inc/stb/stb_image.h
- glad:
	- link: https://glad.dav1d.de/
	- download: glad.zip
	- glad.zip/src/glad.c -> ./src/graphic/glad.cpp
	- glad.zip/include/... -> ./inc/...
- mINI:
	- link: https://github.com/metayeti/mINI
	- download release: mINI.zip
	- mINI.zip/src/mini -> ./inc

# Variable Enviroment
- D:\Programs\MSYS2\mingw64\bin
