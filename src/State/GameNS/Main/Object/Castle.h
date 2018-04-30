#pragma once
#include "../Object.h"

class Castle :public Object {

private:
	int ModelHandle_castle;
public:
	Castle();
	~Castle();
	void update();
	void draw();

};