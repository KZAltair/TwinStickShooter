#pragma once
#include "WinLib.h"

class GDIPlusManager
{
public:
	GDIPlusManager();
	~GDIPlusManager();

public:
	static ULONG_PTR token;
	static int refcount;
};