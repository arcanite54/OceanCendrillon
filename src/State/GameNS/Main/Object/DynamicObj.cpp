#include "DynamicObj.h"

void DynamicObj::muteki(int n) {
	if (mutekiFlag)mutekicount++;
	if (mutekicount == n) {
		mutekicount = 0;
		mutekiFlag = false;
	}
}

void DynamicObj::attack() {
	for (auto itr = atk_obj.begin(); itr != atk_obj.end();) {
		(*itr)->update();
		(*itr)->draw();
		if ((*itr)->isDelete()) {
			delete *itr;
			itr = atk_obj.erase(itr);
			continue;
		}
		++itr;
	}
}
void DynamicObj::flashing(int* handle) {
	// ‚R‚cƒ‚ƒfƒ‹‚Ì•s“§–¾“x‚ð50%‚É‚·‚é
	if (mutekiFlag)MV1SetOpacityRate(*handle, 1.0f - ((mutekicount / 10) % 2)*0.5f);
	else MV1SetOpacityRate(*handle, 1.0f);
}

void DynamicObj::set_direction(int* handle) {
	if (vx != 0.0f || vz != 0.0f)now_direction = atan2(-vx, -vz);
	MV1SetRotationXYZ(*handle, VGet(0.0f, now_direction, 0.0f));
}

bool DynamicObj::canPass(float _x,float _z) {
	return !(-13.0f < _x && _x < 13.0f &&
		-13.0f < _z && _z < 13.0f);
}