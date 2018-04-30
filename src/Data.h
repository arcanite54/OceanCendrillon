#pragma once

#include <assert.h>
#include <array>
#include <list>
#include <cmath> //極座標を使用

#include"DxLib.h"


//円周率
#define Pi 3.14159265358979f


//deleteと0ポインタ
#define SAFE_DELETE(p){\
	delete (p);\
	(p) = 0;\
}

//delete[]と0ポインタ
#define SAFE_DELETE_ARRAY(p){\
	delete[] (p);\
	(p) = 0;\
}

//穴あき配列をSAFE_DELETE
#define SAFE_DELETE_EACH(p){\
	for(auto a : dynamic_cast<p>) { SAFE_DELETE(a); }\
}

const int cx = 320;
const int cy = 240;

float convert_x(float angle, float r);
float convert_y(float angle, float r);



//整数型2次元座標 + 幅高さのクラス
class Point {
public:
	float r;
	float angle;
	int w;
	int h;

	Point() { r = angle = w = h = 0; }
	Point(float _r, float _angle, int _w, int _h){
		r = _r;
		angle = _angle;
		w = _w;
		h = _h;
	}
};


