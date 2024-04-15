
project('MT Engine', 'cpp',
	version: '1.0.0',
	default_options : [
		'c_std=gnu23',
		'cpp_std=gnu++2a',
		'warning_level=3',
		'b_ndebug=true',
	],
	license: 'MIT'
)

cpp = meson.get_compiler('cpp')
dir_base = meson.current_source_dir()
dir_lib = join_paths(dir_base, 'lib')
dir_lib_msys2 = 'D:/Programs/MSYS2/mingw64/lib'

# Include
dir_includes = [
	'./src',
	'./inc',
	'D:/Programs/MSYS2/mingw64/include',
	'D:/Programs/MSYS2/mingw64/include/bullet',
	'D:/Programs/MSYS2/mingw64/include/freetype2'
]


# Dependencies
glfw3 = cpp.find_library('glfw3', dirs: dir_lib_msys2)
assimp = cpp.find_library('assimpd', dirs: dir_lib)
tinygltf = cpp.find_library('tinygltf', dirs: dir_lib)
freetype = cpp.find_library('freetype', dirs: dir_lib_msys2)

bullet_collision = cpp.find_library('BulletCollision', dirs: dir_lib_msys2)
bullet_dynamics = cpp.find_library('BulletDynamics', dirs: dir_lib_msys2)
linear_math = cpp.find_library('LinearMath', dirs: dir_lib_msys2)

# reactphysics3d = cpp.find_library('reactphysics3d', dirs: dir_lib)
# ode = cpp.find_library('ode_double', dirs: dir_lib_msys2)
# newton_dynamic = cpp.find_library('dNewton', dirs: dir_lib_msys2)

bass = cpp.find_library('bass', dirs: dir_lib)


mtengine = library('mtengine',
	[
		'./src/engine/library.cpp'
		,'./src/engine/Config.cpp'
		,'./src/engine/Input.cpp'
		,'./src/engine/Timer.cpp'
		,'./src/engine/Random.cpp'
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
		,'./src/engine/math/Math.cpp'
		,'./src/engine/file/Image.cpp'
		,'./src/engine/file/FileCFG.cpp'
		,'./src/engine/file/FileINI.cpp'
		,'./src/engine/utils/StringUtils.cpp'
		,'./src/engine/utils/FilePathUtils.cpp'
	],
	include_directories: dir_includes
	# dependencies: [zstd, dwarf, cpptrace]
)

mtgraphic = library('mtgraphic',
	[
		'./src/graphic/glad.cpp'
		,'./src/graphic/Graphic.cpp'
		,'./src/graphic/Scene.cpp'
		,'./src/graphic/GUI.cpp'
		,'./src/graphic/Camera.cpp'
		,'./src/graphic/ShaderProgram.cpp'
		,'./src/graphic/ShaderProgramMgr.cpp'
		,'./src/graphic/buffer/VertexArrayObject.cpp'
		,'./src/graphic/buffer/VertexBufferObject.cpp'
		,'./src/graphic/buffer/ElementBufferObject.cpp'
		,'./src/graphic/buffer/FrameBuffer.cpp'
		,'./src/graphic/FrustumCulling.cpp'
		,'./src/graphic/texture/Texture.cpp'
		,'./src/graphic/texture/TextureAtlas.cpp'
		,'./src/graphic/texture/TextureCube.cpp'
		,'./src/graphic/models/ModelMgr.cpp'
		,'./src/graphic/models/ModelBuilder.cpp'
		,'./src/graphic/models/Model.cpp'
		,'./src/graphic/models/ColorModel.cpp'
		,'./src/graphic/models/SimpleModel.cpp'
		,'./src/graphic/models/animation/AnimationModel.cpp'
		,'./src/graphic/particles/Sprite.cpp'
		,'./src/graphic/particles/Particle.cpp'
		,'./src/graphic/particles/Emitter.cpp'
		,'./src/graphic/sky/SkyBox.cpp'
		,'./src/graphic/sky/Sun.cpp'
		,'./src/graphic/terrain/StaticTerrain.cpp'
		,'./src/graphic/terrain/Terrain.cpp'
		,'./src/graphic/terrain/TerrainPart.cpp'
		,'./src/graphic/terrain/TerrainQuad.cpp'
		,'./src/graphic/bsp/BspSourceMap.cpp'
		,'./src/graphic/bsp/BspQuakeMap.cpp'
		,'./src/graphic/bsp/BspMap.cpp'
		,'./src/graphic/bsp/bsp4/Math.cpp'
		,'./src/graphic/bsp/bsp4/Q3BspLoader.cpp'
		,'./src/graphic/bsp/bsp4/Q3BspMap.cpp'
		,'./src/graphic/bsp/bsp4/Q3BspPatch.cpp'
		,'./src/graphic/bsp/bsp4/StringHelpers.cpp'
		,'./src/graphic/bsp/bsp5/bsp.cpp'
		,'./src/graphic/bsp/bsp5/bezier.cpp'
		,'./src/graphic/bsp/bsp5/frustum.cpp'
		# ,' ./src/graphic/bsp/bsp5/q3_shader.cpp'
		# ,' ./src/graphic/bsp/bsp5/shader.cpp'
		# ,' ./src/graphic/bsp/bsp5/shader_loader.cpp'
		# ,' ./src/graphic/bsp/bsp5/texture_loader.cpp'
		,'./src/graphic/hud/Text.cpp'
		,'./src/graphic/other/DebugFrame.cpp'
	],
	include_directories: dir_includes,
	link_with: mtengine,
	dependencies: [tinygltf, assimp, freetype, glfw3],
)

mtphysic = library('mtphysic',
	[
		'./src/physic/Physic.cpp'
		,'./src/physic/body/RigidBody.cpp'
	],
	include_directories: dir_includes,
	link_with: mtengine,
	dependencies: [bullet_collision, bullet_dynamics, linear_math],
)

mtaudio = library('mtaudio',
	[
		'./src/audio/Audio.cpp'
	],
	include_directories: dir_includes,
	link_with: [mtengine, mtgraphic],
	dependencies: [bass],
)

mtgame = library('mtgame',
	[
		'./src/game/Game.cpp'
		,'./src/game/CommandMgr.cpp'
		,'./src/game/Command.cpp'
		,'./src/game/maps/MapBuilder.cpp'
		,'./src/game/maps/Map.cpp'
		,'./src/game/maps/TestMap.cpp'
		,'./src/game/maps/LobbyMap.cpp'
		,'./src/game/maps/AreaBoundMap.cpp'
		,'./src/game/entities/Entity.cpp'
		,'./src/game/entities/TestEnt.cpp'
		,'./src/game/entities/TestAnimEnt.cpp'
		,'./src/game/entities/TestParticleEnt.cpp'
		,'./src/game/entities/TestEmitterEnt.cpp'
		,'./src/game/entities/GroundEnt.cpp'
		,'./src/game/hud/Screen.cpp'
		,'./src/game/hud/Hud.cpp'
		,'./src/game/hud/HudFpsCount.cpp'
	],
	include_directories: dir_includes,
	link_with: [mtengine, mtaudio, mtphysic, mtgraphic],
	dependencies: [],
)

mtmod = library('mtmod',
	[
		'./src/mod/Plugin.cpp'
		,'./src/mod/PluginSystem.cpp'
	],
	include_directories: dir_includes,
	link_with: mtengine,
)

mttest = library('mttest',
	[
		'./src/test/Test.cpp'
		# ,'./src/test/file/TestJson.cpp'
		# ,'./src/test/file/FileJson.cpp'
		,'./src/test/audio/Audio.cpp'
		,'./src/test/audio/AudioMgr.cpp'
		,'./src/test/audio/Sound.cpp'
		,'./src/test/technique/TestTechnique.cpp'
		,'./src/test/thread/Thread.cpp'
		,'./src/test/TestFileCFG.cpp'
		,'./src/test/TestMath.cpp'
		,'./src/test/TestString.cpp'
	],
	include_directories: dir_includes,
	link_with: mtengine,
	dependencies: bass
)

executable('main', './src/main.cpp',
	# include_directories: dir_includes,
	link_with: [mttest, mtgame]
)
