#pragma once

#include <map>
#include <iostream>
#include <type_traits>
#include <vector>
#include <fstream>

#include "NBaseContent.h"

class NImageContent;
class NFramework;

class NContentManagment
{
public:
	NContentManagment(NFramework* framework) { mFramework = framework; }
	~NContentManagment();

	void Initialize();

	template<typename T>
	NBaseContent* LoadAndGetContent(const std::string path) {
		std::map<std::string, NBaseContent*>::iterator mit = mContents.find(path);
		NBaseContent* result = mit != mContents.end() ? mit->second : nullptr;

		if (result == nullptr) {
			bool succesfulLoading = false;

			if (std::is_same<T, NImageContent>::value) {
				result = (NBaseContent*)LoadImageContent(path);
			}

			if (result != nullptr) {
				result->Initialize();
				succesfulLoading = result->Load(path);
			}

			if (succesfulLoading) {
				// Now insert it on the dictionary
				mContents.insert(std::make_pair(path, result));

				std::cout << "Loaded content: " << path;
			}
			else {
				std::cout << "Failed to load content in: " << path;
			}
		}

		return result;
	}

	static bool ReadFileToBuffer(const std::string filePath, 
		std::vector<unsigned char>& buffer);
private:
	NFramework* mFramework;
	std::map<std::string, NBaseContent*> mContents;

	NImageContent* LoadImageContent(const std::string path);

	NBaseContent* GetContent(const std::string path) {
		std::map<std::string, NBaseContent*>::iterator mit = mContents.find(path);

		if (mit == mContents.end()) {
			std::cout << "Not found content in path: " << path;
			return nullptr;
		}

		return mit->second;
	}
};