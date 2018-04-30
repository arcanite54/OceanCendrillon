#pragma once

class Parent;


namespace StateNS {
namespace GameStateNS{

class GameParent;

class GameChild {
public:
	virtual ~GameChild() {}
	virtual GameChild* update(GameParent*) = 0;
	virtual void draw() const = 0;
};


}
}