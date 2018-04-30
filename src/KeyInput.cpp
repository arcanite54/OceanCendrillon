#include "DXLib.h"

#include <fstream>

unsigned INPUT_C = 128;
unsigned INPUT_Z = 16;
unsigned INPUT_X = 32;
unsigned INPUT_LSHIFT = 256;
unsigned INPUT_ESCAPE = 1024;
unsigned INPUT_UP = 8;
unsigned INPUT_RIGHT = 4;
unsigned INPUT_DOWN = 1;
unsigned INPUT_LEFT = 2;

const bool toBoolean[2] = { false, true };


bool Input_Z() {
	return toBoolean[CheckHitKey(KEY_INPUT_Z)] || !((GetJoypadInputState(DX_INPUT_PAD1) & INPUT_Z) == 0)
		|| toBoolean[CheckHitKey(KEY_INPUT_RETURN)];

}

bool Input_X() {
	return toBoolean[CheckHitKey(KEY_INPUT_X)] || !((GetJoypadInputState(DX_INPUT_PAD1) & INPUT_X) == 0);
}

bool Input_C() {
	return toBoolean[CheckHitKey(KEY_INPUT_C)] || !((GetJoypadInputState(DX_INPUT_PAD1) & INPUT_C) == 0);
}

bool Input_RIGHT() {
	return toBoolean[CheckHitKey(KEY_INPUT_RIGHT)] || !((GetJoypadInputState(DX_INPUT_PAD1) & INPUT_RIGHT) == 0)
		|| toBoolean[CheckHitKey(KEY_INPUT_D)];
}

bool Input_LEFT() {
	return toBoolean[CheckHitKey(KEY_INPUT_LEFT)] || !((GetJoypadInputState(DX_INPUT_PAD1) & INPUT_LEFT) == 0)
	|| toBoolean[CheckHitKey(KEY_INPUT_A)];
}

bool Input_UP() {
	return toBoolean[CheckHitKey(KEY_INPUT_UP)] || !((GetJoypadInputState(DX_INPUT_PAD1) & INPUT_UP) == 0)
		|| toBoolean[CheckHitKey(KEY_INPUT_W)];
}

bool Input_DOWN() {
	return toBoolean[CheckHitKey(KEY_INPUT_DOWN)] || !((GetJoypadInputState(DX_INPUT_PAD1) & INPUT_DOWN) == 0)
		|| toBoolean[CheckHitKey(KEY_INPUT_S)];
}

bool Input_RETURN() {
	return toBoolean[CheckHitKey(KEY_INPUT_RETURN)];
}

bool Input_BACK() {
	return toBoolean[CheckHitKey(KEY_INPUT_BACK)];
}

bool Input_SPACE() {
	return toBoolean[CheckHitKey(KEY_INPUT_SPACE)];
}

bool Input_ESCAPE() {
	return toBoolean[CheckHitKey(KEY_INPUT_ESCAPE)] || !((GetJoypadInputState(DX_INPUT_PAD1) & INPUT_ESCAPE) == 0);
}

bool Input_SHIFT() {
	return toBoolean[CheckHitKey(KEY_INPUT_LSHIFT)] || !((GetJoypadInputState(DX_INPUT_PAD1) & INPUT_LSHIFT) == 0)
		|| toBoolean[CheckHitKey(KEY_INPUT_RSHIFT)];
}

bool Input_ALL() {
	return (CheckHitKeyAll() ? true : false);
}

//PS2コントローラー用
void initKeyData() {
	std::ifstream fin("key.txt");
	fin >> INPUT_C;
	fin >> INPUT_Z;
	fin >> INPUT_X;
	fin >> INPUT_LSHIFT;
	fin >> INPUT_ESCAPE;
	fin >> INPUT_UP;
	fin >> INPUT_RIGHT;
	fin >> INPUT_DOWN;
	fin >> INPUT_LEFT;
}

void keyConfig() {

	ClearDrawScreen();
	DrawString(100, 100, "Press triangle", GetColor(255, 255, 255));
	ScreenFlip();
	WaitKey();
	INPUT_C = (GetJoypadInputState(DX_INPUT_PAD1));
	WaitTimer(500);

	ClearDrawScreen();
	DrawString(100, 100, "Press circle", GetColor(255, 255, 255));
	ScreenFlip();
	WaitKey();
	INPUT_Z = (GetJoypadInputState(DX_INPUT_PAD1));
	WaitTimer(500);

	ClearDrawScreen();
	DrawString(100, 100, "Press cross", GetColor(255, 255, 255));
	ScreenFlip();
	WaitKey();
	INPUT_X = (GetJoypadInputState(DX_INPUT_PAD1));
	WaitTimer(500);

	ClearDrawScreen();
	DrawString(100, 100, "Press square", GetColor(255, 255, 255));
	ScreenFlip();
	WaitKey();
	INPUT_LSHIFT = (GetJoypadInputState(DX_INPUT_PAD1));
	WaitTimer(500);

	ClearDrawScreen();
	DrawString(100, 100, "Press escape", GetColor(255, 255, 255));
	ScreenFlip();
	WaitKey();
	INPUT_ESCAPE = (GetJoypadInputState(DX_INPUT_PAD1));
	WaitTimer(500);

	ClearDrawScreen();
	DrawString(100, 100, "Press up", GetColor(255, 255, 255));
	ScreenFlip();
	WaitKey();
	INPUT_UP = (GetJoypadInputState(DX_INPUT_PAD1));
	WaitTimer(500);

	ClearDrawScreen();
	DrawString(100, 100, "Press right", GetColor(255, 255, 255));
	ScreenFlip();
	WaitKey();
	INPUT_RIGHT = (GetJoypadInputState(DX_INPUT_PAD1));
	WaitTimer(500);

	ClearDrawScreen();
	DrawString(100, 100, "Press under", GetColor(255, 255, 255));
	ScreenFlip();
	WaitKey();
	INPUT_DOWN = (GetJoypadInputState(DX_INPUT_PAD1));
	WaitTimer(500);

	ClearDrawScreen();
	DrawString(100, 100, "Press left", GetColor(255, 255, 255));
	ScreenFlip();
	WaitKey();
	INPUT_LEFT = (GetJoypadInputState(DX_INPUT_PAD1));

	std::ofstream fout("key.txt");
	fout << INPUT_C << std::endl;
	fout << INPUT_Z << std::endl;
	fout << INPUT_X << std::endl;
	fout << INPUT_LSHIFT << std::endl;
	fout << INPUT_ESCAPE << std::endl;
	fout << INPUT_UP << std::endl;
	fout << INPUT_RIGHT << std::endl;
	fout << INPUT_DOWN << std::endl;
	fout << INPUT_LEFT << std::endl;

	initKeyData();
}
