#include "NBaseShader.h"
#include "FatalError.h"

#include <fstream>
#include <vector>


NBaseShader::NBaseShader() :
	mProgramShader_ID(0),
	mVertexShader_ID(0),
	mFragmentShader_ID(0),
	mNumAttributes(0)
{
}

NBaseShader::~NBaseShader()
{
}

void NBaseShader::Initialize() {
	CreateAttributes();
}

void NBaseShader::Use() {
	glUseProgram(mProgramShader_ID);

	for (int i = 0; i < mNumAttributes; i++)
	{
		glEnableVertexAttribArray(i);
	}
}

void NBaseShader::Unuse() {
	glUseProgram(0);

	for (int i = 0; i < mNumAttributes; i++)
	{
		glDisableVertexAttribArray(i);
	}
}

GLint NBaseShader::GetUniformLocation(const std::string& uniformName) {
	GLint location = glGetUniformLocation(mProgramShader_ID, uniformName.c_str());

	if (location == GL_INVALID_INDEX) {
		FatalError("Uniform: " + uniformName + " not found in Shader!");
	}

	return location;
}

void NBaseShader::AddAttribute(const std::string& attributeName) {
	glBindAttribLocation(mProgramShader_ID, mNumAttributes++, attributeName.c_str());
}

void NBaseShader::LoadAndCompile(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath) {
	//Get a program object.
	mProgramShader_ID = glCreateProgram();

	mVertexShader_ID = glCreateShader(GL_VERTEX_SHADER);
	if (mVertexShader_ID == 0) {
		FatalError("Vertex Shader failed to be created!");
	}

	mFragmentShader_ID = glCreateShader(GL_FRAGMENT_SHADER);
	if (mFragmentShader_ID == 0) {
		FatalError("Fragment Shader failed to be created!");
	}

	// compile shaders
	CompileShader(vertexShaderFilePath, mVertexShader_ID);
	CompileShader(fragmentShaderFilePath, mFragmentShader_ID);
}

void NBaseShader::CompileShader(const std::string& filePath, GLuint shader_ID) {
	std::ifstream shaderFile(filePath);

	if (shaderFile.fail()) {
		perror(filePath.c_str());
		FatalError("Failed to open " + filePath);
	}

	std::string fileContents = "";
	std::string line;

	while (std::getline(shaderFile, line)) {
		fileContents += line + "\n";
	}

	shaderFile.close();

	const char* contentsPtr = fileContents.c_str();
	glShaderSource(shader_ID, 1, &contentsPtr, nullptr);

	glCompileShader(shader_ID);

	GLint success = 0;
	glGetShaderiv(shader_ID, GL_COMPILE_STATUS, &success);

	if (success == GL_FALSE) {
		GLint maxLength = 0;
		glGetShaderiv(shader_ID, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<char> errorLog(maxLength);
		glGetShaderInfoLog(shader_ID, maxLength, &maxLength, &errorLog[0]);

		// Provide the infolog in whatever manor you deem best
		// Exit with failure
		glDeleteShader(shader_ID); // Don't leak the shader

		std::printf("%s\n", &(errorLog[0]));
		FatalError("Shader: '" + filePath + "' failed to compile!");
	}
}

void NBaseShader::LinkShaders() {
	//Vertex and fragment shaders are successfully compiled.
	//Now time to link them together into a program.

	//Attach our shaders to our program
	glAttachShader(mProgramShader_ID, mVertexShader_ID);
	glAttachShader(mProgramShader_ID, mFragmentShader_ID);

	//Link our program
	glLinkProgram(mProgramShader_ID);

	//Note the different functions here: glGetProgram* instead of glGetShader*.
	GLint isLinked = 0;
	glGetProgramiv(mProgramShader_ID, GL_LINK_STATUS, &isLinked);

	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(mProgramShader_ID, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		std::vector<char> errorLog(maxLength);
		glGetProgramInfoLog(mProgramShader_ID, maxLength, &maxLength, &errorLog[0]);

		//We don't need the program anymore.
		glDeleteProgram(mProgramShader_ID);
		//Don't leak shaders either.
		glDeleteShader(mVertexShader_ID);
		glDeleteShader(mFragmentShader_ID);

		//Use the infoLog as you see fit.
		std::printf("%s\n", &(errorLog[0]));
		FatalError("Shaders failed to link!");
	}

	//Always detach shaders after a successful link.
	glDetachShader(mProgramShader_ID, mVertexShader_ID);
	glDetachShader(mProgramShader_ID, mFragmentShader_ID);
	glDeleteShader(mVertexShader_ID);
	glDeleteShader(mFragmentShader_ID);
}
