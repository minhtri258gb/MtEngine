#ifndef __MT_SHADER_PROGRAM_H__
#define __MT_SHADER_PROGRAM_H__

namespace mt {
namespace graphic {

class ShaderProgram
{

public:

	// Datatype
	enum SHADER_TYPE
	{
		VERTEX = 1 << 0,
		FRAGMENT = 1 << 1,
		GEOMETRY = 1 << 2,
		TESS_CONTROL = 1 << 3,
		TESS_EVALUATION = 1 << 4
	};

	// Variable
	unsigned int programId;
	std::vector<int> locations;

	// Forward
	ShaderProgram();
	~ShaderProgram();
	void init(std::string filename, int flag);
	void close();

	// Native
	void use();
	void addLocation(std::string unifromName);
	void setBool(int locationId, bool value);
	void setInt(int locationId, int value);
	void setFloat(int locationId, float value);
	void setVec2(int locationId, vec2 value);
	void setVec2I(int locationId, vec2i value);
	void setVec3(int locationId, vec3 value);
	void setVec3I(int locationId, vec3i value);
	void setVec4(int locationId, vec4 value);
	void setMat4(int locationId, mat4 value);
	void setListMat4(int locationId, std::vector<mat4> value);

private:

	// Forward
	unsigned int initShaderPath(std::string filepath, SHADER_TYPE type);

};

}}

#endif
