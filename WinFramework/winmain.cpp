#include "Engine.h"

int WINAPI WinMain(
	HINSTANCE hInst,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nShowCmd
)
{
	//Create window
	Window wnd(800, 600, hInst);
	//Create main engine
	Engine engine(wnd);

	while(wnd.RunMessageLoop())
	{
		//Call Engine object
		engine.Run(wnd);
	}
	return 0;
}