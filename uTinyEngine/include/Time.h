#pragma once

#ifndef UTINY_API

#define UTINY_API __declspec(dllimport)

#endif

class UTINY_API Time
{
public:
	static float DeltaTime();
	static float FPS();
};

