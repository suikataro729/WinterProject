#include "RoomServer.h"
#include "RoomEntrance.h"
#include "RoomPizza.h"
#include "RoomSlidePuzzle.h"
#include "RoomMuseum.h"
#include "RoomFan.h"
#include "RoomCalcLabyrinth.h"
#include "RoomGrave.h"
#include "RoomCalcHighLevel.h"
#include "RoomChristmas.h"

#include "../ApplicationGlobal.h"

RoomBase* gRoom;

RoomServer::RoomServer() {
	gRoom = NULL;
}

RoomServer::~RoomServer() {

}

void RoomServer::SetSpown(Chara& chara, Camera& cam) {
	gRoom->SetSpown(chara, cam);
}

void RoomServer::Reset() {
	gRoom->Reset();
}

void RoomServer::Process(Chara& chara, Camera& cam, VECTOR& v, VECTOR oldv) {
	gRoom->Process(chara, cam, v, oldv);
}

void RoomServer::CameraProcess(Camera& cam) {
	gRoom->CameraProcess(cam);
}

void RoomServer::Render(VECTOR vPos, bool viewColl) {
	gRoom->Render(vPos, viewColl);
}

void RoomServer::ChangeRoom(int keyRoom) {
	delete gRoom;

	switch (keyRoom) {
	// �G���g�����X(0000)
	case 0:
		// ���̕����ԍ��ݒ�
		gGlobal.keyNextRoom = 1109;
		gGlobal.keyLoseRoom = 1109;
		//�Q�[���J�E���g������
		gamecntdown = -999;		//���ԂȂ�
		gRoom = new RoomEntrance();
		break;
	// 101��ڂ̒a���������i���j(2126)
	case 2126:
		// ���̕����ԍ��ݒ�
		gGlobal.keyNextRoom = 1225;
		gGlobal.keyLoseRoom = 1225;
		//�Q�[���J�E���g������
		gamecntdown = 6000;		//999�b
		gRoom = new RoomGrave();
		break;
	// �s�U����(6212)
	case 6212:
		// ���̕����ԍ��ݒ�
		gGlobal.keyNextRoom = 4226;
		gGlobal.keyLoseRoom = 1114;
		//�Q�[���J�E���g������
		gamecntdown = 5940;		//99�b
		gRoom = new RoomPizza();
		break;
	// �X���C�h����(1109, 4226)
	case 1109:
		// ���̕����ԍ��ݒ�
		gGlobal.keyNextRoom = 311;
		gGlobal.keyLoseRoom = 1114;
		//�Q�[���J�E���g������
		gamecntdown = 6600;		//110�b
		gRoom = new RoomSlidePuzzle();
		break;
	case 4226:
		// ���̕����ԍ��ݒ�
		gGlobal.keyNextRoom = 1114;
		gGlobal.keyLoseRoom = 1114;
		//�Q�[���J�E���g������
		gamecntdown = 6600;		//99�b
		gRoom = new RoomSlidePuzzle();
		break;
	// �����ٕ���(1114)
	case 1114:
		// ���̕����ԍ��ݒ�
		gGlobal.keyNextRoom = 223;
		gGlobal.keyLoseRoom = 1225;
		//�Q�[���J�E���g������
		gamecntdown = 9000;		//99�b
		gRoom = new RoomMuseum();
		break;
	// �v���O��������(0223)
	case 223:
		// ���̕����ԍ��ݒ�
		gGlobal.keyNextRoom = 3215;
		gGlobal.keyLoseRoom = 1225;
		//�Q�[���J�E���g������
		gamecntdown = 6000;		//999�b
		gRoom = new RoomFan();
		break;
	// �v�Z�i���{�j����(0311)
	case 311:
		// ���̕����ԍ��ݒ�
		gGlobal.keyNextRoom = 6212;
		gGlobal.keyLoseRoom = 1114;
		//�Q�[���J�E���g������
		gamecntdown = 900;		//15�b
		gRoom = new RoomCalcLabyrinth();
		break;
	// �v�Z�i���{�j�����㋉(3215)
	case 3215:
		// ���̕����ԍ��ݒ�
		gGlobal.keyNextRoom = 1225;
		gGlobal.keyLoseRoom = 1225;
		//�Q�[���J�E���g������
		gamecntdown = 6000;		//999�b
		gRoom = new RoomCalcHighLevel();
		break;
	// �N���X�}�X����(1225)
	case 1225:
		// ���̕����ԍ��ݒ�
		gGlobal.keyNextRoom = 0;
		gGlobal.keyLoseRoom = 0;
		//�Q�[���J�E���g������
		gamecntdown = 4000;		//999�b
		gRoom = new RoomChristmas();
		break;
	}
}
