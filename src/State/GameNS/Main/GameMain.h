#pragma once
#include"../../../Data.h"
#include "../GameParent.h"
#include "../GameChild.h"

class Player;
class Enemy;
class Castle;
class Item;
namespace StateNS {
namespace GameStateNS {


class GameMain : public GameChild{

private:

	Player* player;
	std::list<Enemy*> enemy;
	Castle* castle;
	std::list<Item*> item;
	int time;
	int count_start,count_play,count_finish;
	int img_number[10];
	int img_call[2];
	int img_icon[2];
	int HPicon;
	enum STAGE {
		STAGE_start,
		STAGE_play,
		STAGE_finish,
	};
	STAGE stage;
	int ModelHandle_floor;
	bool gameclear;
	int se[2];
	int bgm;
	int deadenemyCount;
	int difficult;
public:
	GameMain(int);
	~GameMain();

	GameChild* update(GameParent*);
	void draw() const;
	void play_update();

};

class Tutorial : public GameChild {

private:

	Player* player;
//	std::list<Enemy*> enemy;
	Castle* castle;
//	std::list<Item*> item;
//	int time;
//	int count_start, count_play, count_finish;
//	int img_number[10];
//	int img_call[2];
//	int img_icon[2];
	int HPicon;
/*
	enum STAGE {
		STAGE_start,
		STAGE_play,
		STAGE_finish,
	};
	*/
//	STAGE stage;
	int ModelHandle_floor;
//	bool gameclear;
//	int se[2];
	int bgm;
//	int deadenemyCount;
public:
	Tutorial();
	~Tutorial();

	GameChild* update(GameParent*);
	void draw() const;
	void play_update();

};



}
}