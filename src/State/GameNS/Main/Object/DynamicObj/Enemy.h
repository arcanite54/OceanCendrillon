#pragma once
#include "../DynamicObj.h"

class Enemy :public DynamicObj {

private:
	float target_x, target_z;
	static int ModelHandle_enemy_origin[2];
	int ModelHandle_enemy;
	bool positionFix;
	bool searchPlayer;
	bool alterstyle;
	static int img_shadow;
public:
	Enemy(float, float,float,float,float,float);
	~Enemy();
	void update(DynamicObj*);
	void update() {}
	void draw();
	void move();
	void animation();

};