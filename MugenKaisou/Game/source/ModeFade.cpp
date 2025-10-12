#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ApplicationGlobal.h"
#include "ModeFade.h"
#include "ModeTalk.h"

ModeFade::ModeFade(std::string type) {
	_fadeType = type;

	gGlobal._isFinishFadeIn = false;
	gGlobal._isFinishFadeOut = false;
	gGlobal._deleteFade = false;
}

ModeFade::~ModeFade() {
	// フェード用
	gGlobal._isFinishFadeIn = false;
	gGlobal._isFinishFadeOut = false;
	gGlobal._deleteFade = false;
}

bool ModeFade::Initialize() {
	if (!base::Initialize()) { return false; }

	_step = 0;
	if (_fadeType == "IN" || _fadeType == "INOUT") {
		_step = 0;
		// 黒からフェードインする
		gFade.ColorMask(0, 0, 0, 255);
	}
	else if (_fadeType == "OUT" || _fadeType == "OUTIN") {
		_step = 2;
	}

	gGlobal._isFinishFadeIn = false;
	gGlobal._isFinishFadeOut = false;

	return true;
}

bool ModeFade::Process() {
	base::Process();
	
	switch (_step) {
	case 0:
		// フェードイン開始
		gFade.ColorFadeIn(120);
		_step++;
		break;
	case 1:
		if (gFade.IsColorFade() == 0) {
			// フェードイン終了
			gGlobal._isFinishFadeIn = true;
			if (_fadeType == "IN" || _fadeType == "OUTIN") {
				// このモードを削除する
				ModeServer::GetInstance()->Del(this);
			}
			else {
				_step = 2;
			}
		}
		break;
	case 2:
		// フェードアウト開始
		gFade.ColorFadeOut(0, 0, 0, 120);
		_step++;
		break;
	case 3:
		if (gFade.IsColorFade() == 0) {
			// フェードアウト終了
			gGlobal._isFinishFadeOut = true;
			if (_fadeType == "OUT" || _fadeType == "INOUT") {
				//if (!TalkFlg[15] && keyRoom == 6212) {
				//	TalkFlg[15] = TRUE;
				//	ModeTalk* modetalk = new ModeTalk("res/jsonfile/TextData/calculation2.json");
				//	// ModeGameより上のレイヤーにトークを登録する
				//	ModeServer::GetInstance()->Add(modetalk, 1000, "talk");
				//}
				//else
				{
					if (gGlobal._deleteFade) {
						// このモードを削除する
						gGlobal._isFinishFadeOut = false;
						ModeServer::GetInstance()->Del(this);
					}
				}
			}
			else {
				_step = 0;
			}
		}
		break;
	}

	// フェードインアウト処理
	gFade.ProcessColorFade();

	return true;
}

bool ModeFade::Render() {
	base::Render();

	// フェードインアウト描画
	gFade.DrawColorFade();

	return true;
}
