#include "Item.h"

int Item::ModelHandle_item_origin[7] = { 10 ,10,10,10,10,10,10 };


Item::Item(float _x, float _y, float _z) {
	x = _x, y = _y+5.0f, z = _z;
	w = 5.0f, h = 4.0f, d = 5.0f;
	//3Dモデルの読み込み
	if (ModelHandle_item_origin[0] == 10) ModelHandle_item_origin[0] = MV1LoadModel("Data/model/itemicon/2way/itemicon.pmx");
	if (ModelHandle_item_origin[1] == 10) ModelHandle_item_origin[1] = MV1LoadModel("Data/model/itemicon/3way/itemicon.pmx");
	if (ModelHandle_item_origin[2] == 10) ModelHandle_item_origin[2] = MV1LoadModel("Data/model/itemicon/rapid/itemicon.pmx");
	if (ModelHandle_item_origin[3] == 10) ModelHandle_item_origin[3] = MV1LoadModel("Data/model/itemicon/through/itemicon.pmx");
	if (ModelHandle_item_origin[4] == 10) ModelHandle_item_origin[4] = MV1LoadModel("Data/model/itemicon/heart/itemicon.pmx");
	if (ModelHandle_item_origin[5] == 10) ModelHandle_item_origin[5] = MV1LoadModel("Data/model/itemicon/power/itemicon.pmx");
	if (ModelHandle_item_origin[6] == 10) ModelHandle_item_origin[6] = MV1LoadModel("Data/model/itemicon/speed/itemicon.pmx");


	itemnum = GetRand(100) % 7;
	
	ModelHandle_item = MV1DuplicateModel(ModelHandle_item_origin[itemnum]);
	//これもデュプリにする
	// ３Ｄモデルの1番目のアニメーションをアタッチする
	//	AttachIndex = MV1AttachAnim(ModelHandle, 0, -1, FALSE);

	// アタッチしたアニメーションの総再生時間を取得する
	//TotalTime = MV1GetAttachAnimTotalTime(ModelHandle_item, AttachIndex);
	// 指定位置にモデルを配置
	MV1SetPosition(ModelHandle_item, VGet(x, y, z));


	MV1SetRotationXYZ(ModelHandle_item, VGet(-Pi/2, 0.0f, 0.0f));
	// 再生時間の初期化
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





	// 再生時間をセットする
	//	MV1SetAttachAnimTime(ModelHandle, AttachIndex, PlayTime);




	// ３Ｄモデルの描画
	MV1DrawModel(ModelHandle_item);

	coli->draw();
	//DrawFormatString(0, 15, GetColor(255, 255, 255), "vx=%.1f vz=%.1f", vx,vz);
}