#pragma once

#include <map>
#include <iostream>

#include "NBaseShader.h"

class NFramework;

class NShaderManagment
{
public:
	NShaderManagment(NFramework* framework) { mFramework = framework; }
	~NShaderManagment();

	void Initialize();

	template<typename T>
	T* LoadAndGetShader(const std::string& baseShaderPath) {
		std::map<std::string, NBaseShader*>::iterator mit = mShaders.find(baseShaderPath);
		T* result = mit != mShaders.end() ? (T*)mit->second : nullptr;

		if (result == nullptr) {
			result = new T();
			result->LoadAndCompile(baseShaderPath + ".vert", baseShaderPath + ".frag");
			result->Initialize();
			result->LinkShaders();

			// Now insert it on the dictionary
			mShaders.insert(std::make_pair(baseShaderPath, result));

			std::cout << "Loaded shader: " << baseShaderPath;
		}

		return result;
	}

private:
	NFramework* mFramework;
	std::map<std::string, NBaseShader*> mShaders;


};

