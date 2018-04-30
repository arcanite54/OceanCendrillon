#pragma once

#include "Collision.h"
#include "../../../Data.h"
#include "../../../KeyInput.h"
class Collision;

extern enum TYPE;

class Object {

protected:
	float x, y, z;
	float w, h, d;
	float vx, vz;

	int AttachIndex;
	float TotalTime, PlayTime;
	float now_direction;
	Collision* coli;
	int count;
	int HP,MAXHP;
	bool delFlag;
	bool mutekiFlag;
	int mutekicount;
	bool bulletThrough;
	int bulletway;
	int bullettime;
	int itemnum;
	float speed;
	int power;

public:
	Object() {}
	virtual ~Object() {
		SAFE_DELETE(coli);
	}
	virtual void update()=0;
	virtual void draw()=0;

	Collision* getCollision() {return coli;}
	void damage(int n) {
		HP -= n;
		if (HP <= 0) {
			HP = 0;
			//delFlag = true;
		}
	}
	int getHP() {return HP;}
	int getMAXHP() { return MAXHP; }
	bool isDelete() {return delFlag;}
	void changeDel() {delFlag = true;}
	bool isMuteki() {return mutekiFlag;}
	void changeMuteki() {mutekiFlag = true;}
	VECTOR get_position() { return VGet(x, y, z); }
	float get_x() { return x; }
	float get_y() { return y; }
	float get_z() { return z; }
	bool isThrough() { return bulletThrough; }
	void changeway(int n) { if(bulletway<n)bulletway = n; }
	void changethrough() { bulletThrough=true; }
	void changetime(int n) { bullettime = n; }
	int getitemnum() { return itemnum; }
	void changeSpeed(float n) { speed = n; }
	int getPower() { return power; }
	void changePower(int n) { power = n; }
};


