#pragma once

#include "../../Data.h"
#include "GameParent.h"

namespace StateNS{
namespace GameStateNS{



class Clear : public GameChild{
private:
	int time;
	int img;
//	bool nowRetry;
	int bgm;

	int ModelHandle_player;


	int AttachIndex;
	float TotalTime;
	float PlayTime;

public:
	Clear::Clear();
	Clear::~Clear();
	
	GameChild* update(GameParent*);
	void draw() const;
	
};


class Over : public GameChild {
private:
	int time;
	int img;
	int bgm;
public:
	Over::Over();
	Over::~Over();

	GameChild* update(GameParent*);
	void draw() const;

};



}
}