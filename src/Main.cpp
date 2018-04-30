#include "DxLib.h"

#include "KeyInput.h"
#include "State/Parent.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(FALSE);
	DxLib_Init();
	SetMainWindowText("OceanCendrillon");
	SetOutApplicationLogValidFlag(FALSE);
	SetDrawScreen(DX_SCREEN_BACK);
	ClearDrawScreen();


	StateNS::Parent *parent = new StateNS::Parent();

	while (!ProcessMessage() && !Input_ESCAPE()) {
		ClearDrawScreen();

		parent->update();
		parent->draw();

		ScreenFlip();
	}

	InitGraph();

	DxLib_End();
	return 0;
}