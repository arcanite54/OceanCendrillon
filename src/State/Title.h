#pragma once

#include "Child.h"

namespace StateNS{

class Parent;

class Title : public Child{
public:
	Title::Title();
	Title::~Title();
	Child* update(Parent*);
	void draw() const;
private:
	int graph[2];
	int count = 0;
	int bgm;
	bool pushZ,pushUP,pushDOWN;
	int step;
	int select;
};

class Op : public Child {
public:
	Op::Op();
	Op::~Op();
	Child* update(Parent*);
	void draw() const;
private:
	int count = 0;
	int movie;
};



}