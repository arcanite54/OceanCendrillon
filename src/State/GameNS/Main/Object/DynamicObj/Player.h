#pragma once
#include "../DynamicObj.h"

class Player:public DynamicObj {

private:
	bool shotFlag;
	int ModelHandle_player;
	int deadCount;
	bool isJump;
	int jumpcount;
	int img_shadow;
public:
	Player(int);
	~Player();
	void update();
	void draw();
	void move();
	int deadcount() { return deadCount; }
	void animation();

};