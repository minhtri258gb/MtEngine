#define __MT_MODEL_BUILDER_CPP__

#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>

#include "common.h"
#include "engine/file/FileCFG.h"
#include "graphic/Graphic.h"
#include "graphic/models/ModelBuilder.h"
#include "graphic/models/SimpleModel.h"

using namespace std;
using namespace mt;
using namespace mt::graphic;

class ModelBuilder::ModelBuilderImpl
{
public:
	
};

ModelBuilder::ModelBuilder()
{
	// Implement
	this->impl = new ModelBuilderImpl();
}

ModelBuilder::~ModelBuilder()
{
	// Implement
	delete this->impl;
}

Model* ModelBuilder::loadModel(string name)
{
	Model* model = this->createDefaultModel(name);
	if (!model)
	{
		// Load config
		string modelDir = "./res/models/" + name + "/";
		string configPath = modelDir + "info.cfg";
		FileCFG fCFG(configPath);
		fCFG.select("general");
		string modelFile = fCFG.get("model");

		// Load model
		string modelPath = modelDir + modelFile;
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(modelPath,
			  aiProcess_Triangulate
			| aiProcess_FlipUVs
			| aiProcess_GenSmoothNormals
		);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
			throw error(importer.GetErrorString());
		
		// Build mesh
		aiMesh* mesh = scene->mMeshes[0]; // #HARD chỉ load 1 mesh

		vector<vec3> vertices;
		vector<vec2> texcoords;
		vector<vec3> normals;
		for (unsigned int i=0; i<mesh->mNumVertices; i++)
		{
			aiVector3D vertice = mesh->mVertices[i];
			vertices.push_back(vec3(vertice.x, vertice.y, vertice.z));

			if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
			{
				aiVector3D texcoord = mesh->mTextureCoords[0][i];
				texcoords.push_back(vec2(texcoord.x, texcoord.y));
			}
			else
				texcoords.push_back(vec2(0.0f, 0.0f));
			
			aiVector3D normal = mesh->mNormals[i];
			normals.push_back(vec3(normal.x, normal.y, normal.z));
		}

		vector<unsigned int> indices;
		for (unsigned int i=0; i<mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (unsigned int j=0; j<face.mNumIndices; j++)
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
		// 	for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
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


		// vector<Vertex> vertices = {};
		// vector<uint> indices = {};
		// uint boneCount = 0;
		// Animation animation;
		// uint vao = 0;
		// Bone skeleton;
		// uint diffuseTexture;

		// Create memory
		SimpleModel *newModel = new SimpleModel();

		// Read config #TODO

		// Read data #TODO
		// vector<vec3> vertices;
		// vertices.push_back(vec3( 0.5f,  0.5f, 0.0f));
		// vertices.push_back(vec3( 0.5f, -0.5f, 0.0f));
		// vertices.push_back(vec3(-0.5f, -0.5f, 0.0f));
		// vertices.push_back(vec3(-0.5f,  0.5f, 0.0f));
		
		// vector<vec2> texcoords;
		// texcoords.push_back(vec2(1.0f, 1.0f));
		// texcoords.push_back(vec2(1.0f, 0.0f));
		// texcoords.push_back(vec2(0.0f, 0.0f));
		// texcoords.push_back(vec2(0.0f, 1.0f));
		
		// vector<unsigned int> indices;
		// indices.push_back(0);
		// indices.push_back(1);
		// indices.push_back(3);
		// indices.push_back(1);
		// indices.push_back(2);
		// indices.push_back(3);

		newModel->loadVAO(vertices, texcoords, indices);
		newModel->loadTexture("./res/textures/wall.jpg");

		// Override class
		model = newModel;
	}
	return model;
}

Model* ModelBuilder::createDefaultModel(string _name)
{
	if (_name == "box")
		return this->createBox();
	else if (_name == "plane")
		return this->createPlane();
	
	return nullptr;
}

Model* ModelBuilder::createBox()
{
	SimpleModel *model = new SimpleModel();

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

	vector<unsigned int> indices;
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

Model* ModelBuilder::createPlane()
{
	SimpleModel *model = new SimpleModel();

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

	vector<unsigned int> indices;
	indices.push_back(0); indices.push_back(2); indices.push_back(1);
	indices.push_back(1); indices.push_back(2); indices.push_back(3);
	
	model->loadVAO(vertices, texcoords, normals, indices);
	model->loadTexture("./res/textures/default.tga");

	return model;
}
