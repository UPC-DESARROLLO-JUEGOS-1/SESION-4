#pragma once

#include <UPCFramework\NWindow.h>
#include <UPCFramework\NFramework.h>
#include <UPCFramework\NSprite.h>
#include <functional>

class NGameApplication
{
public:
	static const int WIDTH = 800;
	static const int HEIGHT = 600;

	NGameApplication();
	~NGameApplication();

	void Start();
private:
	NFramework mFramework;
	NSprite mSprite;

	void InitializeApplication();
	void OnInput(SDL_Event evnt);

	void Update(float dt);
	void Draw(float dt);
};