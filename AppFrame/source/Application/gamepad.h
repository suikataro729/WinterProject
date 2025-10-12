#pragma once

#include	"DxLib.h"

#define	XINPUT_BUTTON_MAX	(16)	// XInput�̃{�^����
#define	PAD_MAX				(4)		// �ڑ�PAD�ő吔
#define	KEY_CNT_MAX			(256)	// �L�[�̍ő吔

class GamePad {
public:
	GamePad();				// �R���X�g���N�^
	virtual ~GamePad();		// �f�X�g���N�^

	virtual void Input();	// ���͍X�V
public:
	// �Q�[���p�b�h1�p�̏ꍇ
	XINPUT_STATE xinput_pad;

	// XInput�p
	int gXKey[XINPUT_BUTTON_MAX];
	int gXTrg[XINPUT_BUTTON_MAX];
	int gXRel[XINPUT_BUTTON_MAX];
};

class GameKeyMouse {
public:
	GameKeyMouse();
	virtual ~GameKeyMouse();

	virtual void Input();
public:
	char KeyBuf[KEY_CNT_MAX];
	int gKKey[KEY_CNT_MAX];
	int gKTrg[KEY_CNT_MAX];
	int gKRel[KEY_CNT_MAX];
};

extern GamePad gPad[PAD_MAX];
extern GameKeyMouse gKeyMouse;
