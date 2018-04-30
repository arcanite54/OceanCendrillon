#include "Castle.h"

Castle::Castle() {
	x = 0.0f, y = 0.0f, z = 0.0f;
	w = 10.0f, h = 10.0f, d = 10.0f;

	//3D���f���̓ǂݍ���
	ModelHandle_castle = MV1LoadModel("Data/model/castle/castle.pmx");
	MV1SetRotationXYZ(ModelHandle_castle, VGet(0.0f, atan2(0,-1), 0.0f));
	//	now_direction = atan2(0, -1);
	coli = new Collision(&x, &y, &z, &w, &h, &d, type_castle);
	coli->registParent(this);
	count = 0;
	delFlag = false;
	mutekiFlag = false;
	mutekicount = 0;
	MAXHP = 13000;
	HP = MAXHP;
	// �w��ʒu�Ƀ��f����z�u
	MV1SetPosition(ModelHandle_castle, VGet(x, y, z));
	bulletThrough = false;

}

Castle::~Castle() {
	MV1DeleteModel(ModelHandle_castle);
}

void Castle::update() {
	mutekicount = 0;
	mutekiFlag = false;
}

void Castle::draw() {

	// �Đ����Ԃ��Z�b�g����
	//	MV1SetAttachAnimTime(ModelHandle, AttachIndex, PlayTime);



	// �R�c���f���̕`��
	MV1DrawModel(ModelHandle_castle);
	coli->draw();

	//DrawFormatString(0, 0, GetColor(255, 255, 255), "x=%.1f y=%.1f z=%.1f", x, y, z);
	//DrawFormatString(0, 15, GetColor(255, 255, 255), "vx=%.1f vz=%.1f", vx,vz);
}