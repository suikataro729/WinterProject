
#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ApplicationGlobal.h"
#include "ModeGameOver.h"

bool ModeGameOver::Initialize() {
	if (!base::Initialize()) { return false; }

	alpha_cnt = 0;

	return true;
}

bool ModeGameOver::Process() {
	base::Process();
	int key = ApplicationMain::GetInstance()->GetKey();
	int trg = ApplicationMain::GetInstance()->GetTrg();

	// このモードより下のレイヤーはProcess()を呼ばない
	ModeServer::GetInstance()->SkipProcessUnderLayer();


	// ESCキー、Aボタン、Bボタンでメニューを閉じる
	if (((trg & PAD_INPUT_1 || trg & PAD_INPUT_2 || trg & PAD_INPUT_9) && alpha_cnt > 255) || alpha_cnt > 1500) {
		// このモードを削除する
		
		ModeServer::GetInstance()->Del(this);
	}

	alpha_cnt += 5;

	return true;
}

bool ModeGameOver::Render() {
	base::Render();
	int Font = GetFontSize();
	//DrawBox(0, 0, 1280, 720, GetColor(0, 0, 0),1);
	SetFontSize(128);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha_cnt);
	USEFUL.DrawPosString(640, 360 - 128, 0, GetColor(255, 0, 0), "死");
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	SetFontSize(Font);
	return true;
}

