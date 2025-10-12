
#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ApplicationGlobal.h"
#include "ModeRoomNumber.h"
#include "ModeTalk.h"
#include "ModeFade.h"

ModeRoomNumber::ModeRoomNumber(int _keyRoom, int _next_keyRoom, bool clear) {
	save_keyRoom = _keyRoom;
	save_clear = clear;
	save_next_keyRoom = _next_keyRoom;
}

ModeRoomNumber::~ModeRoomNumber() {
	//解放処理
	DeleteGraph(cgbg);
	DeleteGraph(cgCover[0]);
	DeleteGraph(cgCover[1]);
	DeleteGraph(cgAreaMapUI);
	for (int i = 0; i < 4; i++) {
		DeleteGraph(cgAreaMapEmpty[i]);
	}
	for (int i = 0; i < 10; i++) {
		DeleteGraph(cgAreaMapNum[0][i]);
		DeleteGraph(cgAreaMapNum[1][i]);
	}
}

bool ModeRoomNumber::Initialize() {
	if (!base::Initialize()) { return false; }
	if (save_next_keyRoom == 1109 && !TalkFlg[0]) {
		TalkFlg[0] = TRUE;
		ModeTalk* modetalk = new ModeTalk("res/jsonfile/TextData/slidepuzzle1.json");
		// ModeGameより上のレイヤーにトークを登録する
		ModeServer::GetInstance()->Add(modetalk, 200, "talk");
	}

	if (gGlobal._isFinishFadeOut) {
		// フェードモードの削除
		gGlobal._deleteFade = true;
	}

	alpha_cnt = 0;
	gamecnt = 0;

	cgbg = LoadGraph("res/UI/ScreenTransition/bg.png");
	cgCover[0] = LoadGraph("res/UI/ScreenTransition/bg0.png");
	cgCover[1] = LoadGraph("res/UI/ScreenTransition/bg1.png");

	cgAreaMapUI = LoadGraph("res/UI/ScreenTransition/AreaMap/UI.png");
	cgAreaMapEmpty[0] = LoadGraph("res/UI/ScreenTransition/AreaMap/empty/entrance.png");
	cgAreaMapEmpty[1] = LoadGraph("res/UI/ScreenTransition/AreaMap/empty/number.png");
	cgAreaMapEmpty[2] = LoadGraph("res/UI/ScreenTransition/AreaMap/empty/theChristmas.png");
	cgAreaMapEmpty[3] = LoadGraph("res/UI/ScreenTransition/AreaMap/empty/udenodan.png");

	cgAreaMapNum[0][0] = LoadGraph("res/UI/ScreenTransition/AreaMap/num/0223.png");
	cgAreaMapNum[0][1] = LoadGraph("res/UI/ScreenTransition/AreaMap/num/0311.png");
	cgAreaMapNum[0][2] = LoadGraph("res/UI/ScreenTransition/AreaMap/num/1109.png");
	cgAreaMapNum[0][3] = LoadGraph("res/UI/ScreenTransition/AreaMap/num/1114.png");
	cgAreaMapNum[0][4] = LoadGraph("res/UI/ScreenTransition/AreaMap/num/entrance.png");
	cgAreaMapNum[0][5] = LoadGraph("res/UI/ScreenTransition/AreaMap/num/3215.png");
	cgAreaMapNum[0][6] = LoadGraph("res/UI/ScreenTransition/AreaMap/num/birthday.png");
	cgAreaMapNum[0][7] = LoadGraph("res/UI/ScreenTransition/AreaMap/num/beforetheday.png");
	cgAreaMapNum[0][8] = LoadGraph("res/UI/ScreenTransition/AreaMap/num/6212.png");
	cgAreaMapNum[0][9] = LoadGraph("res/UI/ScreenTransition/AreaMap/num/theChristmas.png");

	cgAreaMapNum[1][0] = LoadGraph("res/UI/ScreenTransition/AreaMap/num_y/0223.png");
	cgAreaMapNum[1][1] = LoadGraph("res/UI/ScreenTransition/AreaMap/num_y/0311.png");
	cgAreaMapNum[1][2] = LoadGraph("res/UI/ScreenTransition/AreaMap/num_y/1109.png");
	cgAreaMapNum[1][3] = LoadGraph("res/UI/ScreenTransition/AreaMap/num_y/1114.png");
	cgAreaMapNum[1][4] = LoadGraph("res/UI/ScreenTransition/AreaMap/num_y/entrance.png");
	cgAreaMapNum[1][5] = LoadGraph("res/UI/ScreenTransition/AreaMap/num_y/3215.png");
	cgAreaMapNum[1][6] = LoadGraph("res/UI/ScreenTransition/AreaMap/num_y/birthday.png");
	cgAreaMapNum[1][7] = LoadGraph("res/UI/ScreenTransition/AreaMap/num_y/beforetheday.png");
	cgAreaMapNum[1][8] = LoadGraph("res/UI/ScreenTransition/AreaMap/num_y/6212.png");
	cgAreaMapNum[1][9] = LoadGraph("res/UI/ScreenTransition/AreaMap/num_y/theChristmas.png");

	int TBL[] = { 4,2,1,8,7,3,0,5,6,9 };
	for (int i = 0; i < 10; i++) {
		if (SaveRoot[i] == 0) {
			if (TBL[i] == 4) {
				cgAreaMapNum[0][TBL[i]] = cgAreaMapEmpty[0];
				continue;
			}
			if (TBL[i] == 7 || TBL[i] == 6) {
				cgAreaMapNum[0][TBL[i]] = cgAreaMapEmpty[3];
				continue;
			}
			if (TBL[i] == 9) {
				cgAreaMapNum[0][TBL[i]] = cgAreaMapEmpty[2];
				continue;
			}

			cgAreaMapNum[0][TBL[i]] = cgAreaMapEmpty[1];
		}
	}
	switch (save_next_keyRoom)
	{
	case 223:	cgAreaMapNum[0][0] = cgAreaMapNum[1][0]; break;
	case 311:	cgAreaMapNum[0][1] = cgAreaMapNum[1][1]; break;
	case 1109:	cgAreaMapNum[0][2] = cgAreaMapNum[1][2]; break;
	case 1114:	cgAreaMapNum[0][3] = cgAreaMapNum[1][3]; break;
	case 0:		cgAreaMapNum[0][4] = cgAreaMapNum[1][4]; break;
	case 3215:  cgAreaMapNum[0][5] = cgAreaMapNum[1][5]; break;
	case 2126:  cgAreaMapNum[0][6] = cgAreaMapNum[1][6]; break;
	case 4226:  cgAreaMapNum[0][7] = cgAreaMapNum[1][7]; break;
	case 6212:  cgAreaMapNum[0][8] = cgAreaMapNum[1][8]; break;
	case 1225:  cgAreaMapNum[0][9] = cgAreaMapNum[1][9]; break;
	}


	cgNumber[0] = LoadGraph("res/UI/ScreenTransition/NextMap/0223.png");
	cgNumber[1] = LoadGraph("res/UI/ScreenTransition/NextMap/0311.png");
	cgNumber[2] = LoadGraph("res/UI/ScreenTransition/NextMap/1109.png");
	cgNumber[3] = LoadGraph("res/UI/ScreenTransition/NextMap/1114.png");
	cgNumber[4] = LoadGraph("res/UI/ScreenTransition/NextMap/entrance.png");
	cgNumber[5] = LoadGraph("res/UI/ScreenTransition/NextMap/3215.png");
	cgNumber[6] = LoadGraph("res/UI/ScreenTransition/NextMap/birthday.png");
	cgNumber[7] = LoadGraph("res/UI/ScreenTransition/NextMap/beforetheday.png");
	cgNumber[8] = LoadGraph("res/UI/ScreenTransition/NextMap/6212.png");
	cgNumber[9] = LoadGraph("res/UI/ScreenTransition/NextMap/theChristmas.png");

	cgDialyParts[0] = LoadGraph("res/UI/ScreenTransition/NextMap/NEXT.png");
	cgDialyParts[1] = LoadGraph("res/UI/ScreenTransition/NextMap/UI_arrow.png");

	switch (save_next_keyRoom)
	{
	case 223: _cgNum = cgNumber[0]; break;
	case 311: _cgNum = cgNumber[1]; break;
	case 1109: _cgNum = cgNumber[2]; break;
	case 1114: _cgNum = cgNumber[3]; break;
	case 0: _cgNum = cgNumber[4]; break;
	case 3215: _cgNum = cgNumber[5]; break;
	case 2126: _cgNum = cgNumber[6]; break;
	case 4226: _cgNum = cgNumber[7]; break;
	case 6212: _cgNum = cgNumber[8]; break;
	case 1225: _cgNum = cgNumber[9]; break;
	}

	_cgDialy = -1;
	//0の部屋の日記はなし
	if (save_keyRoom == 0) { save_clear = false; }
	//クリアしていなければ読み込まない
	if(!save_clear){ return true; }

	cgDialy[0] = LoadGraph("res/UI/ScreenTransition/dialy/0223.png");
	cgDialy[1] = LoadGraph("res/UI/ScreenTransition/dialy/0311.png");
	cgDialy[2] = LoadGraph("res/UI/ScreenTransition/dialy/1109.png");
	cgDialy[3] = LoadGraph("res/UI/ScreenTransition/dialy/1114.png");
	cgDialy[4] = LoadGraph("res/UI/ScreenTransition/dialy/1125.png");
	cgDialy[5] = LoadGraph("res/UI/ScreenTransition/dialy/2126.png");
	cgDialy[6] = LoadGraph("res/UI/ScreenTransition/dialy/3215.png");
	cgDialy[7] = LoadGraph("res/UI/ScreenTransition/dialy/4226.png");
	cgDialy[8] = LoadGraph("res/UI/ScreenTransition/dialy/5226.png");
	cgDialy[9] = LoadGraph("res/UI/ScreenTransition/dialy/6212.png");
	cgDialy[10] = LoadGraph("res/UI/ScreenTransition/dialy/6225.png");

	switch (save_keyRoom)
	{
	case 223: _cgDialy = cgDialy[0]; break;
	case 311: _cgDialy = cgDialy[1]; break;
	case 1109: _cgDialy = cgDialy[2]; break;
	case 1114: _cgDialy = cgDialy[3]; break;
	case 1225: _cgDialy = cgDialy[4]; break;
	case 2126: _cgDialy = cgDialy[5]; break;
	case 3215: _cgDialy = cgDialy[6]; break;
	case 4226: _cgDialy = cgDialy[7]; break;
	case 5226: _cgDialy = cgDialy[8]; break;
	case 6212: _cgDialy = cgDialy[9]; break;
	case 6225: _cgDialy = cgDialy[10]; break;
	}

	return true;
}

bool ModeRoomNumber::Process() {
	base::Process();
	int key = ApplicationMain::GetInstance()->GetKey();
	int trg = ApplicationMain::GetInstance()->GetTrg();

	// このモードより下のレイヤーはProcess()を呼ばない
	ModeServer::GetInstance()->SkipProcessUnderLayer();

	if (RoomClear[1] == 1 && !TalkFlg[1]) {
		TalkFlg[1] = TRUE;
		ModeTalk* modetalk = new ModeTalk("res/jsonfile/TextData/slidepuzzle5.json");
		// ModeGameより上のレイヤーにトークを登録する
		ModeServer::GetInstance()->Add(modetalk, 200, "talk");
	}
	if (RoomClear[2] == 1 && !TalkFlg[9]) {
		TalkFlg[9] = TRUE;
		ModeTalk* modetalk = new ModeTalk("res/jsonfile/TextData/calculation2.json");
		// ModeGameより上のレイヤーにトークを登録する
		ModeServer::GetInstance()->Add(modetalk, 200, "talk");
	}
	if (RoomClear[3] == 1 && !TalkFlg[6]) {
		TalkFlg[6] = TRUE;
		ModeTalk* modetalk = new ModeTalk("res/jsonfile/TextData/pizza4.json");
		// ModeGameより上のレイヤーにトークを登録する
		ModeServer::GetInstance()->Add(modetalk, 200, "talk");
	}
	if (RoomClear[4] == 1 && !TalkFlg[8]) {
		TalkFlg[8] = TRUE;
		ModeTalk* modetalk = new ModeTalk("res/jsonfile/TextData/meteorite4.json");
		// ModeGameより上のレイヤーにトークを登録する
		ModeServer::GetInstance()->Add(modetalk, 200, "talk");
	}
	if (RoomClear[5] == 1 && !TalkFlg[15]) {
		TalkFlg[15] = TRUE;
		ModeTalk* modetalk = new ModeTalk("res/jsonfile/TextData/museum4.json");
		// ModeGameより上のレイヤーにトークを登録する
		ModeServer::GetInstance()->Add(modetalk, 200, "talk");
	}
	if (RoomClear[6] == 1 && !TalkFlg[21]) {
		TalkFlg[21] = TRUE;
		ModeTalk* modetalk = new ModeTalk("res/jsonfile/TextData/program3.json");
		// ModeGameより上のレイヤーにトークを登録する
		ModeServer::GetInstance()->Add(modetalk, 200, "talk");
	}
	if (RoomClear[7] == 1 && !TalkFlg[17]) {
		TalkFlg[17] = TRUE;
		ModeTalk* modetalk = new ModeTalk("res/jsonfile/TextData/calculationB3.json");
		// ModeGameより上のレイヤーにトークを登録する
		ModeServer::GetInstance()->Add(modetalk, 200, "talk");
	}
	if (RoomClear[8] == 1 && !TalkFlg[18]) {
		TalkFlg[18] = TRUE;
		ModeTalk* modetalk = new ModeTalk("res/jsonfile/TextData/grave4.json");
		// ModeGameより上のレイヤーにトークを登録する
		ModeServer::GetInstance()->Add(modetalk, 200, "talk");
	}

	// ESCキー、Aボタン、Bボタンでメニューを閉じる
	if (trg & PAD_INPUT_1 || trg & PAD_INPUT_2 || trg & PAD_INPUT_9)
	{
		if (save_clear) {
			save_clear = false;
		}
	}

	if (gamecnt == 300){
		// フェードインアウト
		ModeServer::GetInstance()->Add(new ModeFade("OUTIN"), 999, "fade");
	}

	if (gGlobal._isFinishFadeOut) {
		// このモードを削除する
		ModeServer::GetInstance()->Del(this);
	}

	if(!save_clear){ gamecnt++; }
	alpha_cnt = gamecnt * 255 / 60;
	//if(gamecnt > 240){ alpha_cnt = (60 - gamecnt % 60) * 255 / 60; }
	return true;
}

bool ModeRoomNumber::Render() {
	base::Render();
	SetDrawArea(0, 0, 1920, 1080);
	int Font = GetFontSize();

	// 透明度を設定
	SetFontSize(128);
	//SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha_cnt);

	// 画面描画
	DrawGraph(0, 0, cgbg, FALSE);

	if (save_clear) {

		DrawGraph(480, 0, _cgDialy, TRUE);
		DrawGraph(480, 0, cgCover[0], TRUE);
	}
	else
	{
		DrawGraph(480, 0, cgCover[1], TRUE);
		if (gamecnt % 300 < 120)
		{
			//マップ
			DrawGraph(744, 544, cgAreaMapUI, TRUE);

			bool NextStageFlg = false;
			DrawGraph(717, 733, cgAreaMapNum[0][4], TRUE);
			//線
			if (SaveRoot[0] == 1) {
				for (int i = -1; i < 2; i++) {
					DrawLine(717 + 118, 733 + 13 + i, 851, 733 + 13 + i, GetColor(255, 255, 255), 0);
				}
			}

			DrawGraph(851, 733, cgAreaMapNum[0][2], TRUE);
			//線
			if ((SaveRoot[1] == 1 && SaveRoot[2] == 1) || save_next_keyRoom == 311) {
				for (int i = -1; i < 2; i++) {
					DrawLine(851 + 54 + i, 733, 851 + 54 + i, 694 + 25, GetColor(255, 255, 255), 0);
				}
			}
			DrawGraph(851, 694, cgAreaMapNum[0][1], TRUE);
			//線
			if ((SaveRoot[2] == 1 && SaveRoot[3] == 1) || save_next_keyRoom == 6212) {
				for (int i = -1; i < 2; i++) {
					DrawLine(851 + 54 + i, 694, 851 + 54 + i, 655 + 25, GetColor(255, 255, 255), 0);
				}
			}

			DrawGraph(851, 655, cgAreaMapNum[0][8], TRUE);
			//線
			if ((SaveRoot[3] == 1 && SaveRoot[4] == 1) || save_next_keyRoom == 4226) {
				for (int i = -1; i < 2; i++) {
					DrawLine(851 + 54 + i, 655, 851 + 54 + i, 598 + 42, GetColor(255, 255, 255), 0);
				}
			}

			DrawGraph(851, 598, cgAreaMapNum[0][7], TRUE);

			////////////////////////////////////////////////////////////////////

			if (SaveRoot[1] == 1 && SaveRoot[5] == 1)
			{
				//横線前半
				if (RoomClear[3] == 1) {
					for (int i = -1; i < 2; i++) {
						DrawLine(851 + 108, 598 + 21 + i, 851 + 108 + 8, 598 + 21 + i, GetColor(255, 255, 255), 0);
					}

					for (int i = -1; i < 2; i++) {
						DrawLine(851 + 108 + 8 + i, 598 + 21, 851 + 108 + 8 + i, 733 + 13, GetColor(255, 255, 255), 0);
					}
				}
				else if (RoomClear[3] == 1)
				{
					for (int i = -1; i < 2; i++) {
						DrawLine(851 + 108, 655 + 13 + i, 851 + 108 + 8, 655 + 13 + i, GetColor(255, 255, 255), 0);
					}

					for (int i = -1; i < 2; i++) {
						DrawLine(851 + 108 + 8 + i, 655 + 21, 851 + 108 + 8 + i, 733 + 13, GetColor(255, 255, 255), 0);
					}
				}
				else if (RoomClear[2] == 1)
				{
					for (int i = -1; i < 2; i++) {
						DrawLine(851 + 108, 694 + 13 + i, 851 + 108 + 8, 694 + 13 + i, GetColor(255, 255, 255), 0);
					}

					for (int i = -1; i < 2; i++) {
						DrawLine(851 + 108 + 8 + i, 694 + 21, 851 + 108 + 8 + i, 733 + 13, GetColor(255, 255, 255), 0);
					}
				}
				else
				{
					for (int i = -1; i < 2; i++) {
						DrawLine(851 + 108, 733 + 13 + i, 851 + 108 + 8, 733 + 13 + i, GetColor(255, 255, 255), 0);
					}
				}
				//横線後半
				for (int i = -1; i < 2; i++) {
					DrawLine(851 + 108 + 8, 733 + 13 + i, 976, 733 + 13 + i, GetColor(255, 255, 255), 0);
				}
			}



			DrawGraph(976, 733, cgAreaMapNum[0][3], TRUE);
			//線
			if ((SaveRoot[5] == 1 && SaveRoot[6] == 1) || save_next_keyRoom == 223) {
				for (int i = -1; i < 2; i++) {
					DrawLine(976 + 54 + i, 733, 976 + 54 + i, 694 + 25, GetColor(255, 255, 255), 0);
				}
			}

			DrawGraph(976, 694, cgAreaMapNum[0][0], TRUE);
			//線
			if ((SaveRoot[6] == 1 && SaveRoot[7] == 1) || save_next_keyRoom == 3215) {
				for (int i = -1; i < 2; i++) {
					DrawLine(976 + 54 + i, 694, 976 + 54 + i, 655 + 25, GetColor(255, 255, 255), 0);
				}
			}

			DrawGraph(976, 655, cgAreaMapNum[0][5], TRUE);
			//線
			if ((SaveRoot[7] == 1 && SaveRoot[8] == 1) || save_next_keyRoom == 2126) {
				for (int i = -1; i < 2; i++) {
					DrawLine(976 + 54 + i, 655, 976 + 54 + i, 598 + 42, GetColor(255, 255, 255), 0);
				}
			}

			DrawGraph(976, 598, cgAreaMapNum[0][6], TRUE);
			

			if (SaveRoot[5] == 1 && SaveRoot[9] == 1)
			{
				//横線前半
				if (RoomClear[9] == 1) {
					for (int i = -1; i < 2; i++) {
						DrawLine(976 + 108, 598 + 21 + i, 976 + 108 + 8, 598 + 21 + i, GetColor(255, 255, 255), 0);
					}

					for (int i = -1; i < 2; i++) {
						DrawLine(976 + 108 + 8 + i, 598 + 21, 976 + 108 + 8 + i, 733 + 13, GetColor(255, 255, 255), 0);
					}
				}
				else if (RoomClear[8] == 1)
				{
					for (int i = -1; i < 2; i++) {
						DrawLine(976 + 108, 655 + 13 + i, 976 + 108 + 8, 655 + 13 + i, GetColor(255, 255, 255), 0);
					}

					for (int i = -1; i < 2; i++) {
						DrawLine(976 + 108 + 8 + i, 655 + 21, 976 + 108 + 8 + i, 733 + 13, GetColor(255, 255, 255), 0);
					}
				}
				else if (RoomClear[7] == 1)
				{
					for (int i = -1; i < 2; i++) {
						DrawLine(976 + 108, 694 + 13 + i, 976 + 108 + 8, 694 + 13 + i, GetColor(255, 255, 255), 0);
					}

					for (int i = -1; i < 2; i++) {
						DrawLine(976 + 108 + 8 + i, 694 + 21, 976 + 108 + 8 + i, 733 + 13, GetColor(255, 255, 255), 0);
					}
				}
				else
				{
					for (int i = -1; i < 2; i++) {
						DrawLine(976 + 108, 733 + 13 + i, 976 + 108 + 8, 733 + 13 + i, GetColor(255, 255, 255), 0);
					}
				}
				//横線後半
				for (int i = -1; i < 2; i++) {
					DrawLine(976 + 108 + 8, 733 + 13 + i, 1101, 733 + 13 + i, GetColor(255, 255, 255), 0);
				}
			}

			DrawGraph(1101, 733, cgAreaMapNum[0][9], TRUE);

		}
		else if (gamecnt % 300 < 180)
		{
			int j = (gamecnt % 300 - 120) / 20;
			for (int i = 0; i < j + 1; i++) {
				DrawGraph(813 + 18 * i, 560, cgDialyParts[1], TRUE);
			}
			DrawGraph(720, 556, cgDialyParts[0], TRUE);
		}
		else
		{
			for (int i = 0; i < 3; i++) {
				DrawGraph(813 + 18 * i, 560, cgDialyParts[1], TRUE);
			}
			DrawGraph(720, 556, cgDialyParts[0], TRUE);
			DrawGraph(678, 494, _cgNum, TRUE);
		}
	}



	// 透明度を元に戻す
	//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	SetFontSize(Font);
	//for (int i = 0; i < 10; i++)
	//{
	//	DrawFormatString(0, 100 + i * 15, GetColor(255, 255, 255), "save_keyRoom: %d", save_keyRoom);
	//	DrawFormatString(500, 100 + i * 15, GetColor(255, 255, 255), "save_next_keyRoom: %d", save_next_keyRoom);
	//}
	return true;
}

