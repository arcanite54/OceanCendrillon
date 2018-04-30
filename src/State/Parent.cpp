

#include "../Data.h"
#include "Parent.h"
#include "Title.h"

namespace StateNS {


Parent::Parent() :
fTitle(false){
	this->mChild = new Op();
}

Parent::~Parent() {

}

Child* Parent::update() {

	Child* next = mChild->update(this);

	if (next != mChild) {
		SAFE_DELETE(mChild);
		mChild = next;
	}

	next = 0;

	if (fTitle) {//ƒ^ƒCƒgƒ‹‚É–ß‚é
		SAFE_DELETE(mChild);
		mChild = new Title();
		fTitle = false;
	}


	return next;
}

void Parent::draw() const {
	mChild->draw();
}

void Parent::moveTo() {
	fTitle = true;
}

//---------------private---------------






}
