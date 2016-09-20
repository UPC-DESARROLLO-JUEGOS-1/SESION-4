#pragma once

#include <vector>

#include "NBaseContent.h"
#include <GL/glew.h>

class NImageContent : public NBaseContent
{
public:
	NImageContent(NContentManagment* contentManagment);
	~NImageContent();

	int GetWidth() { return mWidth; }
	int GetHeight() { return mHeight; }
	GLuint GetTextureId() { return mImageId; }

	void Initialize();
	bool Load(const std::string path);
private:
	int mWidth;
	int mHeight;
	GLuint mImageId;
};

