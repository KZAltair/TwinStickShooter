#include "Engine.h"

//TODO: Fix playerpos and metric system

Engine::Engine(Window& wnd)
	:
	gfx(wnd.GetWindowWidth(), wnd.GetWindowHeight())
{
	Colors = wnd.GetColorBuffer();
	QueryPerformanceFrequency(&PerfCountFrequecyResult);
	PerfCountFrequency = (float)(PerfCountFrequecyResult.QuadPart);
	SleepIsGranular = (timeBeginPeriod(1) == TIMERR_NOERROR);

	//Init here
	PlayerWidth = 0.75f * map.GetTileSizeInMeters();
	PlayerP.MapX = 0;
	PlayerP.MapY = 0;
	PlayerP.TileX = 2;
	PlayerP.TileY = 2;
	PlayerP.pos.x = map.GetTileSizeInMeters() / 2.0f;
	PlayerP.pos.y = map.GetTileSizeInMeters() - 0.01f;

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
	canonical_position PlayerPos = PlayerP;
	PlayerPos.pos += dir * speed * dt;
	PlayerPos = map.RemapPosition(PlayerPos);
	
	canonical_position LeftPos = PlayerPos;
	LeftPos.pos.x -= (0.5f*PlayerWidth);
	LeftPos = map.RemapPosition(LeftPos);

	canonical_position RightPos = PlayerPos;
	RightPos.pos.x += (0.5f * PlayerWidth);
	RightPos = map.RemapPosition(RightPos);

	if (map.IsWorldWalkable(PlayerPos) &&
		map.IsWorldWalkable(LeftPos) &&
		map.IsWorldWalkable(RightPos))
	{
		PlayerP = PlayerPos;
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
	int MX = (int)(map.GetTileCorner().x + PlayerP.TileX * map.GetTileSizeInPixels());
	int MY = (int)(map.GetTileCorner().y + PlayerP.TileY * map.GetTileSizeInPixels());
	int MxX = (int)(map.GetTileCorner().x + (PlayerP.TileX * map.GetTileSizeInPixels() + map.GetTileSizeInPixels()));
	int MxY = (int)(map.GetTileCorner().y + (PlayerP.TileY * map.GetTileSizeInPixels() + map.GetTileSizeInPixels()));
	gfx.DrawRectancle(Colors, MX, MxX, MY, MxY, 0, 0, 0);

	int PlayerLeft = (int)(map.GetTileCorner().x + PlayerP.TileX * map.GetTileSizeInPixels() +
		PlayerP.pos.x * map.GetPixelsFromMeters() - 0.5f * PlayerWidth * map.GetPixelsFromMeters());
	int PlayerTop = (int)(map.GetTileCorner().y + PlayerP.TileY * map.GetTileSizeInPixels() +
		PlayerP.pos.y * map.GetPixelsFromMeters());
	gfx.DrawRectancle(Colors, PlayerLeft, PlayerLeft + PlayerWidth * map.GetPixelsFromMeters(),
		PlayerTop, PlayerTop - PlayerHeight * map.GetPixelsFromMeters(), 255, 255, 0);
}


