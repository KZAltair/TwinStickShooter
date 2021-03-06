#include "Engine.h"
#include "ComInitializer.h"
#include "GDIPlusManager.h"

#pragma comment(lib, "winmm.lib")

int WINAPI WinMain(
	HINSTANCE hInst,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nShowCmd
)
{
	COMInitializer ComInit;
	GDIPlusManager gdiMan;
	//Create window
	Window wnd(1280, 720, hInst);
	//Create main engine
	Engine engine(wnd);

	while(wnd.RunMessageLoop())
	{
		//Call Engine object
		engine.Run(wnd);

		//Added to github
	}
	return 0;
}