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

//���ĳ�����Ƿ񱻰���
bool Input::GetKeyDown(Key key)
{
	return keyStates[key] == KeyState::Down;
}

//��ȡĳ�����İ��¡��ɿ��¼�
KeyEvent Input::GetKeyEvent(Key key)
{
	return keyEvents[key];
}
//��ȡ�������Ļ�ϵ�λ�ã���Ļ���Ͻ�Ϊ��0,0��
MousePosition Input::GetMousePosition() {
	return currentMousePosition;
}

//��ȡ���λ���������һ֡��ƫ��
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
