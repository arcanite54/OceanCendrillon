#include "Player.h"

Player::Player(int n) {
	x = 0.0f, y = 0.0f, z = -50.0f;
	w = 3.0f, h = 15.0f, d = 3.0f;
	vx = 0.0f; vz = 0.0f;
	MAXHP = 700-200*n;
	HP = MAXHP;
	//3Dモデルの読み込み
	ModelHandle_player = MV1LoadModel("Data/model/midori/midori.pmx");
	img_shadow=LoadGraph("Data/image/shadow.png");
	//MV1SetUseZBuffer(ModelHandle_player,FALSE);
	//MV1SetWriteZBuffer(ModelHandle_player, FALSE);


	AttachIndex = MV1AttachAnim(ModelHandle_player, 0, -1, FALSE);
	TotalTime = MV1GetAttachAnimTotalTime(ModelHandle_player, AttachIndex);
	PlayTime = 8.0f;

	now_direction = atan2(0,-1);
	coli = new Collision(&x, &y, &z, &w, &h, &d,type_body);
	coli->registParent(this);
	count = 0;
	delFlag = false;
	mutekiFlag = false;
	mutekicount = 0;
	shotFlag = false;
	bulletway = 1;
	bullettime = 40;
	bulletThrough = false;
	animeNum = 0;
	deadCount = 0;
	speed = 7.0f;
	power = 100;
	isJump = false;
	jumpcount = 0;
}

Player::~Player() {
	MV1DeleteModel(ModelHandle_player);
}

void Player::update() {
	animation();
	if (HP == 0 && animeNum!=2){
		MV1DetachAnim(ModelHandle_player, AttachIndex);
		AttachIndex = MV1AttachAnim(ModelHandle_player, 2, -1, FALSE);
		TotalTime = MV1GetAttachAnimTotalTime(ModelHandle_player, AttachIndex);
		TotalTime *= 2;
		PlayTime = 0.0f;
		animeNum=2;
		deadCount = 0;
	}
	
	if (animeNum == 2) {
		deadCount++;
		return;
	}
	move();

	set_direction(&ModelHandle_player);
	muteki(150);
	if (Input_Z()&& !shotFlag) {
		if (animeNum == 0) {
			MV1DetachAnim(ModelHandle_player, AttachIndex);
			AttachIndex = MV1AttachAnim(ModelHandle_player, 1, -1, FALSE);
			TotalTime = MV1GetAttachAnimTotalTime(ModelHandle_player, AttachIndex);
			PlayTime = 8.0f;
			animeNum = 1;
		}
		float hitsize = 1.8f;
		switch (bulletway) {
		case 1:
			atk_obj.push_back(new Attack(x, y + 7.0f, z, hitsize, 1.0f, hitsize, now_direction,bulletThrough,true,power));
			break;
		case 2:
			atk_obj.push_back(new Attack(x, y + 7.0f, z, hitsize, 1.0f, hitsize, now_direction+Pi/100, bulletThrough,true,power));
			atk_obj.push_back(new Attack(x, y + 7.0f, z, hitsize, 1.0f, hitsize, now_direction-Pi/100, bulletThrough,true,power));
			break;
		case 3:
			atk_obj.push_back(new Attack(x, y + 7.0f, z, hitsize, 1.0f, hitsize, now_direction, bulletThrough,true,power));
			atk_obj.push_back(new Attack(x, y + 7.0f, z, hitsize, 1.0f, hitsize, now_direction + Pi / 6, bulletThrough,true,power));
			atk_obj.push_back(new Attack(x, y + 7.0f, z, hitsize, 1.0f, hitsize, now_direction - Pi / 6, bulletThrough,true,power));
			break;
		}
		shotFlag = true;
	}
	if (!(Input_Z()) &&animeNum == 1) {
		MV1DetachAnim(ModelHandle_player, AttachIndex);
		AttachIndex = MV1AttachAnim(ModelHandle_player, 0, -1, FALSE);
		TotalTime = MV1GetAttachAnimTotalTime(ModelHandle_player, AttachIndex);
		PlayTime = 8.0f;
		animeNum = 0;
	}
	if (shotFlag)count++;
	if(count>=bullettime){
		shotFlag = false;
		count = 0;
	}
	attack();
}

void Player::draw() {

	SetCameraPositionAndTarget_UpVecY(VGet(x, y + 40, z - 40), VGet(x, y, z));

	// 指定位置にモデルを配置
	MV1SetPosition(ModelHandle_player, VGet(x, y, z));



	// 再生時間をセットする
	MV1SetAttachAnimTime(ModelHandle_player, AttachIndex, PlayTime);

	flashing(&ModelHandle_player);
	DrawBillboard3D(VGet(x, 0, z), 0.5f, 0.5f, 5.0f, 0, img_shadow, TRUE);

	// ３Ｄモデルの描画
	MV1DrawModel(ModelHandle_player);

	coli->draw();
//	DrawFormatString(0, 300, GetColor(255, 255, 255), "%d", animeNum);

//	DrawFormatString(0, 15, GetColor(255, 255, 255), "x=%.1f z=%.1f", x,z);
	//DrawFormatString(0, 30, GetColor(255, 255, 255), "vx=%.1f vz=%.1f", vx, vz);
}

void Player::move() {
	float speedEX = speed;
	if (Input_SHIFT())speedEX = 0.0f;
	vx = 0.0f, vz = 0.0f;
	if (Input_SPACE() && !isJump)isJump = true;
	if (isJump) {
		jumpcount++;
		y = 4.0f*jumpcount-0.1f*jumpcount*jumpcount;
		if (jumpcount == 40) {
			isJump = false;
			jumpcount = 0;
		}
	}

	if (Input_RIGHT())vx = 0.1f;
	if (Input_LEFT())vx = -0.1f;
	if (Input_UP()) vz = 0.1f;
	if (Input_DOWN())vz = -0.1f;

	if (vx != 0.0f && vz != 0.0f)speedEX/= sqrt(2);

	if (canPass(x+vx*speedEX, z+vz*speedEX)) {
		x += vx*speedEX;
		z += vz*speedEX;
	}
//	DrawFormatString(300, 30, GetColor(255, 255, 255), "spe%f,%f", vx, vz);
	//移動限界(プレイヤーのみ)
	x = max(min(x, 100.0f),-100.0f);
	z = max(min(z, 100.0f), -100.0f);

}

void Player::animation() {
	// 再生時間を進める
	if(vx!=0.0f ||vz!=0.0f)PlayTime += 0.5f;
	else if (animeNum == 2)PlayTime += 0.5f;
	else PlayTime = 8.0f;

	// 再生時間がアニメーションの総再生時間に達したら再生時間を０に戻す
	if (PlayTime >= TotalTime) {
		PlayTime = 0.0f;
	}

}

