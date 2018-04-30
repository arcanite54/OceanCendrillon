#pragma once
#include "../Object.h"

class Item :public Object {

private:
	static int ModelHandle_item_origin[7];
	int ModelHandle_item;
public:
	Item(float, float, float);
	~Item();
	void update();
	void draw();

};