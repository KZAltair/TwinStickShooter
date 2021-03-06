#pragma once
#include "Window.h"
#include "Graphics.h"
#include "Timer.h"
#include <string>
//TODO: remake this from sleep to thread
#include <thread>
#include "Vec2.h"
#include "TileMap.h"
#include "Assets.h"
#include "Animation.h"

class Engine
{
public:
	Engine(class Window& wnd);
	Engine(const Engine&) = delete;
	Engine operator=(const Engine&) = delete;
	~Engine();

	void Run(class Window& wnd);
private:
	void ComposeFrame();
	void Update(class Window& wnd);
	LARGE_INTEGER EngineGetWallClock() const;
	float EngineGetSecondsElapsed(LARGE_INTEGER Start, LARGE_INTEGER End) const;
private:
	Graphics gfx;
	int* Colors;
	Timer ft;

private:
	LARGE_INTEGER PerfCountFrequecyResult;
	bool SleepIsGranular = false;
	float PerfCountFrequency;
	const float FPSMS = 1.0f / 30.0f;

	std::string winName = "Windows Framework ";
	std::string counter;
	std::string finTitle;
	float cX = 0;
private:
	//Game stuff here
	TileMap map;
	Vec2<float> dir = {};
	canonical_position PlayerP;
	float speed = 2.0f;
	static constexpr float PlayerWidthMultiplier = 0.4f;
	float PlayerWidth = 0.0f;
	float PlayerHeight = 1.0f;

	Animation* anim = nullptr;
};