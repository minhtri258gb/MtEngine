#define __MT_MODEL_BUILDER_CPP__

#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>

#include <tiny_gltf.h>
#include <tiny_obj_loader.h>

#include "common.h"
#include "engine/Config.h"
#include "engine/Log.h"
#include "engine/file/FileCFG.h"
#include "engine/utils/StringUtils.h"
#include "engine/utils/FilePathUtils.h"
#include "graphic/Graphic.h"
#include "graphic/models/ModelBuilder.h"
#include "graphic/models/SimpleModel.h"
#include "graphic/models/ColorModel.h"

using namespace std;
using namespace mt;
using namespace mt::engine;
using namespace mt::graphic;


class ModelBuilder::ModelBuilderImpl {
public:
	void loadByAssimp(
		string modelPath
		,vector<vec3>& vertices
		,vector<vec4>& colors
		,vector<vec2>& texcoords
		,vector<vec3>& normals
		,vector<uint>& indices
	);
	void loadByTinyGLFT(
		string modelPath
		,vector<vec3>& vertices
		,vector<vec4>& colors
		,vector<vec2>& texcoords
		,vector<vec3>& normals
		,vector<uint>& indices
	);
	void loadByTinyOBJLoader(
		string modelDir
		,string modelPath
		,vector<vec3>& vertices
		,vector<vec4>& colors
		,vector<vec2>& texcoords
		,vector<vec3>& normals
		,vector<uint>& indices
	);
};

ModelBuilder::ModelBuilder() {
	LOG("ModelBuilder");
	try {

		// Implement
		this->impl = new ModelBuilderImpl();
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}

ModelBuilder::~ModelBuilder() {
	LOG("~ModelBuilder");

	// Implement
	delete this->impl;
}

Model* ModelBuilder::loadModel(string name) {
	LOG("loadModel");
	try {

		Model* model = nullptr;

		// Load config
		string modelDir = Config::ins.model_path + name + "/";
		string configPath = modelDir + "info.cfg";
		FileCFG fCFG(configPath);

		fCFG.select("graphic");
		string type = fCFG.get("type");
		string modelFile = fCFG.get("model");
		vec3 modelPos = fCFG.getVec3("pos");
		vec3 modelRot = fCFG.getVec3("rot");
		vec3 modelScale = fCFG.getVec3("scale");

		// Create model
		if (type == "shape") {
			model = this->createDefaultModel(modelFile);
			model->pos = modelPos;
			model->rot = quat(Math::toRadian(modelRot.x), Math::toRadian(modelRot.y), Math::toRadian(modelRot.z));
			model->scale = modelScale;
		}
		else if (type == "color") {

			ColorModel *newModel = new ColorModel(name);
			newModel->pos = modelPos;
			newModel->rot = quat(Math::toRadian(modelRot.x), Math::toRadian(modelRot.y), Math::toRadian(modelRot.z));
			newModel->scale = modelScale;

			// Load model
			string modelPath = modelDir + modelFile;

			vector<vec3> vertices;
			vector<vec4> colors;
			vector<vec2> texcoords;
			vector<vec3> normals;
			vector<uint> indices;

			// string ext = FilePathUtils::getExtension(modelPath);
			// if (ext == "obj")
			// 	impl->loadByTinyOBJLoader(modelDir, modelPath, vertices, colors, texcoords, normals, indices);
			// else if (ext == "glb" || ext == "glft")
			// 	impl->loadByTinyGLFT(modelPath, vertices, colors, texcoords, normals, indices);
			// else
			impl->loadByAssimp(modelPath, vertices, colors, texcoords, normals, indices);

			newModel->loadVAO(vertices, colors, indices);

			model = newModel; // Override class
		}
		else { // simple

			string textureFile = fCFG.get("texture");

			SimpleModel *newModel = new SimpleModel(name);
			newModel->pos = modelPos;
			newModel->rot = quat(Math::toRadian(modelRot.x), Math::toRadian(modelRot.y), Math::toRadian(modelRot.z));
			newModel->scale = modelScale;

			// Load model
			string modelPath = modelDir + modelFile;

			vector<vec3> vertices;
			vector<vec4> colors;
			vector<vec2> texcoords;
			vector<vec3> normals;
			vector<uint> indices;

			// string ext = FilePathUtils::getExtension(modelPath);
			// if (ext == "obj")
			// 	impl->loadByTinyOBJLoader(modelDir, modelPath, vertices, colors, texcoords, normals, indices);
			// else if (ext == "glb" || ext == "glft")
			// 	impl->loadByTinyGLFT(modelPath, vertices, colors, texcoords, normals, indices);
			// else
			impl->loadByAssimp(modelPath, vertices, colors, texcoords, normals, indices);

			newModel->loadVAO(vertices, texcoords, indices);

			newModel->loadTexture(modelDir + textureFile);

			model = newModel; // Override class
		}

		return model;
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}

Model* ModelBuilder::createDefaultModel(string _name) {
	LOG("createDefaultModel");
	try {
		if (_name == "box")
			return this->createBox();
		else if (_name == "plane")
			return this->createPlane();

		return nullptr;
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}

Model* ModelBuilder::createBox() {
	LOG("createBox");
	try {

		SimpleModel *model = new SimpleModel("default_box");

		vector<vec3> vertices;
		vertices.push_back(vec3( 1.0f,  1.0f,  1.0f));
		vertices.push_back(vec3( 1.0f,  1.0f, -1.0f));
		vertices.push_back(vec3( 1.0f, -1.0f,  1.0f));
		vertices.push_back(vec3( 1.0f, -1.0f, -1.0f));
		vertices.push_back(vec3(-1.0f,  1.0f,  1.0f));
		vertices.push_back(vec3(-1.0f,  1.0f, -1.0f));
		vertices.push_back(vec3(-1.0f, -1.0f,  1.0f));
		vertices.push_back(vec3(-1.0f, -1.0f, -1.0f));

		// vector<vec2> texcoords; // crash
		// texcoords.push_back(vec2(1.0f, 1.0f));
		// texcoords.push_back(vec2(1.0f, 0.0f));
		// texcoords.push_back(vec2(1.0f, 1.0f));
		// texcoords.push_back(vec2(1.0f, 0.0f));
		// texcoords.push_back(vec2(0.0f, 1.0f));
		// texcoords.push_back(vec2(0.0f, 0.0f));
		// texcoords.push_back(vec2(0.0f, 1.0f));
		// texcoords.push_back(vec2(0.0f, 0.0f));

		vector<uint> indices;
		indices.push_back(0); indices.push_back(1); indices.push_back(3);
		indices.push_back(0); indices.push_back(3); indices.push_back(2);
		indices.push_back(6); indices.push_back(7); indices.push_back(5);
		indices.push_back(6); indices.push_back(5); indices.push_back(4);
		indices.push_back(2); indices.push_back(3); indices.push_back(7);
		indices.push_back(2); indices.push_back(7); indices.push_back(6);
		indices.push_back(4); indices.push_back(5); indices.push_back(1);
		indices.push_back(4); indices.push_back(1); indices.push_back(0);
		indices.push_back(6); indices.push_back(4); indices.push_back(0);
		indices.push_back(6); indices.push_back(0); indices.push_back(2);
		indices.push_back(5); indices.push_back(7); indices.push_back(3);
		indices.push_back(5); indices.push_back(3); indices.push_back(1);

		model->loadVAO(vertices, indices);

		// model->texture.init("./res/textures/default.png");

		return model;
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}

Model* ModelBuilder::createPlane() {
	LOG("createPlane");
	try {

		SimpleModel *model = new SimpleModel("default_plane");

		vector<vec3> vertices;
		vertices.push_back(vec3(-0.5f, 0.0f, -0.5f));
		vertices.push_back(vec3( 0.5f, 0.0f, -0.5f));
		vertices.push_back(vec3(-0.5f, 0.0f,  0.5f));
		vertices.push_back(vec3( 0.5f, 0.0f,  0.5f));

		vector<vec2> texcoords;
		texcoords.push_back(vec2(0.0f, 1.0f));
		texcoords.push_back(vec2(1.0f, 1.0f));
		texcoords.push_back(vec2(0.0f, 0.0f));
		texcoords.push_back(vec2(1.0f, 0.0f));

		vector<vec3> normals;
		normals.push_back(vec3(0.0f, 1.0f, 0.0f));
		normals.push_back(vec3(0.0f, 1.0f, 0.0f));
		normals.push_back(vec3(0.0f, 1.0f, 0.0f));
		normals.push_back(vec3(0.0f, 1.0f, 0.0f));

		vector<uint> indices;
		indices.push_back(0); indices.push_back(2); indices.push_back(1);
		indices.push_back(1); indices.push_back(2); indices.push_back(3);

		model->loadVAO(vertices, texcoords, normals, indices);
		model->loadTexture("./res/textures/default.tga");

		return model;
	}
	catch (Exception e) {
		track(e);
		throw e;
	}
}


// ModelBuilderImpl
void ModelBuilder::ModelBuilderImpl::loadByAssimp(
	string modelPath
	,vector<vec3>& vertices
	,vector<vec4>& colors
	,vector<vec2>& texcoords
	,vector<vec3>& normals
	,vector<uint>& indices
) {
	LOG("loadByAssimp");

	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(modelPath,
		  aiProcess_Triangulate
		| aiProcess_FlipUVs
		| aiProcess_GenSmoothNormals
	);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		throw error("ASSIMP_SCENE_ERROR", importer.GetErrorString());

	// Build mesh
	aiMesh* mesh = scene->mMeshes[0]; // #HARD chỉ load 1 mesh

	for (uint i=0; i<mesh->mNumVertices; i++) {
		// Vertices
		aiVector3D vertice = mesh->mVertices[i];
		vertices.push_back(vec3(vertice.x, vertice.y, vertice.z));

		// TexCoord
		if (mesh->mTextureCoords[0]) { // does the mesh contain texture coordinates?
			aiVector3D texcoord = mesh->mTextureCoords[0][i];
			texcoords.push_back(vec2(texcoord.x, texcoord.y));
		}
		else
			texcoords.push_back(vec2(0.0f, 0.0f));

		// Normal
		aiVector3D normal = mesh->mNormals[i];
		normals.push_back(vec3(normal.x, normal.y, normal.z));

		// Color
		if (mesh->mColors[0] != nullptr) {
			aiColor4D color = mesh->mColors[0][i];
			colors.push_back(vec4(color.r, color.g, color.b, color.a));
		}
		else
			colors.push_back(vec4(1, 1, 1, 1));
	}

	for (uint i=0; i<mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];
		for (uint j=0; j<face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}


	// if (mesh->mMaterialIndex >= 0)
	// {
	// 	aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
	// 	vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
	// 	textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
	// 	vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
	// 	textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	// }

	// vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName)
	// {
	// 	vector<Texture> textures;
	// 	for(uint i = 0; i < mat->GetTextureCount(type); i++)
	// 	{
	// 	aiString str;
	// 	mat->GetTexture(type, i, &str);
	// 	Texture texture;
	// 	texture.id = TextureFromFile(str.C_Str(), directory);
	// 	texture.type = typeName;
	// 	texture.path = str;
	// 	textures.push_back(texture);
	// 	}
	// 	return textures;
	// }

	// vector<vec2> texcoords;
	// for (short i=0; i<mesh->mNum  mNumVertices; i++)
	// {
	// 	aiVector3D aiVec3 = mesh->mVertices[i];
	// 	vertices.push_back(vec3(aiVec3.x, aiVec3.y, aiVec3.z));
	// }
}

void ModelBuilder::ModelBuilderImpl::loadByTinyGLFT(
		string modelPath
		,vector<vec3>& vertices
		,vector<vec4>& colors
		,vector<vec2>& texcoords
		,vector<vec3>& normals
		,vector<uint>& indices
) {
	LOG("loadByTinyGLFT");

	tinygltf::Model model;
	tinygltf::TinyGLTF loader;
	string err;
	string warn;

	bool isLoaded = false;
	if (StringUtils::endWith(modelPath, "glft"))
		isLoaded = loader.LoadASCIIFromFile(&model, &err, &warn, modelPath.c_str());
	else
		isLoaded = loader.LoadBinaryFromFile(&model, &err, &warn, modelPath.c_str());

	if (!warn.empty())
		cout << "[WARNING] " << warn << endl;
	if (!err.empty())
		cout << "[ERROR] " << err << endl;
	if (!isLoaded)
		throw error("TINYGIFT_LOAD_FAIL", "Faild to load Model with tinyglft");

	// int a=1;

	// #TODO
}

void ModelBuilder::ModelBuilderImpl::loadByTinyOBJLoader(
	string modelDir
	,string modelPath
	,vector<vec3>& vertices
	,vector<vec4>& colors
	,vector<vec2>& texcoords
	,vector<vec3>& normals
	,vector<uint>& indices
) {
	LOG("loadByTinyOBJLoader");

	tinyobj::attrib_t inattrib;
	vector<tinyobj::shape_t> inshapes;
	std::vector<tinyobj::material_t> materials;
	std::string warn;
	std::string err;
	// bool ret = tinyobj::LoadObj(&inattrib, &inshapes, &materials, &err, modelPath.c_str(), modelDir.c_str(), true);
	// int a = 1;

	uint sizeBuffer = inattrib.vertices.size();
	vector<bool> hasVertices(sizeBuffer, false);
	vector<bool> hasColors(sizeBuffer, false);
	vector<bool> hasTexcoords(sizeBuffer, false);
	vector<bool> hasNormals(sizeBuffer, false);
	vertices.resize(sizeBuffer, vec3());
	colors.resize(sizeBuffer, vec4());
	texcoords.resize(sizeBuffer, vec2());
	normals.resize(sizeBuffer, vec3());

	for (uint i=0, sz=inshapes.size(); i<sz; i++) {
		tinyobj::shape_t inshape = inshapes.at(i);
		// inshape.mesh.num_face_vertices // #TODO chưa xử lý
		vector<tinyobj::index_t> indicesObj = inshape.mesh.indices;

		// indicesObj
	}
}
