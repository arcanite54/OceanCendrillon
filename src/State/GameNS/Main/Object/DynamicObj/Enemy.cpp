#include "Enemy.h"
int Enemy::ModelHandle_enemy_origin[2] = { 10 ,10};
int Enemy::img_shadow = -1;
Enemy::Enemy(float _x, float _y, float _z, float _w, float _h, float _d) {
	x = _x, y = _y, z = _z;
	w = _w, h = _h, d = _d;
	vx = 0.0f; vz = 0.0f;
	MAXHP = 200;
	HP = MAXHP;
	//3Dモデルの読み込み
	if(ModelHandle_enemy_origin[0]==10)ModelHandle_enemy_origin[0] = MV1LoadModel("Data/model/enemy/enemy.pmx");
	if (ModelHandle_enemy_origin[1] == 10)ModelHandle_enemy_origin[1] = MV1LoadModel("Data/model/enemy/enemyalter.pmx");
	if (img_shadow == -1)img_shadow = LoadGraph("Data/image/shadow.png");
	if (GetRand(60) % 3 == 0) {
		HP = 100;
		searchPlayer = true;
		alterstyle = true;
	}
	else {
		alterstyle = false;
		searchPlayer = false;
	}
	ModelHandle_enemy = MV1DuplicateModel(ModelHandle_enemy_origin[searchPlayer]);
	target_x = (float)GetRand(20) - 10.0f;
	target_z = (float)GetRand(20) - 10.0f;


	// ３Ｄモデルの1番目のアニメーションをアタッチする
	AttachIndex = MV1AttachAnim(ModelHandle_enemy, 0, -1, FALSE);

	// アタッチしたアニメーションの総再生時間を取得する
	TotalTime = MV1GetAttachAnimTotalTime(ModelHandle_enemy, AttachIndex);

	// 再生時間の初期化
	PlayTime = 8.0f;
	coli=new Collision(&x, &y, &z, &w, &h, &d,type_body);
	coli->registParent(this);
	now_direction = atan2(0, 1);
	count = 0;
	delFlag = false;
	mutekiFlag = false;
	mutekicount = 0;
	positionFix = false;
	bulletThrough = false;
	animeNum = 0;
	speed = 2.0f;
	power = 100;
}

Enemy::~Enemy() {
	MV1DeleteModel(ModelHandle_enemy);
}

void Enemy::update(DynamicObj* other) {
	if (HP == 0)delFlag = true;
	animation();
	if (HP == 100 && !alterstyle) {
		MV1DetachAnim(ModelHandle_enemy, AttachIndex);
		AttachIndex = MV1AttachAnim(ModelHandle_enemy, 1, -1, FALSE);
		TotalTime = MV1GetAttachAnimTotalTime(ModelHandle_enemy, AttachIndex);
		PlayTime = 0.0f;
		alterstyle = true;
	}
	if (searchPlayer) {
		target_x = other->get_x();
		target_z = other->get_z();
	}
	move();
	set_direction(&ModelHandle_enemy);
	muteki(90);

	count++;
	if (x < -110.0f || 110.0f < x || z < -110.0f || 110.0f < z) {
		mutekiFlag = true;
		return;
	}
	if (count%150==0)atk_obj.push_back(new Attack(x, y + 7.0f, z, 1.4f, 1.0f, 1.4f, now_direction,bulletThrough,false,power));

	attack();

}

void Enemy::draw() {

	// 指定位置にモデルを配置
	MV1SetPosition(ModelHandle_enemy, VGet(x, y, z));


	// 再生時間をセットする
	MV1SetAttachAnimTime(ModelHandle_enemy, AttachIndex, PlayTime);
	flashing(&ModelHandle_enemy);
	DrawBillboard3D(VGet(x, 0, z), 0.5f, 0.5f, 5.0f, 0, img_shadow, TRUE);

	// ３Ｄモデルの描画
	MV1DrawModel(ModelHandle_enemy);
// ３Ｄ空間上に球を描画する
	//DrawSphere3D(VGet(x, y, z), 5.0f, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);
	coli->draw();
}

void Enemy::move() {
	float speedEX = speed;
	vx = 0.0f, vz = 0.0f;
	if (alterstyle && !searchPlayer)positionFix = true;
	if (!positionFix) {
		if (x > target_x+0.5f)vx = -0.1f;
		if (x < target_x-0.5f)vx = 0.1f;

		if (z > target_z+0.5f)vz = -0.1f;
		if (z < target_z-0.5f)vz = 0.1f;
		if (vx != 0.0f && vz != 0.0f)speedEX /= sqrt(2);
	}
	if (canPass(x + vx*speedEX, z + vz*speedEX)) {
		x += vx*speedEX;
		z += vz*speedEX;
		positionFix = false;
	}
	else positionFix = true;

}



void Enemy::animation() {
	// 再生時間を進める
	if (vx != 0.0f || vz != 0.0f)PlayTime += 0.5f;
	else if (alterstyle && !searchPlayer)PlayTime += 0.5f;
	else PlayTime = 8.0f;

	// 再生時間がアニメーションの総再生時間に達したら再生時間を０に戻す
	if (PlayTime >= TotalTime) {
		if (alterstyle && !searchPlayer) {
			searchPlayer = true;
			ModelHandle_enemy = MV1DuplicateModel(ModelHandle_enemy_origin[searchPlayer]);
			MV1DetachAnim(ModelHandle_enemy, AttachIndex);
			AttachIndex = MV1AttachAnim(ModelHandle_enemy, 0, -1, FALSE);
			TotalTime = MV1GetAttachAnimTotalTime(ModelHandle_enemy, AttachIndex);
			positionFix = false;
		}
		PlayTime = 0.0f;
	}

}