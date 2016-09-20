#pragma once

#include <functional>
#include <SDL\SDL.h>

#include "NWindow.h"
#include "NContentManagment.h"
#include "NShaderManagment.h"
#include "NCamera.h"

enum NEnumFrameworkState {
	Running,
	Exit
};

class NFramework
{
public:
	static NFramework* GET_FRAMEWORK();

	NFramework();
	~NFramework();

	NContentManagment* GetContentManagment() { return &mContentManagment; }
	NShaderManagment* GetShaderManagment() { return &mShaderManagment; }
	NCamera* GetCamera() { return mCamera; }
	
	void Initialize(const std::string windowName, int screenWidth, int screenHeight, 
		unsigned int windowFlags);

	void SetFrameworkState(NEnumFrameworkState state);
	void OnInput(std::function<void(SDL_Event)> onInput) { mOnInput = onInput; }
	
	void DoGameLoop(std::function<void(float)> onUpdate, std::function<void(float)> onDraw);
	void Update(float dt);
	void Draw(float dt);

private:
	static NFramework* M_FRAMEWORK;

	int mScreenWidth;
	int mScreenHeight;
	NEnumFrameworkState mFrameworkState;

	NCamera* mCamera;

	NWindow mWindow;
	NContentManagment mContentManagment;
	NShaderManagment mShaderManagment;

	std::function<void(SDL_Event)> mOnInput;
	std::function<void(float)> mOnUpdate;
	std::function<void(float)> mOnDraw;

	float ComputeDeltaTime();
	void OnListenInputsFromWindow(SDL_Event evnt);
};

