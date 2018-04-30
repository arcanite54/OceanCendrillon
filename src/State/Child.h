#pragma once


namespace StateNS {
	class Parent;

class Child{
  public:
	virtual ~Child(){}
	virtual Child* update(Parent*) = 0;
	virtual void draw() const = 0;
};

}