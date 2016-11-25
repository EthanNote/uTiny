#pragma once
#include<string>

#ifndef UTINY_API

#define UTINY_API __declspec(dllimport)

#endif

enum KeyState {
	Down = 255, Up = 0
};
enum KeyEvent {
	Pressed = 128, Released = 255, None = 0
};
enum Key {
	Tab = '\t',
	Space = ' ',
	Quote = '\'',
	Esc = 27,

	One = '1', Two = '2', Three = '3', Four = '4', Five = '5',
	Six = '6', Seven = '7', Eight = '8', Nine = '9', Zero = '0',

	A = 'a', B = 'b', C = 'c', D = 'd', E = 'e', F = 'f', G = 'g', H = 'h',
	I = 'i', J = 'j', K = 'k', L = 'l', M = 'm', N = 'n', O = 'o', P = 'p',
	Q = 'q', R = 'r', S = 's', T = 't', U = 'u', V = 'v', W = 'w', X = 'x',
	Y = 'y', Z = 'z',

	Mouse_Left, Mouse_Right, Mouse_Middle
};

typedef struct MousePosition {
	int x, y;
}MousePosition;



class UTINY_API Input
{
public:
	static void Create(std::string = "");
	static void Clear();

	static KeyState GetKeyState(Key key);
	static bool GetKeyDown(Key key);
	static KeyEvent GetKeyEvent(Key key);
	static MousePosition GetMousePosition();
	static MousePosition GetMousePositionChange();

};

