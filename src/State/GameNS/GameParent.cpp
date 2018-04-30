#include "../../Data.h"
#include "GameParent.h"
#include "GameChild.h"
#include "Main/GameMain.h"
#include "../Title.h"

namespace StateNS {
namespace GameStateNS{



GameParent::GameParent(int n) :
fTitle(false){
	if (n == 3)this->mChild = new Tutorial();
	else this->mChild = new GameMain(n);
}

GameParent::~GameParent() {
	SAFE_DELETE(mChild);
}

Child* GameParent::update(Parent* parent) {
	Child* next = this;

	GameChild* nextChild = mChild->update(this);

	if (nextChild != mChild) {
		SAFE_DELETE(mChild);
		mChild = nextChild;
	}

	nextChild = 0;
	switch (mNext)
	{
	case SEQ_TITLE: next = new Title(); break;


	}

	mNext = SEQ_NONE;

	return next;
}

void GameParent::draw() const {
	mChild->draw();
}

void GameParent::moveTo(NextSeq _mNext)
{
	mNext = _mNext;
}


//---------------private---------------




}
}
