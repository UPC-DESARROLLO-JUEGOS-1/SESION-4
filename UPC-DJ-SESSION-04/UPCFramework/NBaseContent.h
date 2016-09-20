#pragma once

#include <string>

// forward declaration, this is done for not having circular dependecies
class NContentManagment;

class NBaseContent
{
public:
	NBaseContent(NContentManagment* contentManagment) { mContentManagment = contentManagment; }
	~NBaseContent();

	virtual void Initialize() {}
	virtual bool Load(const std::string path) { 
		mPath = path; 
		return true;
	}

	std::string GetPath() { mPath; }
	NContentManagment* GetContentManagment() { return mContentManagment; }
protected:
	std::string mPath;
	NContentManagment *mContentManagment;
};

