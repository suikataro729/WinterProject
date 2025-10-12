#include "AppFrame.h"
#include "Door.h"

// ƒhƒA
Door::Door() {
	_flgVisible = true;
	_objTypeDoor = 7;
}

Door::~Door() {

}

void Door::SetVisible(bool flg) {
	_flgVisible = flg;
}

void Door::ChangeDoor(int ChangeDoor) {
	switch (ChangeDoor) {
	case 0:
		_objTypeDoor = 7;
		break;
	case 1:
		_objTypeDoor = 8;
		break;
	}
}

void Door::Clear() {
	if (gPad[0].gXTrg[XINPUT_BUTTON_A]) {
		
	}
}