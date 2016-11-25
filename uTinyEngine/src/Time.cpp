#define UTINY_API __declspec(dllexport)

#include "../include/Time.h"
#include<chrono>
using namespace std::chrono;

float Time::DeltaTime() {
	static steady_clock::time_point last_point = steady_clock::now();
	steady_clock::time_point now_point = steady_clock::now();

	steady_clock::duration time_span = now_point - last_point;
	last_point = now_point;
	return (double)time_span.count()*steady_clock::period::num / steady_clock::period::den;
}


float Time::FPS()
{
	return 0.0f;
}
