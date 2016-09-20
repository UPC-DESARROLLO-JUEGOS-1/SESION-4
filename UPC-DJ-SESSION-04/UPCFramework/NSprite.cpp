#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "NSprite.h"
#include "NFramework.h"
#include "dtVertexSprite.h"

NSprite::NSprite() :
	mX(0),
	mY(0),
	mVBO_ID(0)
{
}

NSprite::~NSprite()
{
	if (mVBO_ID != 0) {
		glDeleteBuffers(1, &mVBO_ID);
	}
}

void NSprite::Initialize(const std::string path)
{
	NFramework* framework = NFramework::GET_FRAMEWORK();
	NContentManagment* contentManagment = framework->GetContentManagment();
	NShaderManagment* shaderManagment = framework->GetShaderManagment();

	const std::string baseShaderPath = "Resources/shaders/ColorShading";

	mShader = shaderManagment->LoadAndGetShader<NSpriteShader>(baseShaderPath);
	mContent = (NImageContent*)contentManagment->LoadAndGetContent<NImageContent>(path);

	mWidth = mContent->GetWidth();
	mHeight = mContent->GetHeight();

	if (mVBO_ID == 0) {
		glGenBuffers(1, &mVBO_ID);
	}

	dtVertexSprite vertexData[6];
	// primer triangulo
	vertexData[0].SetPosition(mWidth, mHeight);
	vertexData[0].SetColor(255, 255, 255, 255);
	vertexData[0].SetUV(1.0f, 1.0f);

	vertexData[1].SetPosition(0, mHeight);
	vertexData[1].SetColor(255, 255, 255, 255);
	vertexData[1].SetUV(0.0f, 1.0f);

	vertexData[2].SetPosition(0, 0);
	vertexData[2].SetColor(255, 255, 255, 255);
	vertexData[2].SetUV(0.0f, 0.0f);
	// segundo triangulo
	vertexData[3].SetPosition(0, 0);
	vertexData[3].SetColor(255, 255, 255, 255);
	vertexData[3].SetUV(0.0f, 0.0f);

	vertexData[4].SetPosition(mWidth, 0);
	vertexData[4].SetColor(255, 255, 255, 255);
	vertexData[4].SetUV(1.0f, 0.0f);

	vertexData[5].SetPosition(mWidth, mHeight);
	vertexData[5].SetColor(255, 255, 255, 255);
	vertexData[5].SetUV(1.0f, 1.0f);

	glBindBuffer(GL_ARRAY_BUFFER, mVBO_ID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void NSprite::Update(float dt)
{
}

void NSprite::Draw(float dt)
{
	mShader->Use();

	// Blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	GLuint mvpLocation = mShader->GetUniformLocation("mvp");
	glm::mat4 cameraMatrix = mCamera->GetCameraMatrix();
	glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	GLuint textureLocation = mShader->GetUniformLocation("sampler");
	glUniform1i(textureLocation, 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mContent->GetTextureId());

	glBindBuffer(GL_ARRAY_BUFFER, mVBO_ID);
	glEnableVertexAttribArray(0);

	// Position
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(dtVertexSprite), (void*)offsetof(dtVertexSprite, Position));
	// Color
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(dtVertexSprite), (void*)offsetof(dtVertexSprite, Color));
	// UV
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_TRUE, sizeof(dtVertexSprite), (void*)offsetof(dtVertexSprite, UV));

	// Draw
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	mShader->Unuse();
}
