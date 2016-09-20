#include "NPrimitiveShader.h"

NPrimitiveShader::NPrimitiveShader() : NBaseShader()
{
}

void NPrimitiveShader::CreateAttributes() {
	AddAttribute("vertexPosition");
	AddAttribute("vertexColor");
}

NPrimitiveShader::~NPrimitiveShader()
{
}
