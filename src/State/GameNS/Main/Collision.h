#pragma once
#include "Object.h"

class Object;
enum TYPE {
	type_body,
	type_atk,
	type_castle,
	type_item,
};

class Collision {
private:
	//�����蔻��𒼕��̂Ƃ��čl����
	float *x, *y, *z;//�����̂̐^�񒆂̍��W(y���W�̂ݐ^�񒆂ł͂Ȃ�)
	float *w, *h, *d;//�����̂̒���(w,d�͔����Ah�͂��̂܂�)
	TYPE colitype;
	Object* parent;
	void process(Object*);
	static int se[2];
public:
	Collision(float*,float*,float*,float*,float*,float*,TYPE);
	Collision(float, float, float, float, float, float,TYPE);
	~Collision();
	bool isHit(const Collision*)const;
	void update(Object*);
	void draw();
	void registParent(Object* p) {parent = p;}
	TYPE getType() {return colitype;}
	void itemget(int);
};

