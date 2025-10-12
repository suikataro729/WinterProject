#pragma once

#include	"DxLib.h"

#define	XINPUT_BUTTON_MAX	(16)	// XInputのボタン数
#define	PAD_MAX				(4)		// 接続PAD最大数
#define	KEY_CNT_MAX			(256)	// キーの最大数

class GamePad {
public:
	GamePad();				// コンストラクタ
	virtual ~GamePad();		// デストラクタ

	virtual void Input();	// 入力更新
public:
	// ゲームパッド1用の場合
	XINPUT_STATE xinput_pad;

	// XInput用
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
