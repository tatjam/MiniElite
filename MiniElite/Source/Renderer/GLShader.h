#pragma once
#include <GL/glew.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using std::cout;
using std::endl;
using std::string;
using std::stringstream;
using std::ifstream;

class GLShader
{
private:
	GLuint id = 0;         // The unique ID / handle for the shader
	std::string typeString; // String representation of the shader type (i.e. "Vertex" or such)
	std::string source;     // The shader source code (i.e. the GLSL code itself)

public:
	// Constructor
	GLShader(const GLenum &type)
	{
		// Get the type of the shader
		if (type == GL_VERTEX_SHADER)
		{
			typeString = "Vertex";
		}
		else if (type == GL_FRAGMENT_SHADER)
		{
			typeString = "Fragment";
		}
		else
		{
			typeString = "Geometry";
		}

		// Create the vertex shader id / handle
		// Note: If you segfault here you probably don't have a valid rendering context.
		id = glCreateShader(type);
	}

	GLuint getId()
	{
		return id;
	}

	string getSource()
	{
		return source;
	}

	// Method to load the shader contents from a file
	void loadFromString(const string &sourceString)
	{
		// Keep hold of a copy of the source
		source = sourceString;

		// Get the source as a pointer to an array of characters
		const char *sourceChars = source.c_str();

		// Associate the source with the shader id
		glShaderSource(id, 1, &sourceChars, NULL);
	}

	// Method to load the shader contents from a string
	void loadFromFile(const string &filename)
	{
		std::ifstream file;

		file.open(filename.c_str());

		if (!file.good())
		{
			std::cout << "Failed to open file: " << filename << std::endl;
			exit(-1);
		}

		// Create a string stream
		std::stringstream stream;

		// Dump the contents of the file into it
		stream << file.rdbuf();

		// Close the file
		file.close();

		// Convert the StringStream into a string
		source = stream.str();

		// Get the source string as a pointer to an array of characters
		const char *sourceChars = source.c_str();

		// Associate the source with the shader id
		glShaderSource(id, 1, &sourceChars, NULL);
	}


	// Method to compile a shader and display any problems if compilation fails
	void compile()
	{
		// Compile the shader
		glCompileShader(id);

		// Check the compilation status and report any errors
		GLint shaderStatus;
		glGetShaderiv(id, GL_COMPILE_STATUS, &shaderStatus);

		// If the shader failed to compile, display the info log and quit out
		if (shaderStatus == GL_FALSE)
		{
			GLint infoLogLength;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &infoLogLength);

			GLchar *strInfoLog = new GLchar[infoLogLength + 1];
			glGetShaderInfoLog(id, infoLogLength, NULL, strInfoLog);

			std::cout << typeString << " shader compilation failed: " << strInfoLog << std::endl;
			std::cin.get();
			delete[] strInfoLog;
		}
		else
		{
			cout << typeString << " shader compilation OK" << endl;
		}
	}
};
