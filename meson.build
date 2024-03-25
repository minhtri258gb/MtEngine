project('MT Engine', 'cpp',
	version: '1.0.0',
	license: 'MIT')
# add_global_arguments('-DSOME_TOKEN=value', language: 'cpp')
# glib_dep = dependency('glib-2.0')

# inc = include_directories('include')

# subdir('include')
# subdir('src')
# subdir('test')

# pkg_mod = import('pkgconfig')
# pkg_mod.generate(
# 	libraries: foolib,
# 	version: '1.0',
# 	name: 'libfoobar',
# 	filebase: 'foobar',
# 	description: 'A Library to barnicate your foos.'
# )

# Include
dir_includes = ['./src', './inc', './inc/bullet']


# Library Engine
engine_file_cpp = [
	 './src/engine/library.cpp'
	,'./src/engine/Config.cpp'
	,'./src/engine/Input.cpp'
	,'./src/engine/Timer.cpp'
	,'./src/engine/datatype/Flag32.cpp'
	,'./src/engine/datatype/3D/Vector2.cpp'
	,'./src/engine/datatype/3D/Vector2i.cpp'
	,'./src/engine/datatype/3D/Vector3.cpp'
	,'./src/engine/datatype/3D/Vector3i.cpp'
	,'./src/engine/datatype/3D/Vector4.cpp'
	,'./src/engine/datatype/3D/Vector4i.cpp'
	,'./src/engine/datatype/3D/Matrix3x3.cpp'
	,'./src/engine/datatype/3D/Matrix4x4.cpp'
	,'./src/engine/datatype/3D/Quaternion.cpp'
	,'./src/engine/exception/Exception.cpp'
	,'./src/engine/exception/BoundingException.cpp'
	,'./src/engine/exception/LoadException.cpp'
	,'./src/engine/exception/MathException.cpp'
	,'./src/engine/load/TextFile.cpp'
	,'./src/engine/load/FileIni.cpp'
	,'./src/engine/math/Math.cpp'
	,'./src/engine/file/Image.cpp'
	,'./src/engine/file/FileCFG.cpp'
	,'./src/engine/utils/StringUtils.cpp'
]
engine_file_h = [
	 './src/engine/enumKey.h'
	,'./src/engine/Config.h'
	,'./src/engine/Input.h'
	,'./src/engine/Timer.h'
	,'./src/engine/datatype/3D/Math3D.'
	,'./src/engine/datatype/Flag32.h'
	,'./src/engine/datatype/3D/Vector2.h'
	,'./src/engine/datatype/3D/Vector2i.h'
	,'./src/engine/datatype/3D/Vector3.h'
	,'./src/engine/datatype/3D/Vector3i.h'
	,'./src/engine/datatype/3D/Vector4.h'
	,'./src/engine/datatype/3D/Vector4i.h'
	,'./src/engine/datatype/3D/Matrix3x3.h'
	,'./src/engine/datatype/3D/Matrix4x4.h'
	,'./src/engine/datatype/3D/Quaternion.h'
	,'./src/engine/exception/Exception.h'
	,'./src/engine/exception/BoundingException.h'
	,'./src/engine/exception/LoadException.h'
	,'./src/engine/exception/MathException.h'
	,'./src/engine/load/TextFile.h'
	,'./src/engine/load/FileIni.h'
	,'./src/engine/math/Math.h'
	,'./src/engine/file/Image.h'
	,'./src/engine/file/FileCFG.h'
	,'./src/engine/utils/StringUtils.h'
]
lib_engine = static_library('engine', engine_file_cpp,
	include_directories: dir_includes
)


# Exec file
# executable('main', './src/main.cpp',
# 	# include_directories: ['include'],
# 	link_with: lib_engine
# )
