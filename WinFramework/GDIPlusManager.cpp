#include "GDIPlusManager.h"
#include <algorithm>

namespace Gdiplus
{
	using std::min;
	using std::max;
}
#include <gdiplus.h>

#pragma comment(lib, "gdiplus.lib")
ULONG_PTR GDIPlusManager::token = 0;
int GDIPlusManager::refcount = 0;

GDIPlusManager::GDIPlusManager()
{
	if (refcount++ == 0)
	{
		Gdiplus::GdiplusStartupInput input;
		input.DebugEventCallback = nullptr;
		input.GdiplusVersion = 1;
		input.SuppressBackgroundThread = false;
		Gdiplus::GdiplusStartup(&token, &input, nullptr);
	}
}

GDIPlusManager::~GDIPlusManager()
{
	if (--refcount == 0)
	{
		Gdiplus::GdiplusShutdown(token);
	}
}
