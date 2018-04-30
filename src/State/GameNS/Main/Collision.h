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
	//当たり判定を直方体として考える
	float *x, *y, *z;//直方体の真ん中の座標(y座標のみ真ん中ではない)
	float *w, *h, *d;//直方体の長さ(w,dは半分、hはそのまま)
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

