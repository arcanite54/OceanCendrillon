#include "DxLib.h"

#include "../Data.h"
#include "../KeyInput.h"
#include "GameNS/GameParent.h"
#include "Config.h"

namespace StateNS {


Title::Title() {
	
}

Title::~Title() {

}

Child* Title::update(Parent *parent) {
	Child* next = this;
	switch (step) {
	case 0://push z key
		count = (count+1) % 120;
		if (Input_Z() && pushZ)step++;
		break;
	case 1://ゲームスタート、そうさせつめい
		if (Input_Z() && pushZ) {
			if(select==0)step++;
			else if(select==1)next = new GameStateNS::GameParent(3);
		}
		if ((Input_UP()&& pushUP)||(Input_DOWN()&&pushDOWN))select = (select+1) %2;
		break;
	case 2:		
		if (Input_Z() && pushZ) {
			if (select == 3) {
				select = 0;
				step--;
			}
			else next = new GameStateNS::GameParent(select);
		}
		if (Input_UP() && pushUP)select = (select + 3) % 4;
		if (Input_DOWN()&& pushDOWN)select = (select + 1) % 4;
		break;
	}

	
	if (!Input_Z())pushZ = true;
	else pushZ = false;

	if (!Input_UP())pushUP = true;
	else pushUP = false;

	if (!Input_DOWN())pushDOWN = true;
	else pushDOWN = false;


	return next;
}

void Title::draw() const {
	//for Debug
//	DrawFormatString(0, 0, GetColor(255, 255, 255), "Title");
//	DrawFormatString(0, 100, GetColor(255, 255, 255), "press X key");
	DrawGraph(0, 0, graph[0], FALSE);

	switch (step) {
	case 0:
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (count - 60)*(count - 60));
		DrawGraph(0, 0, graph[1], TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		break;
	case 1:
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		DrawFormatString(250, 350, GetColor(0, 0, 0), "ゲームスタート");
		DrawFormatString(250, 380, GetColor(0, 0, 0), "そうさせつめい");
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		if(select==0)DrawFormatString(250, 350, GetColor(0, 0, 0), "ゲームスタート");
		else if(select==1)DrawFormatString(250, 380, GetColor(0, 0, 0), "そうさせつめい");

		break;
	case 2:
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		DrawFormatString(250, 330, GetColor(0, 0, 0), "かんたん");
		DrawFormatString(250, 360, GetColor(0, 0, 0), "ふつう");
		DrawFormatString(250, 390, GetColor(0, 0, 0), "むずかしい");
		DrawFormatString(250, 420, GetColor(0, 0, 0), "戻る");
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		if (select == 0)DrawFormatString(250, 330, GetColor(0, 0, 0), "かんたん");
		else if (select == 1)DrawFormatString(250, 360, GetColor(0, 0, 0), "ふつう");
		else if(select==2)DrawFormatString(250, 390, GetColor(0, 0, 0), "むずかしい");
		else if (select == 3)DrawFormatString(250, 420, GetColor(0, 0, 0), "戻る");

		break;
	}
}


Op::Op() {
	movie = LoadGraph("Data/movie/OP2.ogv");
	PlayMovieToGraph(movie);

}

Op::~Op() {

}

Child* Op::update(Parent *parent) {
	Child* next = this;
	count++;

	if ((Input_Z()&&count>120) || GetMovieStateToGraph(movie)==0) {
		PauseMovieToGraph(movie);
		next = new Title();
	}
//	DrawFormatString(0, 100, GetColor(255, 255, 255), "fuga");

	return next;
}

void Op::draw() const {
	// ムービー映像を画面いっぱいに描画します
	DrawGraph(0, 0,  movie, FALSE);
//	PlayMovie("Data/movie/OP.mp4", 1, DX_MOVIEPLAYTYPE_BCANCEL);
//	DrawFormatString(0, 0, GetColor(255, 255, 255), "hoge");
	//DrawFormatString(0, 200, GetColor(255, 255, 255), "%d",movie);


}





}
