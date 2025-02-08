#define	__MT_ANIMATION_MODEL_CPP__

#include <cstdlib>
#include <unordered_map>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>

#include <stb_image.h>

#include "common.h"
#include "engine/Config.h"
#include "engine/Timer.h"
#include "../../Graphic.h"
#include "AnimationModel.h"

#include "../../buffer/VertexArrayObject.h"
#include "../../texture/Texture.h"

using namespace std;
using namespace mt;
using namespace mt::engine;
using namespace mt::graphic;

inline mat4 assimpToMtMatrix(aiMatrix4x4 mat) {
	mat4 m;
	for (int y = 0; y < 4; y++)
		for (int x = 0; x < 4; x++)
			m[x*4+y] = mat[y][x];
	return m;
}

inline vec3 assimpToMtVec3(aiVector3D vec) {
	return vec3(vec.x, vec.y, vec.z);
}

inline quat assimpToMtQuat(aiQuaternion _q) {
	quat q;
	q.x = _q.x;
	q.y = _q.y;
	q.z = _q.z;
	q.w = _q.w;
	return q;
}

// vertex of an animated model
struct Vertex {
	vec3 position;
	vec3 normal;
	vec2 uv;
	vec4i boneIds;
	vec4 boneWeights;
};

// structure to hold bone tree (skeleton)
struct Bone {
	int id = 0; // position of the bone in final upload array
	string name = "";
	mat4 offset;
	vector<Bone> children = {};
};

// sturction representing an animation track
struct BoneTransformTrack {
	vector<float> positionTimestamps = {};
	vector<float> rotationTimestamps = {};
	vector<float> scaleTimestamps = {};

	vector<vec3> positions = {};
	vector<quat> rotations = {};
	vector<vec3> scales = {};
};

// structure containing animation information
struct Animation {
	float duration = 0.0f;
	float ticksPerSecond = 1.0f;
	unordered_map<string, BoneTransformTrack> boneTransforms = {};
};

class AnimationModel::AnimationModelImpl {
public:
	VertexArrayObject VAO;
	Texture texture;

	uint boneCount = 0;
	Animation animation;
	Bone skeleton;
	mat4 globalInverseTransform;

	mat4 identity;
	vector<mat4> currentPose = {};
	// vector<mat4> currentPose = {};

	AnimationModelImpl() {
	}

	// a recursive function to read all bones and form skeleton
	bool readSkeleton(Bone& boneOutput, aiNode* node, unordered_map<string, pair<int, mat4>>& boneInfoTable) {

		if (boneInfoTable.find(node->mName.C_Str()) != boneInfoTable.end()) { // if node is actually a bone
			boneOutput.name = node->mName.C_Str();
			boneOutput.id = boneInfoTable[boneOutput.name].first;
			boneOutput.offset = boneInfoTable[boneOutput.name].second;

			for (unsigned int i = 0; i < node->mNumChildren; i++) {
				Bone child;
				readSkeleton(child, node->mChildren[i], boneInfoTable);
				boneOutput.children.push_back(child);
			}
			return true;
		}
		else { // find bones in children
			for (unsigned int i = 0; i < node->mNumChildren; i++) {
				if (readSkeleton(boneOutput, node->mChildren[i], boneInfoTable)) {
					return true;
				}

			}
		}
		return false;
	}

	void loadModel(const aiScene* scene, aiMesh* mesh, vector<Vertex>& verticesOutput, vector<uint>& indicesOutput, Bone& skeletonOutput, uint &nBoneCount) {

		verticesOutput = {};
		indicesOutput = {};
		//load position, normal, uv
		for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
			//process position
			Vertex vertex;
			vec3 vector;
			vector.x = mesh->mVertices[i].x;
			vector.y = mesh->mVertices[i].y;
			vector.z = mesh->mVertices[i].z;
			vertex.position = vector;
			//process normal
			vector.x = mesh->mNormals[i].x;
			vector.y = mesh->mNormals[i].y;
			vector.z = mesh->mNormals[i].z;
			vertex.normal = vector;
			//process uv
			vec2 vec;
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.uv = vec;

			vertex.boneIds = vec4i();
			vertex.boneWeights = vec4();

			verticesOutput.push_back(vertex);
		}

		//load boneData to vertices
		unordered_map<string, pair<int, mat4>> boneInfo = {};
		vector<uint> boneCounts;
		boneCounts.resize(verticesOutput.size(), 0);
		nBoneCount = mesh->mNumBones;

		//loop through each bone
		for (uint i = 0; i < nBoneCount; i++) {
			aiBone* bone = mesh->mBones[i];
			mat4 m = assimpToMtMatrix(bone->mOffsetMatrix);
			boneInfo[bone->mName.C_Str()] = { i, m };

			//loop through each vertex that have that bone
			for (unsigned int j = 0; j < bone->mNumWeights; j++) {
				uint id = bone->mWeights[j].mVertexId;
				float weight = bone->mWeights[j].mWeight;
				boneCounts[id]++;
				switch (boneCounts[id]) {
				case 1:
					verticesOutput[id].boneIds.x = i;
					verticesOutput[id].boneWeights.x = weight;
					break;
				case 2:
					verticesOutput[id].boneIds.y = i;
					verticesOutput[id].boneWeights.y = weight;
					break;
				case 3:
					verticesOutput[id].boneIds.z = i;
					verticesOutput[id].boneWeights.z = weight;
					break;
				case 4:
					verticesOutput[id].boneIds.w = i;
					verticesOutput[id].boneWeights.w = weight;
					break;
				default:
					//cout << "err: unable to allocate bone to vertex" << endl;
					break;

				}
			}
		}

		//normalize weights to make all weights sum 1
		for (long long unsigned int i = 0; i < verticesOutput.size(); i++) {
			vec4 & boneWeights = verticesOutput[i].boneWeights;
			float totalWeight = boneWeights.x + boneWeights.y + boneWeights.z + boneWeights.w;
			if (totalWeight > 0.0f) {
				verticesOutput[i].boneWeights = vec4(
					boneWeights.x / totalWeight,
					boneWeights.y / totalWeight,
					boneWeights.z / totalWeight,
					boneWeights.w / totalWeight
				);
			}
		}

		//load indices
		for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
			aiFace& face = mesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; j++)
				indicesOutput.push_back(face.mIndices[j]);
		}

		// create bone hirerchy
		readSkeleton(skeletonOutput, scene->mRootNode, boneInfo);
	}

	void loadAnimation(const aiScene* scene, Animation& animation) {
		//loading  first Animation
		aiAnimation* anim = scene->mAnimations[0];

		if (anim->mTicksPerSecond != 0.0f)
			animation.ticksPerSecond = anim->mTicksPerSecond;
		else
			animation.ticksPerSecond = 1;


		animation.duration = anim->mDuration * anim->mTicksPerSecond;
		animation.boneTransforms = {};

		//load positions rotations and scales for each bone
		// each channel represents each bone
		for (unsigned int i = 0; i < anim->mNumChannels; i++) {
			aiNodeAnim* channel = anim->mChannels[i];
			BoneTransformTrack track;
			for (unsigned int j = 0; j < channel->mNumPositionKeys; j++) {
				track.positionTimestamps.push_back(channel->mPositionKeys[j].mTime);
				track.positions.push_back(assimpToMtVec3(channel->mPositionKeys[j].mValue));
			}
			for (unsigned int j = 0; j < channel->mNumRotationKeys; j++) {
				track.rotationTimestamps.push_back(channel->mRotationKeys[j].mTime);
				track.rotations.push_back(assimpToMtQuat(channel->mRotationKeys[j].mValue));
			}
			for (unsigned int j = 0; j < channel->mNumScalingKeys; j++) {
				track.scaleTimestamps.push_back(channel->mScalingKeys[j].mTime);
				track.scales.push_back(assimpToMtVec3(channel->mScalingKeys[j].mValue));
			}
			animation.boneTransforms[channel->mNodeName.C_Str()] = track;
		}
	}

	pair<uint, float> getTimeFraction(vector<float>& times, float& dt) {
		uint segment = 0;
		while (dt > times[segment])
			segment++;
		float start = times[segment - 1];
		float end = times[segment];
		float frac = (dt - start) / (end - start);
		return {segment, frac};
	}

	void getPose(Bone& skeletion, float dt, vector<mat4>& output, mat4 &parentTransform) {
		BoneTransformTrack& btt = animation.boneTransforms[skeletion.name];
		dt = fmod(dt, animation.duration);
		pair<uint, float> fp;
		//calculate interpolated position
		fp = getTimeFraction(btt.positionTimestamps, dt);

		vec3 position1 = btt.positions[fp.first - 1];
		vec3 position2 = btt.positions[fp.first];
		vec3 position = position1.mix(position2, fp.second);

		//calculate interpolated rotation
		fp = getTimeFraction(btt.rotationTimestamps, dt);
		quat rotation1 = btt.rotations[fp.first - 1];
		quat rotation2 = btt.rotations[fp.first];
		quat rotation = rotation1.slerp(rotation2, fp.second);

		//calculate interpolated scale
		fp = getTimeFraction(btt.scaleTimestamps, dt);
		vec3 scale1 = btt.scales[fp.first - 1];
		vec3 scale2 = btt.scales[fp.first];
		vec3 scale = scale1.mix(scale2, fp.second);

		// calculate localTransform
		mat4 localTransform;
		localTransform.translate(position);
		localTransform.rotate(rotation);
		localTransform.scale(scale);

		mat4 globalTransform = parentTransform * localTransform;
		output[skeletion.id] = globalInverseTransform * globalTransform * skeletion.offset;

		//update values for children bones
		for (Bone& child : skeletion.children) {
			getPose(child, dt, output, globalTransform);
		}
		//cout << dt << " => " << position.x << ":" << position.y << ":" << position.z << ":" << endl;
	}

};

ShaderProgram AnimationModel::shader;

AnimationModel::AnimationModel()
{
	// Implement
	this->impl = new AnimationModelImpl();

	//load model file
	Assimp::Importer importer;
	const char* filePath = "./res/models/man/model.dae";
	const aiScene* scene = importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		cout << "ERROR::ASSIMP::" << importer.GetErrorString() << endl;
	}
	aiMesh* mesh = scene->mMeshes[0];

	//as the name suggests just inverse the global transform
	this->impl->globalInverseTransform = assimpToMtMatrix(scene->mRootNode->mTransformation);
	this->impl->globalInverseTransform.inverse();

	vector<Vertex> vertices = {};
	vector<uint> indices = {};
	this->impl->loadModel(scene, mesh, vertices, indices, this->impl->skeleton, this->impl->boneCount);
	this->impl->loadAnimation(scene, this->impl->animation);

	// Prepare data
	vector<vec3> position_tmp;
	vector<vec2> texcoords_tmp;
	vector<vec3> normals_tmp;
	vector<vec4i> bondIds_tmp;
	vector<vec4> weights_tmp;
	vector<unsigned int> indices_tmp;
	for (Vertex v : vertices)
	{
		position_tmp.push_back(v.position);
		texcoords_tmp.push_back(v.uv);
		normals_tmp.push_back(v.normal);
		bondIds_tmp.push_back(v.boneIds);
		weights_tmp.push_back(v.boneWeights);
	}
	for (uint id : indices)
	{
		indices_tmp.push_back(id);
	}

	// Init Vertices Buffer
	this->impl->VAO.init();
	this->impl->VAO.bind();
	this->impl->VAO.addAttribute(position_tmp);
	this->impl->VAO.addAttribute(texcoords_tmp);
	this->impl->VAO.addAttribute(normals_tmp);
	this->impl->VAO.addAttribute(bondIds_tmp);
	this->impl->VAO.addAttribute(weights_tmp);
	this->impl->VAO.addIndices(indices_tmp);
	this->impl->VAO.unbind();

	this->impl->texture.init("./res/models/man/diffuse.png");

	this->impl->currentPose.resize(this->impl->boneCount, this->impl->identity); // use this for no animation
}

AnimationModel::~AnimationModel()
{
	// Implement
	delete this->impl;
}

void AnimationModel::update()
{
}

void AnimationModel::render()
{
	// Shader
	this->shader.use();

	// model matrix
	mat4 modelMatrix;
	modelMatrix.translate(vec3(0.0f, 1.0f, -5.0f));
	modelMatrix.rotate(quat(Math::toRadian(0.0f), vec3(0, 1, 0)));
	modelMatrix.scale(vec3(.3f, .3f, .3f));
	this->shader.setMat4(2, modelMatrix);

	// bone matrix
	float elapsedTime = (float)glfwGetTime();
	this->impl->getPose(this->impl->skeleton, elapsedTime, this->impl->currentPose, this->impl->identity);
	this->shader.setListMat4(3, this->impl->currentPose);

	// draw
	this->impl->texture.bind();

	this->impl->VAO.bind();
	this->impl->VAO.drawElementTriangle();
	this->impl->VAO.unbind();
}
