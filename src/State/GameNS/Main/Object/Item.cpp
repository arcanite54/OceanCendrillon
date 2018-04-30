#include "Item.h"

int Item::ModelHandle_item_origin[7] = { 10 ,10,10,10,10,10,10 };


Item::Item(float _x, float _y, float _z) {
	x = _x, y = _y+5.0f, z = _z;
	w = 5.0f, h = 4.0f, d = 5.0f;
	//3D���f���̓ǂݍ���
	if (ModelHandle_item_origin[0] == 10) ModelHandle_item_origin[0] = MV1LoadModel("Data/model/itemicon/2way/itemicon.pmx");
	if (ModelHandle_item_origin[1] == 10) ModelHandle_item_origin[1] = MV1LoadModel("Data/model/itemicon/3way/itemicon.pmx");
	if (ModelHandle_item_origin[2] == 10) ModelHandle_item_origin[2] = MV1LoadModel("Data/model/itemicon/rapid/itemicon.pmx");
	if (ModelHandle_item_origin[3] == 10) ModelHandle_item_origin[3] = MV1LoadModel("Data/model/itemicon/through/itemicon.pmx");
	if (ModelHandle_item_origin[4] == 10) ModelHandle_item_origin[4] = MV1LoadModel("Data/model/itemicon/heart/itemicon.pmx");
	if (ModelHandle_item_origin[5] == 10) ModelHandle_item_origin[5] = MV1LoadModel("Data/model/itemicon/power/itemicon.pmx");
	if (ModelHandle_item_origin[6] == 10) ModelHandle_item_origin[6] = MV1LoadModel("Data/model/itemicon/speed/itemicon.pmx");


	itemnum = GetRand(100) % 7;
	
	ModelHandle_item = MV1DuplicateModel(ModelHandle_item_origin[itemnum]);
	//������f���v���ɂ���
	// �R�c���f����1�Ԗڂ̃A�j���[�V�������A�^�b�`����
	//	AttachIndex = MV1AttachAnim(ModelHandle, 0, -1, FALSE);

	// �A�^�b�`�����A�j���[�V�����̑��Đ����Ԃ��擾����
	//TotalTime = MV1GetAttachAnimTotalTime(ModelHandle_item, AttachIndex);
	// �w��ʒu�Ƀ��f����z�u
	MV1SetPosition(ModelHandle_item, VGet(x, y, z));


	MV1SetRotationXYZ(ModelHandle_item, VGet(-Pi/2, 0.0f, 0.0f));
	// �Đ����Ԃ̏�����
//	PlayTime = 0.0f;

	//	now_direction = atan2(0, -1);
	coli = new Collision(&x, &y, &z, &w, &h, &d, type_item);
	coli->registParent(this);
	count = 0;
	delFlag = false;
	MAXHP = 100;
	HP = MAXHP;
	bulletThrough = false;

}


Item::~Item() {
	MV1DeleteModel(ModelHandle_item);
}

void Item::update() {
	//	coli=HitCheck_Capsule_Capsule(VGet(x,y,z),VGet(x,y,z),
	//test();
	//	if(count%150==0)coli.push_back(new Collision(x, y, z, 3.0f, 3.0f, 3.0f, Item));
	count++;
	if (count == 900)delFlag = true;

}

void Item::draw() {





	// �Đ����Ԃ��Z�b�g����
	//	MV1SetAttachAnimTime(ModelHandle, AttachIndex, PlayTime);




	// �R�c���f���̕`��
	MV1DrawModel(ModelHandle_item);

	coli->draw();
	//DrawFormatString(0, 15, GetColor(255, 255, 255), "vx=%.1f vz=%.1f", vx,vz);
}