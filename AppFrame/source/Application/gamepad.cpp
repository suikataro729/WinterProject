#include	"gamepad.h"

// 実体
GamePad gPad[PAD_MAX];
GameKeyMouse gKeyMouse;

GamePad::GamePad()
{
	for (int i = 0; i < XINPUT_BUTTON_MAX; i++)
	{
		gXKey[i] = 0;
		gXTrg[i] = 0;
		gXRel[i] = 0;
	}
}

GamePad::~GamePad()
{

}

void GamePad::Input()
{
	// XInputでの入力値取得
	int Xkeyold[XINPUT_BUTTON_MAX];
	for (int i = 0; i < XINPUT_BUTTON_MAX; i++)
	{
		Xkeyold[i] = xinput_pad.Buttons[i];
	}

	GetJoypadXInputState(DX_INPUT_PAD1, &xinput_pad);			// pad1の入力値を取得

	for (int i = 0; i < XINPUT_BUTTON_MAX; i++)
	{
		// XInputでのキー入力、トリガ入力、リリース入力を得る
		gXKey[i] = xinput_pad.Buttons[i];
		gXTrg[i] = (gXKey[i] ^ Xkeyold[i]) & gXKey[i];
		gXRel[i] = (gXKey[i] ^ Xkeyold[i]) & ~gXKey[i];
	}
}

GameKeyMouse::GameKeyMouse()
{
	for (int i = 0; i < KEY_CNT_MAX; i++)
	{
		gKKey[i] = 0;
		gKTrg[i] = 0;
		gKRel[i] = 0;
	}
}

GameKeyMouse::~GameKeyMouse()
{

}

void GameKeyMouse::Input()
{
	int Kkeyold[KEY_CNT_MAX];
	for (int i = 0; i < KEY_CNT_MAX; i++)
	{
		Kkeyold[i] = KeyBuf[i];
	}

	GetHitKeyStateAll(KeyBuf);		// 全てのキーの押下状態を取得

	for (int i = 0; i < KEY_CNT_MAX; i++)
	{
		gKKey[i] = KeyBuf[i];
		gKTrg[i] = (gKKey[i] ^ Kkeyold[i]) & gKKey[i];
		gKRel[i] = (gKKey[i] ^ Kkeyold[i]) & ~gKKey[i];
	}
}
