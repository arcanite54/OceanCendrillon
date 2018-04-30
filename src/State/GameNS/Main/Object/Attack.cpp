#include "Attack.h"

int Attack::ModelHandle_attack_origin[2] = { 10 ,10};


Attack::Attack(float _x, float _y, float _z, float _w, float _h, float _d,float t,bool s,bool _actor,int _power) {
	x = _x, y = _y, z = _z;
	w = _w, h = _h, d = _d;
	vx = -sin(t)*(_actor+1); vz =- cos(t)*(_actor + 1);
	power = _power;
	//3D���f���̓ǂݍ���
	if (ModelHandle_attack_origin[0] == 10) ModelHandle_attack_origin[0] = MV1LoadModel("Data/model/bullet2.pmx");
	if (ModelHandle_attack_origin[1] == 10) ModelHandle_attack_origin[1] = MV1LoadModel("Data/model/bullet.pmx");

	ModelHandle_attack = MV1DuplicateModel(ModelHandle_attack_origin[_actor]);
	//������f���v���ɂ���
	// �R�c���f����1�Ԗڂ̃A�j���[�V�������A�^�b�`����
//	AttachIndex = MV1AttachAnim(ModelHandle, 0, -1, FALSE);

	// �A�^�b�`�����A�j���[�V�����̑��Đ����Ԃ��擾����
//	TotalTime = MV1GetAttachAnimTotalTime(ModelHandle_attack, AttachIndex);

	// �Đ����Ԃ̏�����
	//PlayTime = 0.0f;

//	now_direction = atan2(0, -1);
	coli = new Collision(&x, &y, &z, &w, &h, &d,type_atk);
	coli->registParent(this);
	count = 0;
	delFlag = false;
	MAXHP = 100;
	HP = MAXHP;
	bulletThrough = s;
}


Attack::~Attack() {
	MV1DeleteModel(ModelHandle_attack);
}

void Attack::update() {
	//	coli=HitCheck_Capsule_Capsule(VGet(x,y,z),VGet(x,y,z),
		//test();
	//	if(count%150==0)coli.push_back(new Collision(x, y, z, 3.0f, 3.0f, 3.0f, Attack));
	x += vx;
	z += vz;
	count++;
	if (count == 300)delFlag = true;

}

void Attack::draw() {


	// �w��ʒu�Ƀ��f����z�u
	MV1SetPosition(ModelHandle_attack, VGet(x, y, z));



	// �Đ����Ԃ��Z�b�g����
//	MV1SetAttachAnimTime(ModelHandle, AttachIndex, PlayTime);




	// �R�c���f���̕`��
	MV1DrawModel(ModelHandle_attack);

	coli->draw();
	//DrawFormatString(0, 15, GetColor(255, 255, 255), "vx=%.1f vz=%.1f", vx,vz);
}