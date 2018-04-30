#pragma once

#include "Child.h"

namespace StateNS{

	class Child;

class Parent{
public:
	Parent::Parent();
	Parent::~Parent();
	
	Child* update();
	void draw() const;
	void moveTo();
	
private:
	Child* mChild;
	bool fTitle;
};


}