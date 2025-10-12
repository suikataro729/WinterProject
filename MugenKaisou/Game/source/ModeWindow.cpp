
#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ApplicationGlobal.h"
#include "ModeWindow.h"
#include "ModeTalk.h"
#include <cassert>
#include <string>



bool ModeWindow::Initialize() {
	if (!base::Initialize()) { return false; }

	// jsonファイルの読み込み
	std::ifstream file("res/jsonfile/test.json");
	nlohmann::json json;
	file >> json;
	int i = 0;
	jsonMax = 0;

	// データを読み込む
	for (auto jsonfile : json)
	{
		jsonfile.at("draw").get_to(_jsonData[i].draw);
		jsonfile.at("draw_h").get_to(_jsonData[i].draw_h);
		jsonfile.at("code").get_to(_jsonData[i].code);
		gCode[i] = _jsonData[i].code;		//グローバルに格納
		jsonMax++;
		i++;
	}
	for (int n = 0; n < jsonMax; n++) {
		cgwindow[n] = LoadGraph(_jsonData[n].draw.c_str());
	}
	std::string _cgNum;
	for (i = 0; i < 10; i++) {
		_cgNum = "res/Window/_ScreenTransition/Num/num_" + std::to_string(i) + ".png";
		cgNum[i] = LoadGraph(_cgNum.c_str());
	}
	for (i = 0; i < 10; i++) {
		_cgNum = "res/Window/Labyrinth/" + std::to_string(i) + ".png";
		cgLabyNum[i] = LoadGraph(_cgNum.c_str());
	}
	cgCalc[0] = LoadGraph("res/Window/Labyrinth/plus.png");
	cgCalc[1] = LoadGraph("res/Window/Labyrinth/kakeru.png");
	cgAns[0] = LoadGraph("res/Window/Labyrinth/batu.png");
	cgAns[1] = LoadGraph("res/Window/Labyrinth/maru.png");

	cgNumFrame = LoadGraph("res/Window/_ScreenTransition/Num/number_waku.png");
	cgButton = LoadGraph("res/Window/Pizza/order.png");
	cgBase[0] = LoadGraph("res/Window/_ScreenTransition/bg_1.png");
	cgBase[1] = LoadGraph("res/Window/_ScreenTransition/bg_book.png");
	cgBase[2] = LoadGraph("res/Window/_ScreenTransition/bg_0.png");

	cgQP_Base[0] = LoadGraph("res/Window/LabyrinthPlus/back2.png");
	cgQP_Base[1] = LoadGraph("res/Window/LabyrinthPlus/special.png");

	cgNotNum = LoadGraph("res/Window/_ScreenTransition/Num/num.png");
	cgBlock[0] = LoadGraph("res/Window/SlidePuzle/Tile/0.png");
	cgBlock[1] = LoadGraph("res/Window/SlidePuzle/Tile/1.png");
	cgBlock[2] = LoadGraph("res/Window/SlidePuzle/Tile/2.png");
	cgBlock[3] = LoadGraph("res/Window/SlidePuzle/Tile/3.png");
	cgBlock[4] = LoadGraph("res/Window/SlidePuzle/Tile/4.png");
	cgBlock[5] = LoadGraph("res/Window/SlidePuzle/Tile/exit.png");

	cgBlock[20] = LoadGraph("res/Window/SlidePuzlePlus/0.png");
	cgBlock[21] = LoadGraph("res/Window/SlidePuzlePlus/3.png");
	cgBlock[22] = LoadGraph("res/Window/SlidePuzlePlus/2.png");
	cgBlock[24] = LoadGraph("res/Window/SlidePuzlePlus/1.png");
	cgBlock[25] = LoadGraph("res/Window/SlidePuzlePlus/4.png");
	cgBlock[19] = LoadGraph("res/Window/SlidePuzlePlus/exit.png");

	cglabel[0] = LoadGraph("res/Window/_ScreenTransition/label/0223.png");
	cglabel[1] = LoadGraph("res/Window/_ScreenTransition/label/0311.png");
	cglabel[2] = LoadGraph("res/Window/_ScreenTransition/label/1109.png");
	cglabel[3] = LoadGraph("res/Window/_ScreenTransition/label/1114.png");
	cglabel[4] = LoadGraph("res/Window/_ScreenTransition/label/2126.png");
	cglabel[5] = LoadGraph("res/Window/_ScreenTransition/label/3215.png");
	cglabel[6] = LoadGraph("res/Window/_ScreenTransition/label/4226.png");
	cglabel[7] = LoadGraph("res/Window/_ScreenTransition/label/5226.png");
	cglabel[8] = LoadGraph("res/Window/_ScreenTransition/label/6212.png");
	cglabel[9] = LoadGraph("res/Window/_ScreenTransition/label/6225.png");
	cglabel[10] = LoadGraph("res/Window/_ScreenTransition/label/enter_num.png");


	cgAreaMapUI[0] = LoadGraph("res/Window/_ScreenTransition/AreaMap/UI.png");
	cgAreaMapUI[1] = LoadGraph("res/Window/_ScreenTransition/board.png");
	cgAreaMapEmpty[0] = LoadGraph("res/Window/_ScreenTransition/AreaMap/empty/entrance.png");
	cgAreaMapEmpty[1] = LoadGraph("res/Window/_ScreenTransition/AreaMap/empty/number.png");
	cgAreaMapEmpty[2] = LoadGraph("res/Window/_ScreenTransition/AreaMap/empty/theChristmas.png");
	cgAreaMapEmpty[3] = LoadGraph("res/Window/_ScreenTransition/AreaMap/empty/udenodan.png");

	cgAreaMapNum[0][0] = LoadGraph("res/Window/_ScreenTransition/AreaMap/num/0223.png");
	cgAreaMapNum[0][1] = LoadGraph("res/Window/_ScreenTransition/AreaMap/num/0311.png");
	cgAreaMapNum[0][2] = LoadGraph("res/Window/_ScreenTransition/AreaMap/num/1109.png");
	cgAreaMapNum[0][3] = LoadGraph("res/Window/_ScreenTransition/AreaMap/num/1114.png");
	cgAreaMapNum[0][4] = LoadGraph("res/Window/_ScreenTransition/AreaMap/num/entrance.png");
	cgAreaMapNum[0][5] = LoadGraph("res/Window/_ScreenTransition/AreaMap/num/3215.png");
	cgAreaMapNum[0][6] = LoadGraph("res/Window/_ScreenTransition/AreaMap/num/birthday.png");
	cgAreaMapNum[0][7] = LoadGraph("res/Window/_ScreenTransition/AreaMap/num/beforetheday.png");
	cgAreaMapNum[0][8] = LoadGraph("res/Window/_ScreenTransition/AreaMap/num/6212.png");
	cgAreaMapNum[0][9] = LoadGraph("res/Window/_ScreenTransition/AreaMap/num/theChristmas.png");

	cgAreaMapNum[1][0] = LoadGraph("res/Window/_ScreenTransition/AreaMap/num_y/0223.png");
	cgAreaMapNum[1][1] = LoadGraph("res/Window/_ScreenTransition/AreaMap/num_y/0311.png");
	cgAreaMapNum[1][2] = LoadGraph("res/Window/_ScreenTransition/AreaMap/num_y/1109.png");
	cgAreaMapNum[1][3] = LoadGraph("res/Window/_ScreenTransition/AreaMap/num_y/1114.png");
	cgAreaMapNum[1][4] = LoadGraph("res/Window/_ScreenTransition/AreaMap/num_y/entrance.png");
	cgAreaMapNum[1][5] = LoadGraph("res/Window/_ScreenTransition/AreaMap/num_y/3215.png");
	cgAreaMapNum[1][6] = LoadGraph("res/Window/_ScreenTransition/AreaMap/num_y/birthday.png");
	cgAreaMapNum[1][7] = LoadGraph("res/Window/_ScreenTransition/AreaMap/num_y/beforetheday.png");
	cgAreaMapNum[1][8] = LoadGraph("res/Window/_ScreenTransition/AreaMap/num_y/6212.png");
	cgAreaMapNum[1][9] = LoadGraph("res/Window/_ScreenTransition/AreaMap/num_y/theChristmas.png");

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

	cgFullUI = LoadGraph("res/UI/UI_R.png");

	se[0] = LoadSoundMem("res/sound/SE/numberclick.wav");
	se[1] = LoadSoundMem("res/sound/SE/page.wav");
	se[2] = LoadSoundMem("res/sound/SE/slide.wav");
	se[3] = LoadSoundMem("res/sound/SE/propeller.wav");

	for (i = 0; i < 4; i++) {
		_Keynum[i] = -1;
	}

	//_codesaveの初期化
	for (i = 0; i < 20; i++) {
		_codesave[i].usecheck = 0;
		_codesave[i].codesave = 0;
	}

	//Q_Keynumの初期化
	for (int i = 0; i < 3; i++) {
		Q_Keynum[i] = -1;
	}

	for (int i = 0; i < 5; i++) {
		//Q_correctの初期化
		Q_correct[i] = 0;
		_Q_savenum[0][i] = -1;
		_Q_savenum[1][i] = -1;
		//ランダム計算式更新
		Q_quest1[i] = rand() % 8 + 1;		// 1~9
		Q_quest2[i] = rand() % 8 + 1;		// 1~9
		Q_operator[i] = rand() % 2;		// 0:+  1;*
		switch (Q_operator[i])
		{
		case 0:
			Q_answer[i] = Q_quest1[i] + Q_quest2[i];
			break;
		case 1:
			Q_answer[i] = Q_quest1[i] * Q_quest2[i];
			break;
		}
	}

	//QP_savenumの初期化
	QnowQuest = 0;
	//QP_ansの初期化
	Q_stepflg = true;

	//QP_Keynumの初期化
	for (int i = 0; i < 3; i++) {
		QP_Keynum[i] = -1;
	}

	for (int i = 0; i < 5; i++) {
		//QP_correctの初期化
		QP_correct[i] = 0;
		_QP_savenum[0][i] = -1;
		_QP_savenum[1][i] = -1;
		//ランダム計算式更新
		QP_quest1[i] = rand() % 8 + 1;		// 1~9
		QP_quest2[i] = rand() % 8 + 1;		// 1~9
		QP_operator[i] = rand() % 2;		// 0:+  1;*
		switch (QP_operator[i])
		{
		case 0:
			QP_answer[i] = QP_quest1[i] + QP_quest2[i];
			break;
		case 1:
			QP_answer[i] = QP_quest1[i] * QP_quest2[i];
			break;
		}
	}
	//QP_savenumの初期化
	QPnowQuest = 0;
	//QP_ansの初期化
	QP_stepflg = true;

	QP_step = 0;

	//_puzzleの初期化
	for (i = 0; i < 9; i++) {
		_puzzle[i].drawOrder = i;
		_puzzle[i].x = 1920 / 2 + (rand() % 1920 / 2);
		_puzzle[i].y = 65 + (rand() % (720 - 65));
		_puzzle[i].cgpuzzle = LoadGraph(_puzzle[i].cghandle.c_str());
	}


	// マップデータの初期化
	for (int i = 0; i < MAP_W_1 * MAP_H_1; i++) {
		map1[i] = SlidePuzzle1[i];
	}
	for (int i = 0; i < MAP_W_2 * MAP_H_2; i++) {
		map2[i] = SlidePuzzle2[i];
	}


	Keycnt = 0;
	codesave = -1;
	pagenum = 0;
	pageMax = 0;
	CheckButton = false;
	gRot = 0;
	SetMousePoint(1920 * 3 / 4, 1080 / 2);

	return true;
}

void ModeWindow::AddSaveCode(int Icodesave) {
	for (int i = 0; i < 20; i++) {
		if (_codesave[i].usecheck == 0) {
			_codesave[i].usecheck = 1;
			_codesave[i].codesave = Icodesave;
			pageMax++;
			pagenum = i + 1;
			break;
		}
	}
}

bool ModeWindow::CheckCode(int codesave) {
	for (int i = 0; i < 20; i++) {
		if (_codesave[i].codesave == codesave) {
			return 0;
		}
	}
	return 1;
}

void ModeWindow::SetCode(int& codesave) {
	for (int i = 0; i < 20; i++) {
		if (_codesave[i].codesave == codesave) {
			codesave = _codesave[i].codesave;
			pagenum = i + 1;
			break;
		}
	}
}

int savepoint;

bool ModeWindow::Process() {
	base::Process();

	if (FullScreenFlg)
	{
		// このモードを削除する
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

	if (gChara_Dead) {
		// マップデータの初期化
		for (int i = 0; i < MAP_W_1 * MAP_H_1; i++) {
			map1[i] = SlidePuzzle1[i];
		}
		for (int i = 0; i < MAP_W_2 * MAP_H_2; i++) {
			map2[i] = SlidePuzzle2[i];
		}
		gChara_Dead = false;
	}
	//石板
	{
		int MouseX, MouseY;
		GetMousePoint(&MouseX, &MouseY);
		int buttonX = 1920 / 2;
		int buttonY = 0;
		if (MouseX > buttonX + 59 && MouseX < buttonX + 86 + 59 && MouseY > buttonY && MouseY < buttonY + 60)
		{
			if (gTrg & MOUSE_INPUT_LEFT)
			{
				pagenum = 0;
				PlaySoundMem(se[1], DX_PLAYTYPE_BACK, TRUE);
			}
		}
		for (int i = 0; i < pageMax; i++) {
			if (MouseX > buttonX + 151 + i * 70 && MouseX < buttonX + 151 + (i + 1) * 70 && MouseY > buttonY && MouseY < buttonY + 60)
			{
				if (gTrg & MOUSE_INPUT_LEFT)
				{
					codesave = _codesave[i].codesave;
					pagenum = i + 1;
					PlaySoundMem(se[1], DX_PLAYTYPE_BACK, TRUE);
				}
			}
		}
		if (pagenum == 0) {
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
						PlaySoundMem(se[0], DX_PLAYTYPE_BACK, TRUE);
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
			if (MouseX > buttonX - 100 && MouseX < buttonX + 100 && MouseY > buttonY - 75 && MouseY < buttonY + 75 || gKeyMouse.gKTrg[KEY_INPUT_RETURN])
			{
				if (GetMouseInput() & MOUSE_INPUT_LEFT || gKeyMouse.gKTrg[KEY_INPUT_RETURN])
				{
					CheckButton = true;
					codesave = -1;
					int Keycode = 0;
					bool KeyResetflg = 0;
					for (int i = 0; i < 4; i++) {
						if (_Keynum[i] != -1) { Keycode += _Keynum[i] * pow(10, 3 - i); }
					}
					for (int n = 0; n < jsonMax; n++) {
						if (_jsonData[n].code == Keycode) {
							codesave = Keycode;
							//コードがすでに登録されているか
							if (CheckCode(codesave)) {
								AddSaveCode(codesave);
							}
							else
							{
								SetCode(codesave);
							}
							KeyResetflg = 1;
							break;
						}
					}
					if (!KeyResetflg) {
						for (int i = 0; i < 5; i++) {
							_Keynum[i] = -1;
						}
						Keycnt = 0;
					}
				}
				else
				{
					CheckButton = false;
				}

			}
			else
			{
				CheckButton = false;
			}
		}
		//部屋ごとの処理
		if (_jsonData[0].code == codesave) {
			//ピザ部屋
			if (keyRoom != 6212) { return true; }
			if (RoomClear[3]) { return true; }
			if (MouseX > 1920 / 2 + 259 && MouseX < 1920 / 2 + 259 + 466 && MouseY >  -gRot * 10 + 850 && MouseY < -gRot * 10 + 850 + 94
				&& GetMouseInput() & MOUSE_INPUT_LEFT)
			{
				if (CodeButtonflg) {
					gPizza = true;
					CodeButtonflg = 0;
				}
			}
			else
			{
				CodeButtonflg = 1;
			}
		}
		if (_jsonData[1].code == codesave) {
			//スライドパズルその１部屋
			if (keyRoom != 1109) { return true; }
			if (RoomClear[1]) { return true; }
			
			if (!TalkFlg[2])
			{
				TalkFlg[2] = TRUE;
				ModeTalk* modetalk = new ModeTalk("res/jsonfile/TextData/slidepuzzle3.json");
				// ModeGameより上のレイヤーにトークを登録する
				ModeServer::GetInstance()->Add(modetalk, 200, "talk");
			}
			for (int i = 0; i < MAP_W_1 * MAP_H_1; i++) {
				int n = i / MAP_W_1;
				int map_y = 410 - 87;
				if (MouseX > 960 + 187 - 87 + (i % MAP_W_1) * 87 && MouseX <960 + 187 + (i % MAP_W_1) * 87 && MouseY >  map_y + n * 87 && MouseY < map_y + 87 + n * 87
					&& gTrg & MOUSE_INPUT_LEFT)
				{
					//0は反応しない
					if (map1[i] == 0) { savemap_num1 = 0; continue; }
					GetMousePoint(&savemouseX[0], &savemouseY[0]);
					savemap_num1 = map1[i];
					num = 0;

					reset = false;

					for (m = 0; m < MAP_W_1 * MAP_H_1; m++)
					{
						oldmap1[m] = map1[m];
					}
				}
				//if (MouseX > 960 + 50 + (i % MAP_W_1) * 40 && MouseX < 960 + 50 + 40 + (i % MAP_W_1) * 40 && MouseY >  200 + n * 40 && MouseY < 200 + 40 + n * 40 && gRel & MOUSE_INPUT_LEFT)
				if (gRel & MOUSE_INPUT_LEFT)
				{
					//savemap_num1に値が入っていたら反応しない
					if (savemap_num1 == 0) { continue; }

					PlaySoundMem(se[2], DX_PLAYTYPE_BACK, TRUE);
					reset = false;
					GetMousePoint(&savemouseX[1], &savemouseY[1]);
					if (savemouseX[0] == savemouseX[1] && savemouseY[0] == savemouseY[1]) { continue; }
					int pointX = abs(savemouseX[0]) - abs(savemouseX[1]);
					int pointY = abs(savemouseY[0]) - abs(savemouseY[1]);
					num = 0;
					// 1:右 2:左 3;上 4;下
					dirflg = 0;
					if (abs(pointX) > abs(pointY))
					{
						if (savemouseX[0] < savemouseX[1]) {
							dirflg = 1;
						}
						else
						{
							dirflg = 2;
						}
					}
					else
					{
						if (savemouseY[0] > savemouseY[1]) {
							dirflg = 3;
						}
						else
						{
							dirflg = 4;
						}
					}

					//グローバルに格納
					gMoverot = dirflg;
					gMovemap_num = savemap_num1;
#if 1
					switch (dirflg) {
					case 1: // 右に移動
						for (m = 0; m < MAP_W_1 * MAP_H_1; m++) {
							if (oldmap1[m] == savemap_num1) {
								if (m + 1 == MAP_W_1 * MAP_H_1) continue;
								map1[m + 1] = savemap_num1;
								num++;
							}
							else if (num > 0) {
								map1[m - num] = 0;
								num = 0;
							}
							if (oldmap1[m] > 10 && map1[m] > 10 && oldmap1[m] != map1[m]) {
								reset = true;
							}
						}
						break;
					case 2: // 左に移動
						for (m = MAP_W_1 * MAP_H_1 - 1; m != 0; m--) {
							if (oldmap1[m] == savemap_num1) {
								if (m - 1 < 0) continue;
								map1[m - 1] = savemap_num1;
								num++;
							}
							else if (num > 0) {
								map1[m + num] = 0;
								num = 0;
							}
							if (oldmap1[m] > 10 && map1[m] > 10 && oldmap1[m] != map1[m]) {
								reset = true;
							}
						}
						break;
					case 3: // 上に移動
						for (m = 0; m < MAP_W_1 * MAP_H_1; m++) {
							num = 0;
							for (int t = 0; t < MAP_H_1; t++) {
								if (oldmap1[(m % MAP_W_1) + t * MAP_W_1] == savemap_num1) {
									if ((m % MAP_W_1) + (t - 1) * MAP_W_1 < 0) break;
									if (oldmap1[m] > 10 && map1[m] > 10 && oldmap1[m] != map1[m]) break;
									map1[(m % MAP_W_1) + (t - 1) * MAP_W_1] = savemap_num1;
									map1[(m % MAP_W_1) + t * MAP_W_1] = 0;
								}
								if (oldmap1[(m % MAP_W_1) + t * MAP_W_1] > 10 && map1[(m % MAP_W_1) + t * MAP_W_1] > 10 && oldmap1[(m % MAP_W_1) + t * MAP_W_1] != map1[(m % MAP_W_1) + t * MAP_W_1]) {
									reset = true;
								}
							}
						}
						break;
					case 4: // 下に移動
						for (m = 0; m < MAP_W_1 * MAP_H_1; m++) {
							num = 0;
							for (int t = 0; t < MAP_H_1; t++) {
								if (oldmap1[(m % MAP_W_1) + t * MAP_W_1] == savemap_num1) {
									map1[(m % MAP_W_1) + (t + 1) * MAP_W_1] = savemap_num1;
									num++;
								}
								else if (num > 0) {
									map1[(m % MAP_W_1) + (t - num) * MAP_W_1] = 0;
									num = 0;
								}
								if (oldmap1[(m % MAP_W_1) + t * MAP_W_1] > 10 && map1[(m % MAP_W_1) + t * MAP_W_1] > 10 && oldmap1[(m % MAP_W_1) + t * MAP_W_1] != map1[(m % MAP_W_1) + t * MAP_W_1]) {
									savepoint = (m % MAP_W_1) + t * MAP_W_1;
									reset = true;
								}
							}
						}
						break;
					}

					for (m = 0; m < MAP_W_1 * MAP_H_1; m++)
					{
						if (oldmap1[m] == 98 && map1[m] != 98 ||
							oldmap1[m] == 99 && map1[m] != 99
							) {
							reset = true; break;
						}
					}
					if (reset)
					{
						for (m = 0; m < MAP_W_1 * MAP_H_1; m++)
						{
							map1[m] = oldmap1[m];
						}
						gMoverot = 0;
						gMovemap_num = 0;
					}
#endif
					//savemap_num1初期化
					savemap_num1 = 0;
				}
			}
		}

		if (_jsonData[2].code == codesave) {
			//博物館部屋
			if (keyRoom != 1114) { return true; }
			if (RoomClear[5]) { return true; }
			if (GetMouseInput() & MOUSE_INPUT_LEFT)
			{
				for (int i = 0; i < 9; i++) {

					if (MouseX > _puzzle[_puzzle[i].drawOrder].x && MouseX < _puzzle[_puzzle[i].drawOrder].x + _puzzle[_puzzle[i].drawOrder].w && MouseY > _puzzle[_puzzle[i].drawOrder].y && MouseY < _puzzle[_puzzle[i].drawOrder].y + _puzzle[_puzzle[i].drawOrder].h)
					{
						if (gTrg & MOUSE_INPUT_LEFT) {
							saveW = MouseX - _puzzle[_puzzle[i].drawOrder].x;
							saveH = MouseY - _puzzle[_puzzle[i].drawOrder].y;
							nowPuzzleNum = _puzzle[i].drawOrder;
							//drawOrderを入れ替え
							int saveDrawOrder;
							for (int n = i; n < 8; n++) {
								saveDrawOrder = _puzzle[n].drawOrder;
								_puzzle[n].drawOrder = _puzzle[n + 1].drawOrder;
								_puzzle[n + 1].drawOrder = saveDrawOrder;
							}
						}
						if (nowPuzzleNum == _puzzle[i].drawOrder && gKey & MOUSE_INPUT_LEFT)
						{
							_puzzle[_puzzle[i].drawOrder].x = MouseX - saveW;
							_puzzle[_puzzle[i].drawOrder].y = MouseY - saveH;
						}
					}
				}
			}

		}

		if (_jsonData[3].code == codesave) {
			if (keyRoom != 311) { return true; }
			if (RoomClear[2]) { return true; }
			if (gGlobal._isFinishFadeOut) { return true; }
			if (QnowQuest <= 3) {
				//制限時間減少　問題部屋
				int Keynum = -1;
				if (gKeyMouse.gKTrg[KEY_INPUT_0]) { Keynum = 0; }
				if (gKeyMouse.gKTrg[KEY_INPUT_1]) { Keynum = 1; }
				if (gKeyMouse.gKTrg[KEY_INPUT_2]) { Keynum = 2; }
				if (gKeyMouse.gKTrg[KEY_INPUT_3]) { Keynum = 3; }
				if (gKeyMouse.gKTrg[KEY_INPUT_4]) { Keynum = 4; }
				if (gKeyMouse.gKTrg[KEY_INPUT_5]) { Keynum = 5; }
				if (gKeyMouse.gKTrg[KEY_INPUT_6]) { Keynum = 6; }
				if (gKeyMouse.gKTrg[KEY_INPUT_7]) { Keynum = 7; }
				if (gKeyMouse.gKTrg[KEY_INPUT_8]) { Keynum = 8; }
				if (gKeyMouse.gKTrg[KEY_INPUT_9]) { Keynum = 9; }

				if (Keynum != -1) {
					for (int i = 0; i < 3; i++) {
						if (Q_Keynum[i] != -1) { continue; }
						Q_Keynum[i] = Keynum;
						break;
					}
				}

				//3桁目に数字が入っていたら初期化
				if (Q_Keynum[2] != -1) {
					for (int i = 0; i < 3; i++) {
						Q_Keynum[i] = -1;
					}
				}
			}

			//エンターキーを押したら回答
			if (gKeyMouse.gKTrg[KEY_INPUT_RETURN]) {
				//問題が終了したら初期化
				if (QnowQuest == 4) {
					QnowQuest = 0;
					for (int i = 0; i < 4; i++) {
						//Q_correctの初期化
						Q_correct[i] = 0;
						_Q_savenum[0][i] = -1;
						_Q_savenum[1][i] = -1;
						//ランダム計算式更新
						Q_quest1[i] = rand() % 8 + 1;		// 1~9
						Q_quest2[i] = rand() % 8 + 1;		// 1~9
						Q_operator[i] = rand() % 2;		// 0:+  1;*
						switch (Q_operator[i])
						{
						case 0:
							Q_answer[i] = Q_quest1[i] + Q_quest2[i];
							break;
						case 1:
							Q_answer[i] = Q_quest1[i] * Q_quest2[i];
							break;
						}
					}
					return true;
				}

				if (Q_Keynum[0] == -1) { return true; }
				//回答処理
				if (Q_Keynum[1] == -1) {
					//１桁の場合
					QP_savenum = Q_Keynum[0];
				}
				else
				{
					//２桁の場合
					QP_savenum = Q_Keynum[0] * 10 + Q_Keynum[1];
				}
				_Q_savenum[0][QnowQuest] = Q_Keynum[0];
				_Q_savenum[1][QnowQuest] = Q_Keynum[1];

				if (Q_answer[QnowQuest] == QP_savenum) {
					//正解時
					Q_correct[QnowQuest] = 1;
					gamecntdown += 120;			//秒数加算
				}
				else { Q_correct[QnowQuest] = 2; }
				//Q_Keynum初期化
				for (int i = 0; i < 3; i++) {
					Q_Keynum[i] = -1;
				}
				//次の問題へ
				QnowQuest++;
			}
		}

		if (_jsonData[4].code == codesave) {
			if (keyRoom != 223) { return true; }
			if (RoomClear[6]) { return true; }
			//プロペラ部屋
			int Keynum = -1;
			if (gKeyMouse.gKTrg[KEY_INPUT_0]) { Keynum = 0; }
			if (gKeyMouse.gKTrg[KEY_INPUT_1]) { Keynum = 1; }
			if (gKeyMouse.gKTrg[KEY_INPUT_2]) { Keynum = 2; }
			if (gKeyMouse.gKTrg[KEY_INPUT_3]) { Keynum = 3; }
			if (gKeyMouse.gKTrg[KEY_INPUT_4]) { Keynum = 4; }
			if (gKeyMouse.gKTrg[KEY_INPUT_5]) { Keynum = 5; }
			if (gKeyMouse.gKTrg[KEY_INPUT_6]) { Keynum = 6; }
			if (gKeyMouse.gKTrg[KEY_INPUT_7]) { Keynum = 7; }
			if (gKeyMouse.gKTrg[KEY_INPUT_8]) { Keynum = 8; }
			if (gKeyMouse.gKTrg[KEY_INPUT_9]) { Keynum = 9; }

			if (Keynum != -1) {
				for (int i = 0; i < 3; i++) {
					if (P_Keynum[i] != -1) { continue; }
					P_Keynum[i] = Keynum;
					break;
				}
			}

			//3桁目に数字が入っていたら初期化
			if (P_Keynum[2] != -1) {
				for (int i = 0; i < 3; i++) {
					P_Keynum[i] = -1;
				}
			}
			//P_ansフラグが立っていた時
			if (P_ans) {
				PlaySoundMem(se[3], DX_PLAYTYPE_BACK, TRUE);
				if (30 <= P_savenum &&
					P_savenum < 36) {
					FanSpeed = (P_savenum - 30) * 0.05f;
				}
				P_ans = false;
				//Q_Keynum初期化
				for (int i = 0; i < 3; i++) {
					P_Keynum[i] = -1;
				}

			}
			//エンターキーを押したら回答
			if (gKeyMouse.gKTrg[KEY_INPUT_RETURN]) {
				P_ans = true;
				if (P_Keynum[1] == -1) {
					//１桁の場合
					P_savenum = P_Keynum[0];
				}
				else
				{
					//２桁の場合
					P_savenum = P_Keynum[0] * 10 + P_Keynum[1];
				}
			}
		}

		if (_jsonData[5].code == codesave) {
			//スライドパズルその２部屋
			if (keyRoom != 4226) { return true; }
			if (RoomClear[4]) { return true; }
			for (int i = 0; i < MAP_W_2 * MAP_H_2; i++) {
				int n = i / MAP_W_2;
				int map_y = 249;
				if (MouseX > 960 + 227 + (i % MAP_W_2) * 86 && MouseX < 960 + 227 + 86 + (i % MAP_W_2) * 86 && MouseY >  map_y + n * 86 && MouseY < map_y + 86 + n * 86
					&& gTrg & MOUSE_INPUT_LEFT)
				{

					//0は反応しない
					if (map2[i] == 0) { savemap_num2 = 0; continue; }
					GetMousePoint(&savemouseX[0], &savemouseY[0]);
					savemap_num2 = map2[i];
					num = 0;

					reset = false;

					for (m = 0; m < MAP_W_2 * MAP_H_2; m++)
					{
						oldmap2[m] = map2[m];
					}
				}
				//if (MouseX > 960 + 50 + (i % MAP_W_2) * 40 && MouseX < 960 + 50 + 40 + (i % MAP_W_2) * 40 && MouseY >  200 + n * 40 && MouseY < 200 + 40 + n * 40 && gRel & MOUSE_INPUT_LEFT)
				if (gRel & MOUSE_INPUT_LEFT)
				{
					//savemap_num2に値が入っていたら反応しない
					if (savemap_num2 == 0) { continue; }
					PlaySoundMem(se[2], DX_PLAYTYPE_BACK, TRUE);
					reset = false;
					GetMousePoint(&savemouseX[1], &savemouseY[1]);
					if (savemouseX[0] == savemouseX[1] && savemouseY[0] == savemouseY[1]) { continue; }
					int pointX = abs(savemouseX[0]) - abs(savemouseX[1]);
					int pointY = abs(savemouseY[0]) - abs(savemouseY[1]);
					num = 0;
					// 1:右 2:左 3;上 4;下
					dirflg = 0;
					if (abs(pointX) > abs(pointY))
					{
						if (savemouseX[0] < savemouseX[1]) {
							dirflg = 1;
						}
						else
						{
							dirflg = 2;
						}
					}
					else
					{
						if (savemouseY[0] > savemouseY[1]) {
							dirflg = 3;
						}
						else
						{
							dirflg = 4;
						}
					}

					//グローバルに格納
					gMoverot = dirflg;
					gMovemap_num = savemap_num2;
#if 1
					switch (dirflg) {
					case 1: // 右に移動
						for (m = 0; m < MAP_W_2 * MAP_H_2; m++) {
							if (oldmap2[m] == savemap_num2) {
								if (m + 1 == MAP_W_2 * MAP_H_2) continue;
								map2[m + 1] = savemap_num2;
								num++;
							}
							else if (num > 0) {
								map2[m - num] = 0;
								num = 0;
							}
							if (oldmap2[m] > 10 && map2[m] > 10 && oldmap2[m] != map2[m]) {
								reset = true;
							}
						}
						break;
					case 2: // 左に移動
						for (m = MAP_W_2 * MAP_H_2 - 1; m != 0; m--) {
							if (oldmap2[m] == savemap_num2) {
								if (m - 1 < 0) continue;
								map2[m - 1] = savemap_num2;
								num++;
							}
							else if (num > 0) {
								map2[m + num] = 0;
								num = 0;
							}
							if (oldmap2[m] > 10 && map2[m] > 10 && oldmap2[m] != map2[m]) {
								reset = true;
							}
						}
						break;
					case 3: // 上に移動
						for (m = 0; m < MAP_W_2 * MAP_H_2; m++) {
							num = 0;
							for (int t = 0; t < MAP_H_2; t++) {
								if (oldmap2[(m % MAP_W_2) + t * MAP_W_2] == savemap_num2) {
									if ((m % MAP_W_2) + (t - 1) * MAP_W_2 < 0) break;
									if (oldmap2[m] > 10 && map2[m] > 10 && oldmap2[m] != map2[m]) break;
									map2[(m % MAP_W_2) + (t - 1) * MAP_W_2] = savemap_num2;
									map2[(m % MAP_W_2) + t * MAP_W_2] = 0;
								}
								if (oldmap2[(m % MAP_W_2) + t * MAP_W_2] > 10 && map2[(m % MAP_W_2) + t * MAP_W_2] > 10 && oldmap2[(m % MAP_W_2) + t * MAP_W_2] != map2[(m % MAP_W_2) + t * MAP_W_2]) {
									reset = true;
								}
							}
						}
						break;
					case 4: // 下に移動
						for (m = 0; m < MAP_W_2 * MAP_H_2; m++) {
							num = 0;
							for (int t = 0; t < MAP_H_2; t++) {
								if (oldmap2[(m % MAP_W_2) + t * MAP_W_2] == savemap_num2) {
									map2[(m % MAP_W_2) + (t + 1) * MAP_W_2] = savemap_num2;
									num++;
								}
								else if (num > 0) {
									map2[(m % MAP_W_2) + (t - num) * MAP_W_2] = 0;
									num = 0;
								}
								if (oldmap2[(m % MAP_W_2) + t * MAP_W_2] > 10 && map2[(m % MAP_W_2) + t * MAP_W_2] > 10 && oldmap2[(m % MAP_W_2) + t * MAP_W_2] != map2[(m % MAP_W_2) + t * MAP_W_2]) {
									savepoint = (m % MAP_W_2) + t * MAP_W_2;
									reset = true;
								}
							}
						}
						break;
					}

					for (m = 0; m < MAP_W_2 * MAP_H_2; m++)
					{
						if (oldmap2[m] == 98 && map2[m] != 98 ||
							oldmap2[m] == 99 && map2[m] != 99
							) {
							reset = true; break;
						}
					}
					if (reset)
					{
						for (m = 0; m < MAP_W_2 * MAP_H_2; m++)
						{
							map2[m] = oldmap2[m];
						}
						gMoverot = 0;
						gMovemap_num = 0;
					}
#endif
					//savemap_num2初期化
					savemap_num2 = 0;
				}
			}
		}
		if (_jsonData[6].code == codesave)
		{
			if (keyRoom != 3215) { return true; }
			if (RoomClear[7]) { return true; }
			if (gGlobal._isFinishFadeOut) { return true; }
			if (QP_step > 3)
			{
				if (QP_correct[0] == 1) { return true; }
				//制限時間減少　問題部屋
				int Keynum = -1;
				if (gKeyMouse.gKTrg[KEY_INPUT_0]) { Keynum = 0; }
				if (gKeyMouse.gKTrg[KEY_INPUT_1]) { Keynum = 1; }
				if (gKeyMouse.gKTrg[KEY_INPUT_2]) { Keynum = 2; }
				if (gKeyMouse.gKTrg[KEY_INPUT_3]) { Keynum = 3; }
				if (gKeyMouse.gKTrg[KEY_INPUT_4]) { Keynum = 4; }
				if (gKeyMouse.gKTrg[KEY_INPUT_5]) { Keynum = 5; }
				if (gKeyMouse.gKTrg[KEY_INPUT_6]) { Keynum = 6; }
				if (gKeyMouse.gKTrg[KEY_INPUT_7]) { Keynum = 7; }
				if (gKeyMouse.gKTrg[KEY_INPUT_8]) { Keynum = 8; }
				if (gKeyMouse.gKTrg[KEY_INPUT_9]) { Keynum = 9; }

				if (Keynum != -1) {
					for (int i = 0; i < 5; i++) {
						if (QP_Keynum[i] != -1) { continue; }
						QP_Keynum[i] = Keynum;
						break;
					}
				}

				//5桁目に数字が入っていたら初期化
				if (QP_Keynum[4] != -1) {
					for (int i = 0; i < 5; i++) {
						QP_Keynum[i] = -1;
					}
					QP_correct[0] = 0;
				}
				if (gKeyMouse.gKTrg[KEY_INPUT_RETURN])
				{
					if (QP_Keynum[3] == -1) {
						QP_correct[0] = 0;
						return true;
					}
					int SaveNum = 0;
					for (int i = 0; i < 4; i++) {
						if (QP_Keynum[i] != -1) {
							SaveNum += QP_Keynum[i] * pow(10, 3 - i);
						}
					}
					if (SaveNum == 5226)
					{
						QP_correct[0] = 1;
						gamecntdown = 59940;		//999秒
						gChangeDoor = 1;
					}
					else
					{
						QP_correct[0] = 2;
					}
				}
			}
			else
			{
				if (QPnowQuest <= 3) {
					//制限時間減少　問題部屋
					int Keynum = -1;
					if (gKeyMouse.gKTrg[KEY_INPUT_0]) { Keynum = 0; }
					if (gKeyMouse.gKTrg[KEY_INPUT_1]) { Keynum = 1; }
					if (gKeyMouse.gKTrg[KEY_INPUT_2]) { Keynum = 2; }
					if (gKeyMouse.gKTrg[KEY_INPUT_3]) { Keynum = 3; }
					if (gKeyMouse.gKTrg[KEY_INPUT_4]) { Keynum = 4; }
					if (gKeyMouse.gKTrg[KEY_INPUT_5]) { Keynum = 5; }
					if (gKeyMouse.gKTrg[KEY_INPUT_6]) { Keynum = 6; }
					if (gKeyMouse.gKTrg[KEY_INPUT_7]) { Keynum = 7; }
					if (gKeyMouse.gKTrg[KEY_INPUT_8]) { Keynum = 8; }
					if (gKeyMouse.gKTrg[KEY_INPUT_9]) { Keynum = 9; }

					if (Keynum != -1) {
						for (int i = 0; i < 3; i++) {
							if (QP_Keynum[i] != -1) { continue; }
							QP_Keynum[i] = Keynum;

							break;
						}
					}

					//3桁目に数字が入っていたら初期化
					if (QP_Keynum[2] != -1) {
						for (int i = 0; i < 3; i++) {
							QP_Keynum[i] = -1;
						}
					}
				}

				//エンターキーを押したら回答
				if (gKeyMouse.gKTrg[KEY_INPUT_RETURN]) {
					//問題が終了したら初期化
					if (QPnowQuest == 4) {
						QPnowQuest = 0;
						QP_step++;
						for (int i = 0; i < 4; i++) {
							//QP_correctの初期化
							QP_correct[i] = 0;
							_QP_savenum[0][i] = -1;
							_QP_savenum[1][i] = -1;
							//ランダム計算式更新
							QP_quest1[i] = rand() % 8 + 1;		// 1~9
							QP_quest2[i] = rand() % 8 + 1;		// 1~9
							QP_operator[i] = rand() % 2;		// 0:+  1;*
							switch (QP_operator[i])
							{
							case 0:
								QP_answer[i] = QP_quest1[i] + QP_quest2[i];
								break;
							case 1:
								QP_answer[i] = QP_quest1[i] * QP_quest2[i];
								break;
							}
						}
						return true;
					}

					if (QP_Keynum[0] == -1) { return true; }
					//回答処理
					if (QP_Keynum[1] == -1) {
						//１桁の場合
						QP_savenum = QP_Keynum[0];
					}
					else
					{
						//２桁の場合
						QP_savenum = QP_Keynum[0] * 10 + QP_Keynum[1];
					}
					_QP_savenum[0][QPnowQuest] = QP_Keynum[0];
					_QP_savenum[1][QPnowQuest] = QP_Keynum[1];

					if (QP_answer[QPnowQuest] == QP_savenum) {
						//正解時
						QP_correct[QPnowQuest] = 1;
						gamecntdown += 240;			//秒数加算
					}
					else { QP_correct[QPnowQuest] = 2; }
					//QP_Keynum初期化
					for (int i = 0; i < 3; i++) {
						QP_Keynum[i] = -1;
					}
					//次の問題へ
					QPnowQuest++;
				}
			}


		}
		if (_jsonData[7].code == codesave) {
			//ピザ部屋
			if (keyRoom != 2126) { return true; }
			if (RoomClear[3]) { return true; }
			if (MouseX > 1920 / 2 + 259 && MouseX < 1920 / 2 + 259 + 466 && MouseY >  -gRot * 10 + 850 && MouseY < -gRot * 10 + 850 + 94
				&& GetMouseInput() & MOUSE_INPUT_LEFT)
			{
				if (CodeButtonflg) {
					gPizza = true;
					CodeButtonflg = 0;
				}
			}
			else
			{
				CodeButtonflg = 1;
			}
		}
		if (MouseX < 1920 / 2) {
			SetMousePoint(1920 / 2, MouseY);
		}
	}

	return true;
}

bool ModeWindow::Render() {
	base::Render();
	SetDrawArea(1920 / 2, 0, 1920, 1080);
	//石板
	{
		DrawGraph(1920 / 2, 0, cgBase[0], TRUE);
		//付箋描画
		{
			DrawGraph(1920 / 2 + 59, 24, cglabel[10], TRUE);
			int DrawLabel;
			for (int n = 0; n < pageMax; n++) {
				switch (_codesave[n].codesave)
				{
				case 223:
					DrawLabel = 0;
					break;
				case 311:
					DrawLabel = 1;
					break;
				case 1109:
					DrawLabel = 2;
					break;
				case 1114:
					DrawLabel = 3;
					break;
				case 2126:
					DrawLabel = 4;
					break;
				case 3215:
					DrawLabel = 5;
					break;
				case 4226:
					DrawLabel = 6;
					break;
				case 5226:
					DrawLabel = 7;
					break;
				case 6212:
					DrawLabel = 8;
					break;
				case 6225:
					DrawLabel = 9;
					break;

					break;
				default:
					DrawLabel = -1; // デフォルト値を設定
					break;
				}
				DrawGraph(1920 / 2 + 151 + n * 70, 24, cglabel[DrawLabel], TRUE);
			}
		}
		SetDrawArea(1920 / 2, 65, 1920, 1080);

		//０番の時だけ入力
		if (pagenum == 0) {
			DrawGraph(1920 / 2, 0, cgBase[1], TRUE);
			int Draw_Keynum[4];
			for (int i = 0; i < 4; i++) {
				if (0 < _Keynum[i]) { Draw_Keynum[i] = _Keynum[i]; }
			}
			int buttonX = 1920 * 3 / 4;
			int Font = GetFontSize();
			SetFontSize(64);
			for (int i = 0; i < 4; i++) {
				int n = 0;
				int DrawNum = cgNotNum;
				n = _Keynum[i];
				if (n != -1) {
					DrawNum = cgNum[n];
				}
				DrawGraph(1920 / 2 + 198 + i * 153, 275, cgNumFrame, TRUE);
				DrawGraph(1920 / 2 + 198 + i * 153, 275, DrawNum, TRUE);
				//int color = GetColor(255, 255, 255);
				//if (i == Keycnt) { color = GetColor(255, 0, 0); }
				//if (_Keynum[i] != -1) { DrawFormatString(buttonX + (i - 2) * 70, 100, color, "%d", _Keynum[i]); }
				//DrawFormatString(buttonX + (i - 2) * 70, 110, color, "_");

			}
			int DrawAreaMap[10];
			int TBL[] = { 4,2,1,8,7,3,0,5,6,9 };
			for (int i = 0; i < 10; i++) {
				if (SaveRoot[i] == 1) {
					DrawAreaMap[TBL[i]] = cgAreaMapNum[0][TBL[i]];
				}
				else
				{
					if (TBL[i] == 4) {
						DrawAreaMap[TBL[i]] = cgAreaMapEmpty[0];
						continue;
					}
					if (TBL[i] == 7 || TBL[i] == 6) {
						DrawAreaMap[TBL[i]] = cgAreaMapEmpty[3];
						continue;
					}
					if (TBL[i] == 9) {
						DrawAreaMap[TBL[i]] = cgAreaMapEmpty[2];
						continue;
					}
					DrawAreaMap[TBL[i]] = cgAreaMapEmpty[1];
					//if (SaveRoot[i] == 0) {
					//	if (TBL[i] == 4) {
					//		DrawAreaMap[TBL[i]] = cgAreaMapEmpty[0];
					//		continue;
					//	}
					//	if (TBL[i] == 6) {
					//		continue;
					//	}
					//	if (TBL[i] == 7) {
					//		DrawAreaMap[TBL[i]] = cgAreaMapEmpty[3];
					//		continue;
					//	}
					//	if (TBL[i] == 9) {
					//		DrawAreaMap[TBL[i]] = cgAreaMapEmpty[2];
					//		continue;
					//	}

					//	DrawAreaMap[TBL[i]] = cgAreaMapEmpty[1];
					//}
				}
				switch (keyRoom)
				{
				case 223:	DrawAreaMap[0] = cgAreaMapNum[1][0]; break;
				case 311:	DrawAreaMap[1] = cgAreaMapNum[1][1]; break;
				case 1109:	DrawAreaMap[2] = cgAreaMapNum[1][2]; break;
				case 1114:	DrawAreaMap[3] = cgAreaMapNum[1][3]; break;
				case 0:		DrawAreaMap[4] = cgAreaMapNum[1][4]; break;
				case 3215:  DrawAreaMap[5] = cgAreaMapNum[1][5]; break;
				case 2126:  DrawAreaMap[6] = cgAreaMapNum[1][6]; break;
				case 4226:  DrawAreaMap[7] = cgAreaMapNum[1][7]; break;
				case 6212:  DrawAreaMap[8] = cgAreaMapNum[1][8]; break;
				case 1225:  DrawAreaMap[9] = cgAreaMapNum[1][9]; break;
				}
			}

			{
				//マップ
				DrawGraph(1920 / 2 + 198, 494, cgAreaMapUI[1], TRUE);

				DrawGraph(1920 / 2 + 264, 544, cgAreaMapUI[0], TRUE);


				//DrawGraph(1920 / 2 + 237, 733, DrawAreaMap[0], TRUE);

				//DrawGraph(1920 / 2 + 371, 733, DrawAreaMap[1], TRUE);
				//DrawGraph(1920 / 2 + 371, 694, DrawAreaMap[2], TRUE);
				//DrawGraph(1920 / 2 + 371, 655, DrawAreaMap[3], TRUE);
				//DrawGraph(1920 / 2 + 371, 598, DrawAreaMap[4], TRUE);

				//DrawGraph(1920 / 2 + 496, 733, DrawAreaMap[5], TRUE);
				//DrawGraph(1920 / 2 + 496, 694, DrawAreaMap[6], TRUE);
				//DrawGraph(1920 / 2 + 496, 655, DrawAreaMap[7], TRUE);
				//DrawGraph(1920 / 2 + 496, 598, DrawAreaMap[8], TRUE);

				//DrawGraph(1920 / 2 + 621, 733, DrawAreaMap[9], TRUE);

				DrawGraph(1920 / 2 + 237, 733, DrawAreaMap[4], TRUE);

				DrawGraph(1920 / 2 + 371, 733, DrawAreaMap[2], TRUE);
				DrawGraph(1920 / 2 + 371, 694, DrawAreaMap[1], TRUE);
				DrawGraph(1920 / 2 + 371, 655, DrawAreaMap[8], TRUE);
				DrawGraph(1920 / 2 + 371, 598, DrawAreaMap[7], TRUE);

				DrawGraph(1920 / 2 + 496, 733, DrawAreaMap[3], TRUE);
				DrawGraph(1920 / 2 + 496, 694, DrawAreaMap[0], TRUE);
				DrawGraph(1920 / 2 + 496, 655, DrawAreaMap[5], TRUE);
				DrawGraph(1920 / 2 + 496, 598, DrawAreaMap[6], TRUE);

				DrawGraph(1920 / 2 + 621, 733, DrawAreaMap[9], TRUE);

			}
			SetFontSize(Font);
		}
		else
		{
			//codesaveで保存してある画像を表示
			for (int n = 0; n < jsonMax; n++) {
				if (_jsonData[n].code == codesave) {
					int oldRot = gRot;
					gRot -= GetMouseWheelRotVol();
					if (_jsonData[n].draw_h < 1080 + gRot * 10 - 65 || 0 > gRot * 10) {
						gRot = oldRot;
					}
					DrawGraph(1920 / 2, 0, cgwindow[n], TRUE);

					//部屋ごとの描画
					if (_jsonData[0].code == codesave)
					{
						if (RoomClear[3]) {
							DrawGraph(1920 / 2, 0, cgDialy[9], TRUE);
							DrawGraph(1920 / 2, 0, cgBase[2], TRUE);
						}
						else
						{
							DrawGraph(1920 / 2 + 259, 850, cgButton, TRUE);
							if (!CodeButtonflg) {
								SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
								DrawBox(1920 / 2 + 259, 850, 1920 / 2 + 259 + 466, 850 + 94, GetColor(0, 0, 0), 1);
								SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
							}
						}
					}
					if (_jsonData[1].code == codesave)
					{
						if (RoomClear[1]) {
							DrawGraph(1920 / 2, 0, cgDialy[2], TRUE);
							DrawGraph(1920 / 2, 0, cgBase[2], TRUE);
						}
						else
						{
							cgBlock[0] = LoadGraph("res/Window/SlidePuzle/Tile/0.png");
							cgBlock[1] = LoadGraph("res/Window/SlidePuzle/Tile/1.png");
							cgBlock[2] = LoadGraph("res/Window/SlidePuzle/Tile/2.png");
							cgBlock[3] = LoadGraph("res/Window/SlidePuzle/Tile/3.png");
							cgBlock[4] = LoadGraph("res/Window/SlidePuzle/Tile/4.png");
							cgBlock[5] = LoadGraph("res/Window/SlidePuzle/Tile/exit.png");
							bool blockflg[20];
							int map_y = 410 - 87;
							for (int i = 0; i < 20; i++) {
								blockflg[i] = 0;
							}
							for (int i = 0; i < MAP_W_1 * MAP_H_1; i++) {
								int n = i / MAP_W_1;
								if (map1[i] == 99) { continue; }
								DrawGraph(960 + 187 - 87 + (i % MAP_W_1) * 87, map_y + n * 87, cgBlock[0], TRUE);
							}
							for (int i = 0; i < MAP_W_1 * MAP_H_1; i++) {
								int n = i / MAP_W_1;

								if (map1[i] == 99) { continue; }

								if (1 < map1[i]) {
									if (map1[i] == 11 && blockflg[11] == 0) {
										blockflg[11] = 1;
										DrawGraph(960 + 187 - 87 + (i % MAP_W_1) * 87, map_y + n * 87, cgBlock[4], TRUE);
									}
									if (map1[i] == 12 && blockflg[12] == 0) {
										blockflg[12] = 1;
										DrawGraph(960 + 187 - 87 + (i % MAP_W_1) * 87, map_y + n * 87, cgBlock[1], TRUE);
									}
									if (map1[i] == 13 && blockflg[13] == 0) {
										blockflg[13] = 1;
										DrawGraph(960 + 187 - 87 + (i % MAP_W_1) * 87, map_y + n * 87, cgBlock[1], TRUE);
									}
									if (map1[i] == 14 && blockflg[14] == 0) {
										blockflg[14] = 1;
										DrawGraph(960 + 187 - 87 + (i % MAP_W_1) * 87, map_y + n * 87, cgBlock[2], TRUE);
									}
									if (map1[i] == 15 && blockflg[15] == 0) {
										blockflg[15] = 1;
										DrawGraph(960 + 187 - 87 + (i % MAP_W_1) * 87, map_y + n * 87, cgBlock[3], TRUE);
									}
									if (map1[i] == 16 && blockflg[16] == 0) {
										blockflg[16] = 1;
										DrawGraph(960 + 187 - 87 + (i % MAP_W_1) * 87, map_y + n * 87, cgBlock[3], TRUE);
									}
									if (map1[i] == 98 && blockflg[17] == 0) {
										blockflg[17] = 1;
										DrawGraph(960 + 187 - 87 + (i % MAP_W_1) * 87, map_y + n * 87, cgBlock[5], TRUE);
										continue;
									}
								}
							}
						}

					}
					if (_jsonData[2].code == codesave)
					{
						if (RoomClear[5]) {
							DrawGraph(1920 / 2, 0, cgDialy[3], TRUE);
							DrawGraph(1920 / 2, 0, cgBase[2], TRUE);
						}
						else
						{
							for (int i = 0; i < 9; i++) {
								//DrawBox(_puzzle[i].x, _puzzle[i].y, _puzzle[i].x + _puzzle[i].w, _puzzle[i].y + _puzzle[i].h, GetColor(_Color[i].r, _Color[i].g, _Color[i].b), 1);
								DrawGraph(_puzzle[_puzzle[i].drawOrder].x, _puzzle[_puzzle[i].drawOrder].y, _puzzle[_puzzle[i].drawOrder].cgpuzzle, TRUE);
								//DrawGraph(1920 / 2 + _puzzle[i].x, _puzzle[i].y + 65, _puzzle[i].cgpuzzle, TRUE);cgBase[2]
							}
						}
					}
					if (_jsonData[3].code == codesave)
					{
						if (RoomClear[2]) {
							DrawGraph(1920 / 2, 0, cgDialy[1], TRUE);
							DrawGraph(1920 / 2, 0, cgBase[2], TRUE);
						}
						else
						{
							int Font = GetFontSize();
							SetFontSize(32);
							for (int i = 0; i < 4; i++)
							{
								switch (Q_operator[i])
								{
								case 0:
									DrawGraph(1920 / 2 + 170, 390 + 150 * i, cgLabyNum[Q_quest1[i]], TRUE);
									DrawGraph(1920 / 2 + 271, 402 + 150 * i, cgCalc[0], TRUE);
									DrawGraph(1920 / 2 + 376, 390 + 150 * i, cgLabyNum[Q_quest2[i]], TRUE);
									break;
								case 1:
									DrawGraph(1920 / 2 + 170, 390 + 150 * i, cgLabyNum[Q_quest1[i]], TRUE);
									DrawGraph(1920 / 2 + 271, 402 + 150 * i, cgCalc[1], TRUE);
									DrawGraph(1920 / 2 + 376, 390 + 150 * i, cgLabyNum[Q_quest2[i]], TRUE);
									break;
								}

								//正解
								if (Q_correct[i] == 1) { DrawGraph(1920 / 2 + 739, 374 + 147 * i, cgAns[1], TRUE); }
								else if (Q_correct[i] == 2) { DrawGraph(1920 / 2 + 739, 374 + 147 * i, cgAns[0], TRUE); }
							}
							for (int i = 0; i < QnowQuest; i++)
							{
								//入力
								for (int j = 0; j < 2; j++) {
									if (_Q_savenum[j][i] == -1) { continue; }
									DrawGraph(1920 / 2 + 569 + 60 * j, 390 + 150 * i, cgLabyNum[_Q_savenum[j][i]], TRUE);
								}
							}

							//入力
							for (int j = 0; j < 3; j++) {
								if (Q_Keynum[j] == -1) { continue; }
								DrawGraph(1920 / 2 + 569 + 60 * j, 390 + 150 * QnowQuest, cgLabyNum[Q_Keynum[j]], TRUE);
							}

							SetFontSize(Font);
						}
					}
					if (_jsonData[4].code == codesave)
					{
						if (RoomClear[6]) {
							DrawGraph(1920 / 2, 0, cgDialy[0], TRUE);
							DrawGraph(1920 / 2, 0, cgBase[2], TRUE);
						}
						else
						{
							int Font = GetFontSize();
							SetFontSize(32);
							//入力
							for (int i = 0; i < 3; i++) {
								if (P_Keynum[i] == -1) { continue; }
								DrawFormatString(1920 / 2 + 584 - 10 + i * 55, 617 - 14, GetColor(0, 0, 0), "%d", P_Keynum[i]);
							}
							SetFontSize(Font);
						}
					}
					if (_jsonData[5].code == codesave)
					{
						if (RoomClear[4]) {
							DrawGraph(1920 / 2, 0, cgDialy[7], TRUE);
							DrawGraph(1920 / 2, 0, cgBase[2], TRUE);
						}
						else
						{
							bool blockflg[30];
							int map_y = 249;
							for (int i = 0; i < 30; i++) {
								blockflg[i] = 0;
							}
							for (int i = 0; i < MAP_W_2 * MAP_H_2; i++) {
								int n = i / MAP_W_2;
								if (map2[i] == 99) { continue; }
								DrawGraph(960 + 227 + (i % MAP_W_2) * 86, map_y + n * 86, cgBlock[20], TRUE);
							}
							for (int i = 0; i < MAP_W_2 * MAP_H_2; i++) {
								int n = i / MAP_W_2;
								if (map2[i] == 99) { continue; }

								if (1 < map2[i]) {
									if (map2[i] == 21 && blockflg[21] == 0) {
										blockflg[21] = 1;
										DrawGraph(960 + 227 + (i % MAP_W_2) * 86, map_y + n * 86, cgBlock[21], TRUE);
									}
									if (map2[i] == 22 && blockflg[22] == 0) {
										blockflg[22] = 1;
										DrawGraph(960 + 227 + (i % MAP_W_2) * 86, map_y + n * 86, cgBlock[22], TRUE);
									}
									if (map2[i] == 23 && blockflg[23] == 0) {
										blockflg[23] = 1;
										DrawGraph(960 + 227 + (i % MAP_W_2) * 86, map_y + n * 86, cgBlock[22], TRUE);
									}
									if (map2[i] == 28 && blockflg[28] == 0) {
										blockflg[28] = 1;
										DrawGraph(960 + 227 + (i % MAP_W_2) * 86, map_y + n * 86, cgBlock[22], TRUE);
									}
									if (map2[i] == 29 && blockflg[29] == 0) {
										blockflg[29] = 1;
										DrawGraph(960 + 227 + (i % MAP_W_2) * 86, map_y + n * 86, cgBlock[22], TRUE);
									}
									if (map2[i] == 24 && blockflg[24] == 0) {
										blockflg[24] = 1;
										DrawGraph(960 + 227 + (i % MAP_W_2) * 86, map_y + n * 86, cgBlock[24], TRUE);
									}
									if (map2[i] == 27 && blockflg[27] == 0) {
										blockflg[27] = 1;
										DrawGraph(960 + 227 + (i % MAP_W_2) * 86, map_y + n * 86, cgBlock[24], TRUE);
									}
									if (map2[i] == 25 && blockflg[25] == 0) {
										blockflg[25] = 1;
										DrawGraph(960 + 227 + (i % MAP_W_2) * 86, map_y + n * 86, cgBlock[25], TRUE);
									}
									if (map2[i] == 26 && blockflg[26] == 0) {
										blockflg[26] = 1;
										DrawGraph(960 + 227 + (i % MAP_W_2) * 86, map_y + n * 86, cgBlock[25], TRUE);
									}
									if (map2[i] == 98 && blockflg[19] == 0) {
										blockflg[19] = 1;
										DrawGraph(960 + 227 + (i % MAP_W_2) * 86, map_y + n * 86, cgBlock[19], TRUE);
									}
								}
							}
						}
					}
					if (_jsonData[6].code == codesave)
					{
						if (RoomClear[7]) {
							DrawGraph(1920 / 2, 0, cgDialy[6], TRUE);
							DrawGraph(1920 / 2, 0, cgBase[2], TRUE);
						}
						else
						{
							if (QP_step > 3)
							{
								DrawGraph(1920 / 2, 0, cgQP_Base[0], TRUE);
								DrawGraph(1920 / 2 + 176, 431, cgQP_Base[1], TRUE);
								int SaveNum = 0;
								if (QP_Keynum[0] != -1) { DrawGraph(1920 / 2 + 215, 690, cgLabyNum[QP_Keynum[0]], TRUE); }
								if (QP_Keynum[1] != -1) { DrawGraph(1920 / 2 + 274, 690, cgLabyNum[QP_Keynum[1]], TRUE); }
								if (QP_Keynum[2] != -1) { DrawGraph(1920 / 2 + 371, 690, cgLabyNum[QP_Keynum[2]], TRUE); }
								if (QP_Keynum[3] != -1) { DrawGraph(1920 / 2 + 430, 690, cgLabyNum[QP_Keynum[3]], TRUE); }

								//正解
								if (QP_correct[0] == 1) { DrawGraph(1920 / 2 + 739, 374 + 147, cgAns[1], TRUE); }
								else if (QP_correct[0] == 2) { DrawGraph(1920 / 2 + 739, 374 + 147, cgAns[0], TRUE); }

							}
							else
							{
								int Font = GetFontSize();
								SetFontSize(32);
								for (int i = 0; i < 4; i++)
								{
									switch (QP_operator[i])
									{
									case 0:
										DrawGraph(1920 / 2 + 170, 390 + 150 * i, cgLabyNum[QP_quest1[i]], TRUE);
										DrawGraph(1920 / 2 + 271, 402 + 150 * i, cgCalc[0], TRUE);
										DrawGraph(1920 / 2 + 376, 390 + 150 * i, cgLabyNum[QP_quest2[i]], TRUE);
										break;
									case 1:
										DrawGraph(1920 / 2 + 170, 390 + 150 * i, cgLabyNum[QP_quest1[i]], TRUE);
										DrawGraph(1920 / 2 + 271, 402 + 150 * i, cgCalc[1], TRUE);
										DrawGraph(1920 / 2 + 376, 390 + 150 * i, cgLabyNum[QP_quest2[i]], TRUE);
										break;
									}

									//正解
									if (QP_correct[i] == 1) { DrawGraph(1920 / 2 + 739, 374 + 147 * i, cgAns[1], TRUE); }
									else if (QP_correct[i] == 2) { DrawGraph(1920 / 2 + 739, 374 + 147 * i, cgAns[0], TRUE); }
								}
								for (int i = 0; i < QPnowQuest; i++)
								{
									//入力
									for (int j = 0; j < 2; j++) {
										if (_QP_savenum[j][i] == -1) { continue; }
										DrawGraph(1920 / 2 + 569 + 60 * j, 390 + 150 * i, cgLabyNum[_QP_savenum[j][i]], TRUE);
									}
								}

								//入力
								for (int j = 0; j < 3; j++) {
									if (QP_Keynum[j] == -1) { continue; }
									DrawGraph(1920 / 2 + 569 + 60 * j, 390 + 150 * QPnowQuest, cgLabyNum[QP_Keynum[j]], TRUE);
								}
								SetFontSize(Font);
							}

						}
					}
					if (_jsonData[7].code == codesave)
					{
						if (RoomClear[3]) {
							DrawGraph(1920 / 2, 0, cgDialy[5], TRUE);
							DrawGraph(1920 / 2, 0, cgBase[2], TRUE);
						}
						else
						{
							DrawGraph(1920 / 2 + 259, 850, cgButton, TRUE);
							if (!CodeButtonflg) {
								SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
								DrawBox(1920 / 2 + 259, 850, 1920 / 2 + 259 + 466, 850 + 94, GetColor(0, 0, 0), 1);
								SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
							}
						}
					}
					DrawGraph(1920 / 2, 0, cgBase[2], TRUE);
					break;
				}
			}
		}

		DrawGraph(1920 / 2 + 577, 1009, cgFullUI, TRUE);

		SetDrawArea(1920 / 2, 0, 1920, 1080);
	}
	SetDrawArea(0, 0, 1920, 1080);
	return true;
}

