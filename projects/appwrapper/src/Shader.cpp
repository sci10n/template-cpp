#include "Shader.hpp"
#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

std::string Shader::readFile(const std::string& filePath) const{
	std::ifstream fileStream(filePath, std::ios::in);

	if(!fileStream.is_open()) {
		std::cout << "Could not read file " << filePath << std::endl;
		return "";
	}

	std::string content { std::istreambuf_iterator<char>{fileStream}, {} };
	return content; // Loading line-by-line will *not* work on some GPUs...
}

Shader::~Shader(){
	glDeleteShader(_shaderID);
}

Shader::Shader(const GLuint& type) {
	_shaderID = glCreateShader(type);
}


bool Shader::fromFile(const std::string& path) {
	const std::string source = readFile(path);
	const char *sourcePtr = source.c_str();
	glShaderSource(_shaderID, 1, &sourcePtr, NULL);
	return true;
}

bool Shader::fromString(const char* source) {
	glShaderSource(_shaderID, 1, &source, NULL);
	return true;
}

bool Shader::compile(){
	glCompileShader(_shaderID);
	GLint success;
	GLchar infoLog[512];

	glGetShaderiv(_shaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(_shaderID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
		return false;
	}
	return true;
}

GLuint Shader::getID() const{
	return _shaderID;
}
