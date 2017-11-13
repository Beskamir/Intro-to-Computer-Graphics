// ShaderProgram class based on TA's game of life with some help from Daniel Dastoor.

#include "ShaderProgram.h"

ShaderProgram::ShaderProgram() = default;

ShaderProgram::~ShaderProgram(){
    id = 0;
}

bool ShaderProgram::attachShader(string path, GLenum type){
	if (id == 0) {
		id = glCreateProgram();
		//if (OpenGL::error("glCreateProgram"))
		//	return false;
	}
//	cout<<id<<endl;

	std::ifstream in(path);
	string buffer = [&in] {
		std::ostringstream ss{};
		ss << in.rdbuf();
		return ss.str();
	}();
	const char *buffer_array[] = { buffer.c_str() };



	GLuint shader = glCreateShader(type);
	//if (OpenGL::error("glCreateShader"))
	//	return false;

	glShaderSource(shader, 1, buffer_array, 0);
	//if (OpenGL::error("glShaderSource"))
	//	return false;

	glCompileShader(shader);
	//if (OpenGL::error("glCompileShader"))
	//	return false;

	// Compile results
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE) {
		GLint length;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		string info(length, ' ');
		glGetShaderInfoLog(shader, info.length(), &length, &info[0]);
		cerr << "ERROR compiling shader " << shader << " :" << endl;
		cerr << info << endl;
	}
	// Attach shader
    glAttachShader(id, shader);
//    cout<<id<<":"<<shader<<endl;
    //if (OpenGL::error("glAttachShader"))
	//	return false;
	return true;
}

bool ShaderProgram::link(){
	if (id <= 0) {
		return false;
	}
	glLinkProgram(id);
	//if (OpenGL::error("glLinkProgram"))
	//	return false;
//    cout<<"Linking: "<<id<<endl;

	GLint state = 0;
	glGetProgramiv(id, GL_LINK_STATUS, &state);
	if (state == GL_FALSE) {
		glGetProgramiv(id, GL_INFO_LOG_LENGTH, &state);

		char* buffer = new char[state];
		glGetProgramInfoLog(id, state, &state, buffer);
		buffer[state - 1] = '\0';         // ensure we're null-terminated

		cerr << "ERROR: Program " << id << " did not link. The program log:" << endl;
		cerr << buffer << endl;

		return false;
	}

	return true;
}

bool ShaderProgram::bind(){
	glUseProgram(id);
	//if (OpenGL::error("glUseProgram"))
	//	return false;
	return true;
}

void ShaderProgram::unbind(){
	glUseProgram(0);
}
