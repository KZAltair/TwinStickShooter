#include "Engine.h"

Engine::Engine(Window& wnd)
	:
	ball(Vec2(300.0f, 300.0f), Vec2(100.0f, 100.0f)),
	walls(0.0f, 800.0f, 0.0f, 600.0f)
{
	Colors = wnd.GetColorBuffer();
}

Engine::~Engine()
{
}

void Engine::Run(Window& wnd)
{
	//Thread sleep to stop burning cycles
	float dt = ft.Go();
	bench += dt;
	std::chrono::duration<float> ThreadSleepTime(FPSMS - bench);
	if (bench < FPSMS)
	{
		//Windows native command to hold thread cycles
		Sleep(DWORD(ThreadSleepTime.count() * 1000.0f));
	}
	else
	{
		bench = 0.0f;
	}
	counter = std::to_string(cX);
	finTitle = winName + counter;
	SetWindowTextA(wnd.GetCustomWindow(), finTitle.c_str());
	cX = 1.0f / ThreadSleepTime.count();


	Update(wnd);
	ComposeFrame();
}

void Engine::Update(Window& wnd)
{
	float dt = ft.Go();
	ball.Update(dt);
	ball.DoWallCollision(walls);
}

void Engine::ComposeFrame()
{
	//gfx.FillScreenFast(Colors,255, 0, 0);
	gfx.ClearScreenSuperFast(Colors);
	//gfx.DrawPixel(Colors, 100, 100, 255, 0, 0);
	ball.Draw(gfx, Colors);
}


