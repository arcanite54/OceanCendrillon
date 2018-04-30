#include "ClearOver.h"
#include "../../KeyInput.h"

namespace StateNS {
namespace GameStateNS{


//------------------------------
//Clear�N���X
//------------------------------
Clear::Clear() : 
time(0){
	img = LoadGraph("Data/image/clear.png");
	bgm = LoadSoundMem("Data/music/clearover/se_maoudamashii_jingle05.wav");
	PlaySoundMem(bgm, DX_PLAYTYPE_BACK,TRUE);
	ModelHandle_player = MV1LoadModel("Data/model/midori/midori.pmx");
	AttachIndex = MV1AttachAnim(ModelHandle_player, 3, -1, FALSE);
	TotalTime = MV1GetAttachAnimTotalTime(ModelHandle_player, AttachIndex);
	PlayTime = 0.0f;
	SetCameraPositionAndTarget_UpVecY(VGet(0.0f, 10.0f, -50.0f), VGet(1.0f, 20.0f, 0.0f));

	// �w��ʒu�Ƀ��f����z�u
	MV1SetPosition(ModelHandle_player, VGet(20.0f, 0.0f, 0.0f));

}

Clear::~Clear() {

}

GameChild* Clear::update(GameParent* parent) {
	
	GameChild* next = this;
	time++;

	//�I��
//	if (Input_UP())nowRetry = true;
	//else if (Input_DOWN())nowRetry = false;
	PlayTime += 0.5f;
	if (PlayTime >= TotalTime) {
		PlayTime = 0.0f;
	}


	if (time > 90 && Input_Z()) {
		StopSoundMem(bgm);
		//�^�C�g����
		parent->moveTo(parent->NextSeq::SEQ_TITLE);
	}


	return next;
}

void Clear::draw() const {
//	DrawFormatString(cx, 100, GetColor(0, 255, 0), "Clear");
	DrawGraph(0, 0, img, FALSE);




	// �Đ����Ԃ��Z�b�g����
	MV1SetAttachAnimTime(ModelHandle_player, AttachIndex, PlayTime);

	// �R�c���f���̕`��
	MV1DrawModel(ModelHandle_player);


}


//------------------------------
//Over�N���X
//------------------------------
Over::Over() : time(0){
	img = LoadGraph("Data/image/over.png");
	bgm = LoadSoundMem("Data/music/clearover/se_maoudamashii_jingle11.wav");
	PlaySoundMem(bgm, DX_PLAYTYPE_BACK,TRUE);

}

Over::~Over() {

}

GameChild* Over::update(GameParent* parent) {
	GameChild* next = this;

	time++;


//	if (Input_UP())nowRetry = true;
//	else if (Input_DOWN())nowRetry = false;
	if (time > 90 && Input_Z()) {
		StopSoundMem(bgm);
		parent->moveTo(parent->NextSeq::SEQ_TITLE);
	}

	return next;
}

void Over::draw() const {
//	DrawFormatString(cx, 100, GetColor(0, 255, 0), "Over");
	DrawGraph(0, 0, img, FALSE);
	
	
}



}
}
