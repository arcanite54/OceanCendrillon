#include "Collision.h"

int Collision::se[2] = { 10 ,10};


Collision::Collision(float* _x, float* _y, float* _z,float* _w,float* _h,float* _d,TYPE t) {
	this->x = _x; this->y = _y; this->z = _z;
	this->w = _w; this->h = _h; this->d = _d;
	colitype = t;
	if(se[0]==10)se[0] = LoadSoundMem("Data/music/se/se_maoudamashii_se_pc03.wav");//’e”­Ë
	if(se[1]==10)se[1] = LoadSoundMem("Data/music/se/se_maoudamashii_explosion06.wav");//”í’e
	if (colitype == type_atk)PlaySoundMem(se[0], DX_PLAYTYPE_BACK);
}

Collision::Collision(float _x, float _y, float _z, float _w, float _h, float _d,TYPE t) {
	*this->x = _x; *this->y = _y; *this->z = _z;
	*this->w = _w; *this->h = _h; *this->d = _d;
	colitype = t;
	if (se[0] == 10)se[0] = LoadSoundMem("Data/music/se/se_maoudamashii_se_pc03.wav");//’e”­Ë
	if (se[1] == 10)se[1] = LoadSoundMem("Data/music/se/se_maoudamashii_explosion06.wav");//”í’e
	if (colitype == type_atk)PlaySoundMem(se[0], DX_PLAYTYPE_BACK);
}

Collision::~Collision() {
	//SAFE_DELETE(parent);
}

void Collision::process(Object* other) {
//	if (parent->isMuteki())return;

	char mask = 0;
	mask |= 1 << this->colitype;
	mask |= 1 << (other->getCollision())->getType();
	switch (mask) {
	case 0b0001://playerbody,enemybody
		if (!(parent->isMuteki())) {
			PlaySoundMem(se[1], DX_PLAYTYPE_BACK);

			parent->damage(100);
			parent->changeMuteki();
		}
		break;
	case 0b0011://atk,body

		if (!(parent->isMuteki())) {
			PlaySoundMem(se[1], DX_PLAYTYPE_BACK);

			parent->damage(other->getPower());
			parent->changeMuteki();
		}
		if (!(other->isThrough()))other->changeDel();
		break;
	case 0b0101://castle,playerbody
		//g‚¤‚©‚à‚µ‚ê‚È‚¢‚¯‚Ç‚½‚Ô‚ñg‚í‚È‚¢‚í
		break;
	case 0b0110://castle,atk
		if (!(parent->isMuteki())) {
			PlaySoundMem(se[1], DX_PLAYTYPE_BACK);

			parent->damage(100);
			//parent->changeMuteki();
			other->changeDel();
		}
		break;
	case 0b1001://item,playerbody
		itemget(other->getitemnum());
		other->changeDel();
		break;
	}
}

void Collision::itemget(int num) {
	switch (num) {
	case 0://2way
		parent->changeway(2);
		break;
	case 1://3way
		parent->changeway(3);
		break;
	case 2://rapid
		parent->changetime(15);
		break;
	case 3://through
		parent->changethrough();
		break;
	case 4://heart
		parent->damage(-100);
		break;
	case 5://power
		parent->changePower(200);
		break;
	case 6://speed
		parent->changeSpeed(10.0f);
		break;
	}


}

void Collision::update(Object* other) {

	if(isHit(other->getCollision()))process(other);
	
}

void Collision::draw() {
	/*
	DrawLine3D(VGet(*this->x - *this->w, *this->y , *this->z - *this->d), VGet(*this->x - *this->w, *this->y , *this->z + *this->d), GetColor(255, 0, 0));
	DrawLine3D(VGet(*this->x - *this->w, *this->y , *this->z - *this->d), VGet(*this->x + *this->w, *this->y , *this->z - *this->d), GetColor(255, 0, 0));
	DrawLine3D(VGet(*this->x - *this->w, *this->y , *this->z - *this->d), VGet(*this->x - *this->w, *this->y + *this->h, *this->z - *this->d), GetColor(255, 0, 0));
	
	DrawLine3D(VGet(*this->x + *this->w, *this->y + *this->h, *this->z + *this->d), VGet(*this->x + *this->w, *this->y , *this->z + *this->d), GetColor(255, 0, 0));
	DrawLine3D(VGet(*this->x + *this->w, *this->y + *this->h, *this->z + *this->d), VGet(*this->x + *this->w, *this->y + *this->h, *this->z - *this->d), GetColor(255, 0, 0));
	DrawLine3D(VGet(*this->x + *this->w, *this->y + *this->h, *this->z + *this->d), VGet(*this->x - *this->w, *this->y + *this->h, *this->z + *this->d), GetColor(255, 0, 0));
	
	DrawLine3D(VGet(*this->x - *this->w, *this->y + *this->h, *this->z + *this->d), VGet(*this->x - *this->w, *this->y + *this->h, *this->z - *this->d), GetColor(255, 0, 0));
	DrawLine3D(VGet(*this->x - *this->w, *this->y + *this->h, *this->z + *this->d), VGet(*this->x - *this->w, *this->y , *this->z + *this->d), GetColor(255, 0, 0));
	DrawLine3D(VGet(*this->x + *this->w, *this->y , *this->z + *this->d), VGet(*this->x - *this->w, *this->y , *this->z + *this->d), GetColor(255, 0, 0));
	DrawLine3D(VGet(*this->x + *this->w, *this->y , *this->z + *this->d), VGet(*this->x + *this->w, *this->y , *this->z - *this->d), GetColor(255, 0, 0));
	DrawLine3D(VGet(*this->x + *this->w, *this->y + *this->h, *this->z - *this->d), VGet(*this->x - *this->w, *this->y + *this->h, *this->z - *this->d), GetColor(255, 0, 0));
	DrawLine3D(VGet(*this->x + *this->w, *this->y + *this->h, *this->z - *this->d), VGet(*this->x + *this->w, *this->y , *this->z - *this->d), GetColor(255, 0, 0));
	*/
}

bool Collision::isHit(const Collision* other)const {
	return
		*this->x + *this->w > *other->x - *other->w &&
		*this->x - *this->w < *other->x + *other->w	&&
		*this->z + *this->d > *other->z - *other->d &&
		*this->z - *this->d < *other->z + *other->d	&&
		*this->y + *this->h > *other->y - *other->h &&
		*this->y - *this->h < *other->y + *other->h;
}
