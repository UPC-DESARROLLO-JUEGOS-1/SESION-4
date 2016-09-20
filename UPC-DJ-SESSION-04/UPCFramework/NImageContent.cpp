#include "NImageContent.h"
#include "NContentManagment.h"
#include "PicoPNG.h"
#include "FatalError.h"

NImageContent::NImageContent(NContentManagment* contentManagment) : NBaseContent(contentManagment)
{
}

NImageContent::~NImageContent()
{
}

void NImageContent::Initialize()
{
	NBaseContent::Initialize();
}

bool NImageContent::Load(const std::string path) {
	NBaseContent::Load(path);

	std::vector<unsigned char> imagerRawBufferData;
	bool fileLoaded = NContentManagment::ReadFileToBuffer(mPath, imagerRawBufferData);
	bool imageDecoded = false;

	if (fileLoaded) {
		std::vector<unsigned char> imageDataPNG;

		unsigned long rWidth;
		unsigned long rHeight;

		int errorCode = decodePNG(imageDataPNG, rWidth, rHeight, &(imagerRawBufferData[0]),
			imagerRawBufferData.size(), true);
		imageDecoded = errorCode == 0;

		if (errorCode != 0) {
			FatalError("Decode PicoPNG failed with error: " + std::to_string(errorCode));
		}
		else {
			mWidth = rWidth;
			mHeight = rHeight;

			glGenTextures(1, &(mImageId));

			glBindTexture(GL_TEXTURE_2D, mImageId);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0,
				GL_RGBA, GL_UNSIGNED_BYTE, &(imageDataPNG[0]));

			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}

	return fileLoaded && imageDecoded;
}
