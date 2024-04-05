
# Application
- Visual Studio Code
- Python (enviroment)
- MSYS2

# CMD
Download and Install Python
> pip install meson
> pip install ninja
> meson setup bin
> ninja || meson compile
> ninja test || meson test

# Library
- MSYS2:
	- pacman -S mingw64/mingw-w64-x86_64-freetype
	- pacman -S mingw64/mingw-w64-x86_64-glfw
	- pacman -S mingw64/mingw-w64-x86_64-glm
	- pacman -S mingw64/mingw-w64-x86_64-bullet
- Assimp:
	- link: https://github.com/assimp/assimp
		- code . (có extendtion cmake) (cài cmake để build)
		- build all
		- move: assimp/bin/libassimp-5d.dll -> ./bin/libassimp-5d.dll
		- move: assimp/lib/libassimpd.dll.a -> ./lib/libassimpd.dll.a
		- move: assimp/include/assimp -> ./inc/assimp
- bass:
	- link: https://www.un4seen.com/
	- download: bass24.zip
	- bass24.zip/x64/bass.dll -> ./bin/bass.dll
	- bass24.zip/c/x64/bass.lib -> ./lib/bass.lib
	- bass24.zip/c/bass.h -> ./inc/bass/bass.h
- stb:
	- link: https://github.com/nothings/stb/blob/master/stb_image.h
	- move: ./inc/stb/stb_image.h
- glad:
	- link: https://glad.dav1d.de/
	- Select:
		- C/C++
		- OpenGL
		- API:
			- gl: version 4.6
			- gles1: None
			- gles2: None
			- glec2: None
		- Profile: Compatibility
		- Extensions: no select
		- Options: Generate a loader
	- Generate
	- download: glad.zip
	- glad.zip/src/glad.c -> ./src/graphic/glad.cpp
	- glad.zip/include/... -> ./inc/...
- mINI:
	- link: https://github.com/metayeti/mINI
	- download release: mINI.zip
	- mINI.zip/src/mini -> ./inc
- tinygltf
	- link: https://github.com/syoyo/tinygltf

# Variable Enviroment
- D:\Programs\MSYS2\mingw64\bin


# Fix Dependency
mingw-w64-x86_64-toolchain (parent)
mingw-w64-x86_64-winpthreads-git (child)
