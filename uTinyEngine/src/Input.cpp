#define UTINY_API __declspec(dllexport)
#include "../include/Input.h"

#include<map>
#include<iostream>
std::map<Key, KeyState> keyStates;
std::map<Key, KeyEvent> keyEvents;

MousePosition lastMousePosition;
MousePosition currentMousePosition;

void Input::Create(std::string)
{
}

void Input::Clear()
{
}

KeyState Input::GetKeyState(Key key)
{
	return keyStates[key];
}

//检测某个键是否被按下
bool Input::GetKeyDown(Key key)
{
	return keyStates[key] == KeyState::Down;
}

//获取某个键的按下、松开事件
KeyEvent Input::GetKeyEvent(Key key)
{
	return keyEvents[key];
}
//获取鼠标在屏幕上的位置，屏幕左上角为（0,0）
MousePosition Input::GetMousePosition() {
	return currentMousePosition;
}

//获取鼠标位置相对于上一帧的偏移
MousePosition Input::GetMousePositionChange() {
	MousePosition d{ currentMousePosition.x - lastMousePosition.x,
		currentMousePosition.y - lastMousePosition.y };
	int max = 10;
	if (d.x > max)d.x = max;
	if (d.y > max)d.y = max;
	if (d.x < -max)d.x = -max;
	if (d.y < -max)d.y = -max;
	return d;
}
