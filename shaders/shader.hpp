#ifndef SHADER_HPP
#define SHADER_HPP

#include <GL/glew.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
  public:
	// the program ID
	unsigned int ID;

	// Consrtuctor reads and builds the shader
	Shader(const char *vertexPath, const char *fragmentPath)
	{
		// 1. Retrieve vertex and fragment source codes from files
		std::string vShaderStr;
		std::string fShaderStr;
		try
		{
			// open file
			std::ifstream vShaderFile(vertexPath);
			std::ifstream fShaderFile(fragmentPath);
			std::stringstream vShaderStream;
			std::stringstream fShaderStream;
			// read file's buffer contents into stream
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			// close file handles
			vShaderFile.close();
			fShaderFile.close();
			vShaderStr = vShaderStream.str();
			fShaderStr = fShaderStream.str();
		}
		catch (std::ifstream::failure e)
		{
			throw std::runtime_error("ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ");
		}

		const char *vShaderCode = vShaderStr.c_str();
		const char *fShaderCode = fShaderStr.c_str();

		// 2. Compile the shaders
		unsigned int vertex, fragment;
		int success;
		char infoLog[512];

		// vertex shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		// print compile errors if any
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertex, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
					  << infoLog << std::endl;
		}

		// fragment shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		// print compile errors if any
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragment, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
					  << infoLog << std::endl;
		}

		// 3. Link shader program
		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);
		// print linking errors if any
		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(ID, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
					  << infoLog << std::endl;
		}
		// delete the shaders after they aer linked
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}
	// Use/activate the shader
	void use() { glUseProgram(ID); }
	// Utility uniform functions
	void setBool(const std::string &name, bool value)
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	}
	void setInt(const std::string &name, int value)
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}
	void setFloat(const std::string &name, float value)
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}
};

#endif
