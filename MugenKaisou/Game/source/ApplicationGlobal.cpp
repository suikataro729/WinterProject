
#include "AppFrame.h"
#include "ApplicationGlobal.h"

// ����
ApplicationGlobal		gGlobal;
RoomData				rData;

ApplicationGlobal::ApplicationGlobal() {
}

ApplicationGlobal::~ApplicationGlobal() {
}


bool ApplicationGlobal::Init() {
	_cgCursor = LoadGraph("res/cursor.png");

	// �����ԍ��p
	keyNowRoom = 0;
	keyNextRoom = 0;
	keyLoseRoom = 0;

	// �t�F�[�h�p
	_isFinishFadeIn = false;
	_isFinishFadeOut = false;
	_deleteFade = false;

	return true;
}

// �s�U�o���t���O�i�E���Ńs�U�𒍕�������ATURE�j
bool gPizza = 0;

// �L�����N�^�̎��S�t���O
bool gChara_Dead = 0;

int gCode[20];

// �������u���b�N���
int gMovemap_num = 0;	//������map�ԍ�
int gMoverot = 0;		//����������  1:�E 2:�� 3;�� 4;��

// �h�A�؂�ւ��p
int gChangeDoor;

// �����ԍ�
int keyRoom = 0;

int gamecntdown;
bool respown_flg;

//�v���y�������֘A
float FanSpeed = 0.15f;

//���f�[�^
int SaveRoot[] = { 0,0,0,0,0,0,0,0,0,0 };
//int SaveRoot[] = { 1,1,1,1,1,1,1,1,1,1 };

int RoomClear[] = { 0,0,0,0,0,0,0,0,0,0 };		//0:�N���A���ĂȂ��A1:�N���A�ς�
//int RoomClear[] = { 1,1,1,1,1,1,1,1,1,1 };		//0:�N���A���ĂȂ��A1:�N���A�ς�

//0:slidepuzzle1 1:slidepuzzle5 2:slidepuzzle3 3:timeflag 4:respawn 5:pizza2 6:pizza4 7:meteorite2 8:meteorite3 9:calculation2 10:entrance4 
// 11:entrance5 12:christmas 13:museum1 14:pizza2 15:meteorite4 16:entranceend 17:calculationB3 18:grave4 19:meteorite1 20:grave1 21:
bool TalkFlg[] = { FALSE };

bool FullScreenFlg;

//0: �����l 1:���̕����̂܂� 2:��������
int chengeRoom;