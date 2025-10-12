
#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ApplicationGlobal.h"
#include "ModeTitle.h"
#include "ModeGame.h"
#include "ModeFade.h"

bool ModeTitle::Initialize() {
	if (!base::Initialize()) { return false; }

	cg_bg[0] = LoadGraph("res/UI/Title/cg_title.png");
	cg_bg[1] = LoadGraph("res/UI/Title/cg_title_book.png");
	cg_bg[2] = LoadGraph("res/UI/Title/cg_title_number.png");
	cg_bg[3] = LoadGraph("res/UI/Title/cg_title_press.png");
	cg_bg[4] = LoadGraph("res/UI/Title/cg_title_undertitle.png");
	cg_bg[5] = LoadGraph("res/UI/Title/cg_title_title.png");

	bookY = 0;
	bookSaveY = 0.5;
	buttonSaveY = 1;

	flgGameStart = true;

	return true;
}

bool ModeTitle::Process() {
	base::Process();
	int key = ApplicationMain::GetInstance()->GetKey();
	int trg = ApplicationMain::GetInstance()->GetTrg();

	// このモードより下のレイヤーはProcess()を呼ばない
	ModeServer::GetInstance()->SkipProcessUnderLayer();

	if (GetModeCount() % 3 == 0)
	{
		// bookYを等速で10と-10の間で動かす
		if (bookY >= 20 || bookY <= -10) {
			bookSaveY = -bookSaveY;
		}
		bookY += bookSaveY;
	}

	// ESCキー、Aボタン、Bボタンでメニューを閉じる
	if (trg & PAD_INPUT_1 || trg & PAD_INPUT_2 || trg & PAD_INPUT_9) {
		// フェードインアウト
		ModeServer::GetInstance()->Add(new ModeFade("OUTIN"), 999, "fade");
	}

	if (gGlobal._isFinishFadeOut) {
		// このモードを削除する
		ModeServer::GetInstance()->Del(this);
	}

	return true;
}

bool ModeTitle::Render() {
	base::Render();
	int Font = GetFontSize();

	//背景
	DrawGraph(0, 0, cg_bg[0], TRUE);

	//本
	DrawGraph(0, bookY, cg_bg[1], TRUE);

	//文字
	DrawGraph(0, 0, cg_bg[2], TRUE);


	//ボタン
	DrawGraph(0, 0, cg_bg[3], TRUE);

	//ゆらゆら文字
	for (int i = 0; i < 1080; i++) {
		SetDrawArea(0, i, 1920, i + 1);
		DrawGraph(10 * sin(PI * 2 * ((int)(GetModeCount() / 3 + i / 0.8) % 200) / 200), 0, cg_bg[4], TRUE);
	}

	SetDrawArea(0, 0, 1920, 1080);

	DrawGraph(0, 0, cg_bg[5], TRUE);

	
	SetFontSize(Font);

	return true;
}

