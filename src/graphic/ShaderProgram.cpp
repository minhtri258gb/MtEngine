#define __MT_SHADER_PROGRAM_CPP__

#include <fstream>
#include <sstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "common.h"
#include "ShaderProgram.h"
#include "engine/Config.h"

using namespace std;
using namespace mt::engine;
using namespace mt::graphic;


ShaderProgram::ShaderProgram()
{
	this->programId = -1;
}

ShaderProgram::~ShaderProgram()
{
}

void ShaderProgram::init(string _filename, int _flag)
{
	// Get config
	_filename = Config::ins.shader_path + _filename;

	unsigned int vertexShaderId = -1;
	if (_flag & SHADER_TYPE::VERTEX)
		vertexShaderId = this->initShaderPath(_filename+".vs.glsl", SHADER_TYPE::VERTEX);

	unsigned int fragmentShaderId = -1;
	if (_flag & SHADER_TYPE::FRAGMENT)
		fragmentShaderId = this->initShaderPath(_filename+".fs.glsl", SHADER_TYPE::FRAGMENT);

	unsigned int geometryShaderId = -1;
	if (_flag & SHADER_TYPE::GEOMETRY)
		geometryShaderId = this->initShaderPath(_filename+".gs.glsl", SHADER_TYPE::GEOMETRY);

	unsigned int tessControlShaderId = -1;
	if (_flag & SHADER_TYPE::TESS_CONTROL)
		tessControlShaderId = this->initShaderPath(_filename+".cs.glsl", SHADER_TYPE::TESS_CONTROL);

	unsigned int tessEvaluationShaderId = -1;
	if (_flag & SHADER_TYPE::TESS_EVALUATION)
		tessEvaluationShaderId = this->initShaderPath(_filename+".es.glsl", SHADER_TYPE::TESS_EVALUATION);

	// Compile Program
	this->programId = glCreateProgram();
	if (_flag & SHADER_TYPE::VERTEX)
		glAttachShader(this->programId, vertexShaderId);
	if (_flag & SHADER_TYPE::FRAGMENT)
		glAttachShader(this->programId, fragmentShaderId);
	if (_flag & SHADER_TYPE::GEOMETRY)
		glAttachShader(this->programId, geometryShaderId);
	if (_flag & SHADER_TYPE::TESS_CONTROL)
		glAttachShader(this->programId, tessControlShaderId);
	if (_flag & SHADER_TYPE::TESS_EVALUATION)
		glAttachShader(this->programId, tessEvaluationShaderId);
	glLinkProgram(this->programId);

	// Clean
	if (_flag & SHADER_TYPE::VERTEX)
		glDeleteShader(vertexShaderId);
	if (_flag & SHADER_TYPE::FRAGMENT)
		glDeleteShader(fragmentShaderId);
	if (_flag & SHADER_TYPE::GEOMETRY)
		glDeleteShader(geometryShaderId);
	if (_flag & SHADER_TYPE::TESS_CONTROL)
		glDeleteShader(tessControlShaderId);
	if (_flag & SHADER_TYPE::TESS_EVALUATION)
		glDeleteShader(tessEvaluationShaderId);
	
	// Check
	int success;
	char infoLog[512];
	glGetProgramiv(this->programId, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(this->programId, 512, NULL, infoLog);
		throw error(string("Failed to compile vertex shader: ")+infoLog);
	}
}

void ShaderProgram::close()
{
	locations.clear();

	glDeleteProgram(this->programId);
}

void ShaderProgram::use()
{
	glUseProgram(this->programId);
}

void ShaderProgram::addLocation(string _unifromName)
{
	int location = glGetUniformLocation(this->programId, _unifromName.c_str());
	this->locations.push_back(location);
}

void ShaderProgram::setBool(int _locationId, bool _value)
{         
    glUniform1i(this->locations.at(_locationId), (int)_value); 
}

void ShaderProgram::setInt(int _locationId, int _value)
{ 
    glUniform1i(this->locations.at(_locationId), _value); 
}

void ShaderProgram::setFloat(int _locationId, float _value)
{ 
    glUniform1f(this->locations.at(_locationId), _value); 
} 

void ShaderProgram::setVec2(int _locationId, vec2 _value)
{
	glUniform2f(this->locations.at(_locationId), _value.x, _value.y);
}

void ShaderProgram::setVec2I(int _locationId, vec2i _value)
{
	glUniform2i(this->locations.at(_locationId), _value.x, _value.y);
}

void ShaderProgram::setVec3(int _locationId, vec3 _value)
{
	glUniform3f(this->locations.at(_locationId), _value.x, _value.y, _value.z);
}

void ShaderProgram::setVec3I(int _locationId, vec3i _value)
{
	glUniform3i(this->locations.at(_locationId), _value.x, _value.y, _value.z);
}

void ShaderProgram::setVec4(int _locationId, vec4 _value)
{
	glUniform4f(this->locations.at(_locationId), _value.x, _value.y, _value.z, _value.w);
}

void ShaderProgram::setMat4(int _locationId, mat4 _value)
{
	glUniformMatrix4fv(this->locations.at(_locationId), 1, GL_FALSE, &_value[0]);
	
	// debug - begin
	// cout << "=================\n";
	// cout << _value[0][0] << " " << _value[0][1] << " " << _value[0][2] << " " << _value[0][3] << " " << endl;
	// cout << _value[1][0] << " " << _value[1][1] << " " << _value[1][2] << " " << _value[1][3] << " " << endl;
	// cout << _value[2][0] << " " << _value[2][1] << " " << _value[2][2] << " " << _value[2][3] << " " << endl;
	// cout << _value[3][0] << " " << _value[3][1] << " " << _value[3][2] << " " << _value[3][3] << " " << endl;
	// debug - end
}

void ShaderProgram::setListMat4(int _locationId, std::vector<mat4> _value)
{
	glUniformMatrix4fv(this->locations.at(_locationId), _value.size(), GL_FALSE, &_value[0][0]);
}

unsigned int ShaderProgram::initShaderPath(string _filepath, SHADER_TYPE _type)
{
	// Read source
	ifstream shaderFile;
	shaderFile.open(_filepath);
	if (!shaderFile)
		throw error("Unable to open file " + _filepath);

	stringstream shaderStream;
	shaderStream << shaderFile.rdbuf();
	shaderFile.close();
	
	string shaderSrc = shaderStream.str();
	const char* bufferSource = shaderSrc.c_str();

	// Create shader
	unsigned int shaderId;
	switch (_type)
	{
	case VERTEX:
		shaderId = glCreateShader(GL_VERTEX_SHADER);
		break;
	case FRAGMENT:
		shaderId = glCreateShader(GL_FRAGMENT_SHADER);
		break;
	case GEOMETRY:
		shaderId = glCreateShader(GL_GEOMETRY_SHADER);
		break;
	case TESS_CONTROL:
		shaderId = glCreateShader(GL_TESS_CONTROL_SHADER);
		break;
	case TESS_EVALUATION:
		shaderId = glCreateShader(GL_TESS_EVALUATION_SHADER);
		break;
	}
	
	glShaderSource(shaderId, 1, &bufferSource, NULL);
	glCompileShader(shaderId);

	int success;
	char infoLog[512];
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(shaderId, 512, NULL, infoLog);
		throw error("Failed to compile shader: "+_filepath+'\n'+infoLog);
	}

	return shaderId;
}
