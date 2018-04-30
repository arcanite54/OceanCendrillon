#pragma once
#include "../Object.h"
#include "Attack.h"
class DynamicObj :public Object {
protected:

	std::list<Attack*>atk_obj;
	int animeNum;
public:
	DynamicObj() {};
	~DynamicObj() {
		for (auto v : atk_obj) {
			SAFE_DELETE(v);
		}
	}
	virtual void update()=0;
	virtual void draw()=0;
	void muteki(int);
	void attack();
	std::list<Attack*>getATKlist() {
		return atk_obj;
	}
	void flashing(int*);
	void set_direction(int*);

	bool canPass(float,float);

};