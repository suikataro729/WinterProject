#include "AppFrame.h"
#include "BeltConveyor.h"

BeltConveyor::BeltConveyor() {

}

BeltConveyor::~BeltConveyor() {

}

void BeltConveyor::Init() {
	
}

void BeltConveyor::Process() {

}

void BeltConveyor::MovePos(VECTOR &vCharaPos, int boxType, int MoveSpeed) {
	VECTOR v;
	switch (boxType) {
	case 2:
		// x•ûŒü‚Ö
		v = VGet(MoveSpeed, 0, 0);
		break;
	case 3:
		// -x•ûŒü‚Ö
		v = VGet(-MoveSpeed, 0, 0);
		break;
	case 4:
		// z•ûŒü‚Ö
		v = VGet(0, 0, MoveSpeed);
		break;
	case 5:
		// -z•ûŒü‚Ö
		v = VGet(0, 0, -MoveSpeed);
		break;
	}
	vCharaPos = VAdd(vCharaPos, v);
}

void BeltConveyor::Render() {
	
}
