
#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ApplicationGlobal.h"
#include "ModeEnding.h"
#include "ModeTalk.h"
#include "ModeTitle.h"
#include "ModeFade.h"
#include <cassert>
#include <string>


bool ModeEnding::Initialize() {
	if (!base::Initialize()) { return false; }

	std::string _cgNum;
	for (int i = 0; i < 10; i++) {
		_cgNum = "res/Window/_ScreenTransition/Num/num_" + std::to_string(i) + ".png";
		cgNum[i] = LoadGraph(_cgNum.c_str());
	}
	cgNumFrame = LoadGraph("res/Window/_ScreenTransition/Num/number_waku.png");
	cgBase[0] = LoadGraph("res/Window/_ScreenTransition/bg_1.png");
	cgBase[1] = LoadGraph("res/UI/enternum.png");
	cgBase[2] = LoadGraph("res/Window/_ScreenTransition/bg_0.png");

	cgNotNum = LoadGraph("res/Window/_ScreenTransition/Num/num.png");

	Keycnt = 0;
	codesave = -1;
	ResetGame = 0;
	SetMousePoint(1920 * 3 / 4, 1080 / 2);

	return true;
}
bool ModeEnding::Process() {
	base::Process();

	// このモードより下のレイヤーはProcess()を呼ばない
	ModeServer::GetInstance()->SkipProcessUnderLayer();
	
	if (ResetGame) {
		for (int i = 0; i < 10; i++) {
			SaveRoot[i] = 0;
			RoomClear[i] = 0;
		}
		for (int i = 0; i < 99; i++) {
			TalkFlg[i] = 0;
		}
		// トークフラグ解放
		for (int i = 0; i < 10; i++) {
			TalkFlg[i] = FALSE;
		}
		//ゲームを再起動させるModeGame
		ModeServer::GetInstance()->Add(new ModeFade("IN"), 998, "fade");
		ModeServer::GetInstance()->Add(new ModeTitle(), 997, "title");
		ModeServer::GetInstance()->Del(this);
	}

	{
		// キーの入力、トリガ入力を得る
		int keyold = gKey;
		gKey = GetMouseInput();		// キー入力を取得
		// キーのトリガ情報生成（押した瞬間しか反応しないキー情報）
		gTrg = (gKey ^ keyold) & gKey;
		gRel = (gKey ^ keyold) & ~gKey;
	}

	//石板
	{
			if (CheckHitKeyAll(DX_CHECKINPUT_KEY)) {
				if (Keyflg) {
					int Keynum = -1;
					if (CheckHitKey(KEY_INPUT_0)) { Keynum = 0; }
					if (CheckHitKey(KEY_INPUT_1)) { Keynum = 1; }
					if (CheckHitKey(KEY_INPUT_2)) { Keynum = 2; }
					if (CheckHitKey(KEY_INPUT_3)) { Keynum = 3; }
					if (CheckHitKey(KEY_INPUT_4)) { Keynum = 4; }
					if (CheckHitKey(KEY_INPUT_5)) { Keynum = 5; }
					if (CheckHitKey(KEY_INPUT_6)) { Keynum = 6; }
					if (CheckHitKey(KEY_INPUT_7)) { Keynum = 7; }
					if (CheckHitKey(KEY_INPUT_8)) { Keynum = 8; }
					if (CheckHitKey(KEY_INPUT_9)) { Keynum = 9; }
					if ((_Keynum[Keycnt] != Keynum) && Keynum != -1) {
						_Keynum[Keycnt] = Keynum;
						Keycnt++;
					}
					if (Keycnt == 5 || codesave != -1) {
						for (int i = 0; i < 5; i++) {
							_Keynum[i] = -1;
						}
						codesave = -1;
						Keycnt = 0;
					}
					Keyflg = 0;
				}
			}
			else
			{
				Keyflg = 1;
			}

			int buttonX = 1920 * 3 / 4;
			int buttonY = 1080 * 6 / 8;
			if (gKeyMouse.gKTrg[KEY_INPUT_RETURN])
			{
				if (gKeyMouse.gKTrg[KEY_INPUT_RETURN])
				{
					int Keycode = 0;
					bool KeyResetflg = 0;
					for (int i = 0; i < 4; i++) {
						if (_Keynum[i] != -1) { Keycode += _Keynum[i] * pow(10, 3 - i); }
					}
					if (!KeyResetflg) {
						for (int i = 0; i < 5; i++) {
							_Keynum[i] = -1;
						}
						Keycnt = 0;
					}
					if (Keycode == 1225) {
						ModeTalk* modetalk = new ModeTalk("res/jsonfile/TextData/end1225.json");
						// ModeGameより上のレイヤーにトークを登録する
						ModeServer::GetInstance()->Add(modetalk, 200, "talk");
						ResetGame = 1;
					}
					else if (Keycode == 5226)
					{
						ModeTalk* modetalk = new ModeTalk("res/jsonfile/TextData/end5226.json");
						// ModeGameより上のレイヤーにトークを登録する
						ModeServer::GetInstance()->Add(modetalk, 200, "talk");
						ResetGame = 1;
					}
					else if (Keycode == 6225)
					{
						ModeTalk* modetalk = new ModeTalk("res/jsonfile/TextData/end6225.json");
						// ModeGameより上のレイヤーにトークを登録する
						ModeServer::GetInstance()->Add(modetalk, 200, "talk");
						ResetGame = 1;
					}
				}
			}
		//部屋ごとの処理
	}

	return true;
}

bool ModeEnding::Render() {
	base::Render();
	SetDrawArea(1920 / 4, 0, 1920 * 3 / 4, 1080);
	//石板
	{
			DrawGraph(386, 144, cgBase[1], TRUE);
			int Draw_Keynum[4];
			for (int i = 0; i < 4; i++) {
				if (0 < _Keynum[i]) { Draw_Keynum[i] = _Keynum[i]; }
			}
			int Font = GetFontSize();
			SetFontSize(64);
			for (int i = 0; i < 4; i++) {
				int n = 0;
				int DrawNum = cgNotNum;
				n = _Keynum[i];
				if (n != -1) {
					DrawNum = cgNum[n];
				}
				DrawGraph(660 + i * 153, 403, cgNumFrame, TRUE);
				DrawGraph(660 + i * 153, 403, DrawNum, TRUE);
			}
			SetFontSize(Font);
	}
	SetDrawArea(0, 0, 1920, 1080);
	return true;
}

