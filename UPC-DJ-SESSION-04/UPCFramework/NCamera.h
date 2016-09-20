#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class NCamera
{
public:
	NCamera();
	~NCamera();

	void Initialize(int screenWidth, int screenHeight);
	void Update(float dt);

	void SetPosition(const glm::vec2& position) {
		mNeedMatrixUpdate = true;
		mPosition = position;
	}

	void SetScale(float scale) {
		mNeedMatrixUpdate = true;
		mScale = scale;
	}

	glm::mat4 GetCameraMatrix() { return mCameraMatrix; }
	glm::vec2 GetPosition() { return mPosition; }
	float GetScale() { return mScale; }

private:
	int mScreenWidth, mScreenHeight;
	bool mNeedMatrixUpdate;
	float mScale;

	glm::vec2 mPosition;
	glm::mat4 mCameraMatrix;
	glm::mat4 mOrthoMatrix;
};

