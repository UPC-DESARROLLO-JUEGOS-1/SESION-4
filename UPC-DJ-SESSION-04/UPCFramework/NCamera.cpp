#include "NCamera.h"

NCamera::NCamera() :
	mPosition(0.0f, 0.0f),
	mCameraMatrix(1.0f),
	mOrthoMatrix(1.0f),
	mScale(1.0f),
	mNeedMatrixUpdate(true),
	mScreenWidth(0), mScreenHeight(0)
{
}

void NCamera::Initialize(int screenWidth, int screenHeight)
{
	mScreenWidth = screenWidth;
	mScreenHeight = screenHeight;

	mOrthoMatrix = glm::ortho(0.0f, (float)mScreenWidth,
		(float)mScreenHeight, 0.0f);
}

void NCamera::Update(float dt) {
	if (mNeedMatrixUpdate) {
		glm::vec3 translate(mPosition.x, mPosition.y, 0.0f);
		mCameraMatrix = glm::translate(mOrthoMatrix, translate);

		glm::vec3 scale(mScale, mScale, 0.0f);
		mCameraMatrix = glm::scale(mCameraMatrix, scale);

		mNeedMatrixUpdate = false;
	}
}


NCamera::~NCamera()
{
}
