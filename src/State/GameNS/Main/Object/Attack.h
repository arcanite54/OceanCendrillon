#pragma once
#include "../Object.h"

class Attack :public Object {

private:
	static int ModelHandle_attack_origin[2];
	int ModelHandle_attack;
	int actor;
public:
	Attack(float,float,float,float,float,float,float,bool,bool,int);
	~Attack();
	void update();
	void draw();

};