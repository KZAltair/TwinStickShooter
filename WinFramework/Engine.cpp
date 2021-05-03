#include "Engine.h"

Engine::Engine(Window& wnd)
	:
	gfx(wnd.GetWindowWidth(), wnd.GetWindowHeight())
{
	Colors = wnd.GetColorBuffer();
	QueryPerformanceFrequency(&PerfCountFrequecyResult);
	PerfCountFrequency = (float)(PerfCountFrequecyResult.QuadPart);
	SleepIsGranular = (timeBeginPeriod(1) == TIMERR_NOERROR);

	//Init here
	PlayerP.MapX = 0;
	PlayerP.MapY = 0;
	PlayerP.TileX = 2;
	PlayerP.TileY = 2;
	PlayerP.pos = pos;

	map.SetWorldPosition(PlayerP);

}

Engine::~Engine()
{
}

void Engine::Run(Window& wnd)
{
	//Thread sleep to stop burning cycles
	LARGE_INTEGER LastCounter = EngineGetWallClock();
	
	LARGE_INTEGER WorkCounter = EngineGetWallClock();

	float WorkSecondsElapsed = EngineGetSecondsElapsed(LastCounter, WorkCounter);
	float SecondsElapsedForFrame = WorkSecondsElapsed;

	while (SecondsElapsedForFrame < FPSMS)
	{
		if (SleepIsGranular)
		{
			DWORD SleepMS = (DWORD)(1000.0f * (FPSMS - SecondsElapsedForFrame));
			Sleep(SleepMS);
		}
		SecondsElapsedForFrame = EngineGetSecondsElapsed(LastCounter, EngineGetWallClock());
	}

	counter = std::to_string(cX);
	finTitle = winName + counter;
	SetWindowTextA(wnd.GetCustomWindow(), finTitle.c_str());
	cX = 1.0f / SecondsElapsedForFrame;
	Update(wnd);
	ComposeFrame();

	LARGE_INTEGER EndCounter = EngineGetWallClock();
	LastCounter = EndCounter;
}

void Engine::Update(Window& wnd)
{
	float dt = ft.Go();
	dir = {};
	if (wnd.kbd.KeyIsPressed('W'))
	{
		dir.y = -1.0f;
	}
	if (wnd.kbd.KeyIsPressed('S'))
	{
		dir.y = 1.0f;
	}
	if (wnd.kbd.KeyIsPressed('A'))
	{
		dir.x = -1.0f;
	}
	if (wnd.kbd.KeyIsPressed('D'))
	{
		dir.x = 1.0f;
	}
	Vec2 newPos = PlayerP.pos;
	newPos += dir * speed * dt;
	raw_position PlayerPos = { PlayerP.MapX, PlayerP.MapY, newPos.x, newPos.y };
	raw_position LeftPos = PlayerPos;
	LeftPos.X -= 30.0f;
	raw_position RightPos = PlayerPos;
	RightPos.X += 30.0f;

	if (map.IsWorldWalkable(PlayerPos) &&
		map.IsWorldWalkable(LeftPos) &&
		map.IsWorldWalkable(RightPos))
	{
		canonical_position CanPos = map.GetCanonicalPosition(PlayerPos);
		PlayerP.MapX = CanPos.MapX;
		PlayerP.MapY = CanPos.MapY;
		PlayerP.TileX = CanPos.TileX;
		PlayerP.TileY = CanPos.TileY;
		PlayerP.pos.x = map.GetTileCorner().x + 80.0f * CanPos.TileX + CanPos.pos.x;
		PlayerP.pos.y = map.GetTileCorner().y + 80.0f * CanPos.TileY + CanPos.pos.y;
		map.SetWorldPosition(PlayerP);
	}
}

LARGE_INTEGER Engine::EngineGetWallClock() const
{
	LARGE_INTEGER Result;
	QueryPerformanceCounter(&Result);
	return Result;
}

float Engine::EngineGetSecondsElapsed(LARGE_INTEGER Start, LARGE_INTEGER End) const
{
	float Result = ((float)(End.QuadPart - Start.QuadPart) / PerfCountFrequency);
	return Result;
}

void Engine::ComposeFrame()
{
	//gfx.FillScreenFast(Colors,255, 0, 0);
	//gfx.DrawPixel(Colors, 100, 100, 255, 0, 0);
	gfx.ClearScreenSuperFast(Colors);
	map.Draw(Colors, gfx);
	int MX = (int)(map.GetTileCorner().x + PlayerP.TileX * 80.0f);
	int MY = (int)(map.GetTileCorner().y + PlayerP.TileY * 80.0f);
	int MxX = (int)(map.GetTileCorner().x + (PlayerP.TileX * 80.0f + 80.0f));
	int MxY = (int)(map.GetTileCorner().y + (PlayerP.TileY * 80.0f + 80.0f));
	gfx.DrawRectancle(Colors, MX, MxX, MY, MxY, 0, 0, 0);
	int MinX = (int)(PlayerP.pos.x - 30.0f);
	int MinY = (int)(PlayerP.pos.y);
	int MaxX = (int)(PlayerP.pos.x + 30.0f);
	int MaxY = (int)(PlayerP.pos.y - 80.0f);
	gfx.DrawRectancle(Colors, MinX, MaxX, MinY, MaxY, 255, 255, 0);
}


