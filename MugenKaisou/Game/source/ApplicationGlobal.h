#include "appframe.h"
#include "Room/RoomData.h"
#include "Fade.h"

class ApplicationGlobal
{
public:
	ApplicationGlobal();
	virtual ~ApplicationGlobal();

	bool Init();
public:
	int _cgCursor;

	// �����ԍ��p
	int keyNowRoom;
	int keyNextRoom;
	int keyLoseRoom;

	// �t�F�[�h�p
	bool _isFinishFadeIn, _isFinishFadeOut;
	bool _deleteFade;
};

// �����i�}�b�v�j�f�[�^
extern RoomData rData;

// �s�U�o���t���O�i�E���Ńs�U�𒍕�������ATURE�j
extern bool gPizza;

// �L�����N�^�̎��S�t���O
extern bool gChara_Dead;

extern int gCode[20];

//�v���y�������֘A
extern float FanSpeed;

// �������u���b�N���
extern int gMovemap_num;	//������map�ԍ�
extern int gMoverot;		//����������  1:�E 2:�� 3;�� 4;��

// �h�A�؂�ւ��p
extern int gChangeDoor;		// 0:�ʏ�h�A, 1:�B���h�A

// �����ԍ�
extern int keyRoom;

// ���̃\�[�X��gGlobal���g����悤��
extern ApplicationGlobal		gGlobal;

// �c�莞��
extern int gamecntdown;

// ���X�|�[���p�t���O
extern bool respown_flg;

extern int SaveRoot[10];		//0:�ʂ��Ă��Ȃ��A1:�ʉߍς�

extern int RoomClear[10];		//0:�N���A���ĂȂ��A1:�N���A�ς�

extern bool TalkFlg[99];

extern bool FullScreenFlg;

extern int chengeRoom;