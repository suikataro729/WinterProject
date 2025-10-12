
#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ApplicationGlobal.h"
#include "ModeGame.h"
#include "ModeTitle.h"
#include "ModeFade.h"

// メニュー項目
class MenuItemViewCollision : public MenuItemBase {
public:
	MenuItemViewCollision(void* param, std::string text) : MenuItemBase(param, text) {}

	// 項目を決定したらこの関数が呼ばれる
	// return int : 0 = メニュー継続, 1 = メニュー終了
	virtual int Selected() {
		ModeGame* mdGame = static_cast<ModeGame*>(_param);
		mdGame->SetDebugViewColloion(!mdGame->GetDebugViewColloion());
		return 1;
	}
};

class MenuItemViewInfo : public MenuItemBase {
public:
	MenuItemViewInfo(void* param, std::string text) : MenuItemBase(param, text) {}

	// 項目を決定したらこの関数が呼ばれる
	// return int : 0 = メニュー継続, 1 = メニュー終了
	virtual int Selected() {
		ModeGame* mdGame = static_cast<ModeGame*>(_param);
		mdGame->SetDebugViewInfo(!mdGame->GetDebugViewInfo());
		return 0;
	}
};


bool ModeGame::Initialize() {
	if (!base::Initialize()) { return false; }

	se[0] = LoadSoundMem("res/sound/SE/move.wav");
	cgUI = LoadGraph("res/UI/UI_L.png");

	// キャラ初期化
	_chara.Init();
	// カメラ初期化
	_cam.Init(_chara._vPos);

	// マップ指定
	Rooms->ChangeRoom(keyRoom = 0);
	_flgMap = false;
	rData.RoomLoad(keyRoom);
	// キャラ・カメラのマップ対応初期化
	Rooms->SetSpown(_chara, _cam);

	// 非同期処理開始---------------------------------------------------
	SetUseASyncLoadFlag(TRUE);

	// オブジェクトの3Dモデル取得
	rData.LoadModelHandle();

	// 非同期処理終了---------------------------------------------------
	SetUseASyncLoadFlag(FALSE);

	// マップ初期化
	rData.RoomInit();

	// サウンド
	_sound.Load(keyRoom);

	// カウント画像読み込み
	for (int n = 0; n < 10; n++)
	{
		std::string img = "res/UI/L_UI/countNum/";
		img += std::to_string(n);
		img += ".png";
		cg_countNum[n] = LoadGraph(img.c_str());
	}
	for (int n = 0; n < 10; n++)
	{
		std::string img = "res/UI/L_UI/countNum_y/";
		img += std::to_string(n);
		img += ".png";
		cg_countNum_y[n] = LoadGraph(img.c_str());
	}
	cg_timebg = LoadGraph("res/UI/L_UI/TIMELIMIT.png");

	// 部屋番号画像読み込み
	cgRoomNumber[0] = LoadGraph("res/UI/L_UI/RoomNum/6212.png");
	cgRoomNumber[1] = LoadGraph("res/UI/L_UI/RoomNum/1109.png");
	cgRoomNumber[2] = LoadGraph("res/UI/L_UI/RoomNum/1114.png");
	cgRoomNumber[3] = LoadGraph("res/UI/L_UI/RoomNum/0311.png");
	cgRoomNumber[4] = LoadGraph("res/UI/L_UI/RoomNum/0223.png");
	cgRoomNumber[5] = LoadGraph("res/UI/L_UI/RoomNum/beforetheday.png");
	cgRoomNumber[6] = LoadGraph("res/UI/L_UI/RoomNum/3215.png");
	cgRoomNumber[7] = LoadGraph("res/UI/L_UI/RoomNum/101birthday.png");
	cgRoomNumber[8] = LoadGraph("res/UI/L_UI/RoomNum/entrance.png");
	cgRoomNumber[9] = LoadGraph("res/UI/L_UI/RoomNum/theChristmas.png");

	// 非同期処理終了---------------------------------------------------
	//SetUseASyncLoadFlag(FALSE);

	// エフェクト用
	_flgEffect = false;

	// その他初期化
	_bViewCollision = FALSE;
	_bViewInfo = FALSE;
	respown_flg = false;
	clear_cnt = -1;
	FullScreenFlg = TRUE;
	_flgPlay = true;

	SetMouseDispFlag(true);

#if 0
	ModeTalk* modetalk = new ModeTalk("res/jsonfile/TextData/christmas.json");
	// ModeGameより上のレイヤーにトークを登録する
	ModeServer::GetInstance()->Add(modetalk, 200, "talk");
#endif
#if 0
	ModeEnding* modetalk = new ModeEnding();
	// ModeGameより上のレイヤーにトークを登録する
	ModeServer::GetInstance()->Add(modetalk, 200, "talk");
#endif
#if 0
	ModeRoomNumber* modegamenumber = new ModeRoomNumber(keyRoom, 1109, TRUE);
	// ModeGameより上のレイヤーにメニューを登録する
	ModeServer::GetInstance()->Add(modegamenumber, 110, "number");
#endif
#if 0
	ModeEffekseer* modeeffekseer = new ModeEffekseer();
	modeeffekseer->Initialize(0.0f, 0.0f, 0.0f); // エフェクトの位置を設定
	// ModeGameより上のレイヤーにメニューを登録する
	ModeServer::GetInstance()->Add(modeeffekseer, 120, "effekseer");
#endif
//ウィンドウ出し
#if 0
	FullScreenFlg = FALSE;
	ModeWindow* modewindow = new ModeWindow();
	ModeServer::GetInstance()->Add(modewindow, 100, "window");
#endif
	//_vEffekseer[0].AddEffect("res/Laser01.efkefc", 0.0f, 500.0f, 0.0f);
	// テクスチャレンダリング用の画像作成
	render_texture_handle = MakeScreen(1920, 1080);

	// BGM再生
	_sound.Play(DX_PLAYTYPE_LOOP);

	return true;
}

bool ModeGame::Terminate() {
	base::Terminate();

	return true;
}

bool ModeGame::Process() {
	base::Process();
	int key = ApplicationMain::GetInstance()->GetKey();
	int trg = ApplicationMain::GetInstance()->GetTrg();
	int rel = ApplicationMain::GetInstance()->GetRel();


	if (!rData.IsLoad()) {

		// 処理前のステータスを保存しておく
		Chara::STATUS oldStatus = _chara._status;

		// ESCキーでModeEffekseerを開く
		//if (trg & PAD_INPUT_9) {
		//	gamecntdown = 0;
		//}

		// ゲームパッド対応（XInput）
		float lx, ly, rx, ry;	// 左右アナログスティックの座標
		float analogMin = 0.3f;	// アナログ閾値
		lx = (float)gPad[0].xinput_pad.ThumbLX / 32768.f; ly = (float)gPad[0].xinput_pad.ThumbLY / -32768.f;
		rx = (float)gPad[0].xinput_pad.ThumbRX / 32768.f; ry = (float)gPad[0].xinput_pad.ThumbRY / 32768.f;

		// マップ切り替え
		if (_flgMap) {
			// キャラクター初期化
			_chara.Spown(respown_flg);
			// カメラ初期化
			_cam.Spown(_chara._vPos);
			
			rData.RoomLoad(keyRoom);
			Rooms->SetSpown(_chara, _cam);
			_sound.Delete();

			// 非同期処理開始-------------------------
			SetUseASyncLoadFlag(TRUE);

			// オブジェクトの3Dモデル取得
			rData.LoadModelHandle();

			// 非同期処理終了-------------------------
			SetUseASyncLoadFlag(FALSE);

			// マップ初期化
			rData.RoomInit();
			// サウンド
			_sound.Load(keyRoom);

			_flgMap = false;
			_flgPlay = true;

			//BGM停止
			_sound.Stop();
			// BGM再生
			_sound.Play(DX_PLAYTYPE_LOOP);
		}

		//リスポーンフラグが立っていたら初期値にする
		if (respown_flg) {
			// キャラのリスポーンと初期化
			_chara.Spown(respown_flg);
			// 部屋初期化
			Rooms->Reset();
			// カメラ初期化
			_cam.Spown(_chara._vPos);
			respown_flg = false;

			if (!TalkFlg[4]) {
				TalkFlg[4] = TRUE;
				ModeTalk* modetalk = new ModeTalk("res/jsonfile/TextData/respawn.json");
				// ModeGameより上のレイヤーにトークを登録する
				ModeServer::GetInstance()->Add(modetalk, 200, "talk");
			}
		}

		// キャラ移動(カメラ設定に合わせて)

		// カメラの向いている角度を取得
		float sx = _cam._vPos.x - _cam._vTarget.x;
		float sz = _cam._vPos.z - _cam._vTarget.z;
		float camrad = atan2(sz, sx);

		// 移動方向を決める
		VECTOR v = { 0,0,0 };
		float mvSpeed;
		float length = sqrt(lx * lx + ly * ly);
		float rad = atan2(lx, ly);

		{
			mvSpeed = 6.f;
			if (length < analogMin) {
				// 入力が小さかったら動かなかったことにする
				length = 0.f;
			}
			else {
				length = mvSpeed;
			}
			// vをrad分回転させる
			v.x = cos(rad + camrad) * length;
			v.z = sin(rad + camrad) * length;
		}

		// 移動量設定
		v = VScale(v, 2.f);
		// 移動前の位置を保存
		_chara._oldvPos = _chara._vPos;
		VECTOR oldv = v;
		_cam._vPos = _cam._oldvPos;

		// vの分移動
		_chara._vPos = VAdd(_chara._vPos, v);

		// 重力増加
		if (_chara.gravity < 100.f) {
			_chara.gravity += 0.6f;
		}
		else {
			_chara.gravity = 100.f;
		}

		// キャラ移動処理
		// 部屋による処理
		Rooms->Process(_chara, _cam, v, oldv);

		if (_chara.jump_flg == 1) {
			if (_chara._isLanded)
			{
				_effekseer.AddEffect("res/Effect/jump/jump.efkefc", _chara._vPos.x, _chara._vPos.y, _chara._vPos.z, 30);
				_vEffekseer.push_back(_effekseer);
			}
			// ジャンプ処理
			_chara.Jump();
		}

		//重力の反映
		_chara._vPos.y -= _chara.gravity;

		// キャラが降下中（下に移動している）か
		if (_chara.jump_flg && _chara._vPos.y < _chara._oldvPos.y) {
			// 降下アニメーションに変更
			_chara._flgJumpAnim = 2;
		}

		// キャラが上下に移動した量だけ、移動量を修正
		v.y += _chara._vPos.y - _chara._oldvPos.y;

		// カメラ修正
		_cam._vPos.y += v.y;
		_cam._vTarget.y += v.y;

		//落下時に元の座標に戻る
		if (_chara._vPos.y < -400 || _chara._isDead)
		{
			respown_flg = true;
			gChara_Dead = true;
		}

		// 移動量をそのままキャラの向きにする
		// キャラクターステータス更新
		_chara.ChangeStatus(v);

		// カメラ操作を行う（右スティック）
		{
			// Y軸回転
			float sx = _cam._vPos.x - _cam._vTarget.x;
			float sz = _cam._vPos.z - _cam._vTarget.z;
			float rad = atan2(sz, sx);
			float length = sqrt(sz * sz + sx * sx);
			if (rx > analogMin) { rad -= 0.05f; }
			if (rx < -analogMin) { rad += 0.05f; }
			_cam._vPos.x = _cam._vTarget.x + cos(rad) * length;
			_cam._vPos.z = _cam._vTarget.z + sin(rad) * length;

			// Y位置
			if (ry > analogMin) { _cam._vPos.y -= 5.f; }
			if (ry < -analogMin) { _cam._vPos.y += 5.f; }
		}

		// カメラ当たり判定
		Rooms->CameraProcess(_cam);

		// キャラクターアニメーション更新
		_chara.ChangeCharaAnim(oldStatus);

		//カウントダウン
		{
			if (gamecntdown != -999)
			{
				gamecntdown -= 1;
				if (-60 > gamecntdown)
				{
					//０秒になった
					_chara._flgExit = true;
				}
			}
		}
		// エフェクト処理
		if (keyRoom != 1225)
		{
			if (VSize(v) > 0.f) {		// 移動していない時は無視するため
				if (GetModeCount() % 11 == 0 && _chara._isLanded == true) {
					_effekseer.AddEffect("res/Effect/dash/dash.efkefc", _chara._vPos.x, _chara._vPos.y, _chara._vPos.z, 37);
					_vEffekseer.push_back(_effekseer);
				}
				if (GetModeCount() % 45 == 0 && _chara._isLanded == true) {
					PlaySoundMem(se[0], DX_PLAYTYPE_BACK, TRUE);
				}
			}

			//if (gPad[0].gXTrg[XINPUT_BUTTON_X]) {
			//_effekseer.AddEffect("res/Laser01.efkefc", _chara._vPos.x, _chara._vPos.y, _chara._vPos.z);
			//_vEffekseer.push_back(_effekseer);
			//}
			for (int i = 0; i < _vEffekseer.size(); i++) {
				_vEffekseer[i].Process();

				// 消去処理
				if (_vEffekseer[i].EffectCnt > _vEffekseer[i].EffectCntMax) {
					_vEffekseer.erase(_vEffekseer.begin() + i);
				}
			}
			// Effekseerにより再生中のエフェクトを更新する。
			UpdateEffekseer3D();
		}

		// 出口
		if (_chara._flgExit) {
			if (_flgPlay) {
				// フェードインアウト
				ModeServer::GetInstance()->Add(new ModeFade("OUT"), 998, "fade");
				_flgPlay = false;
			}
			else {
				if (gGlobal._isFinishFadeOut) {
					// フェードアウト終了
					ModeRoomNumber* modegamenumber;
					if (-60 > gamecntdown && gamecntdown != -999) {
						// タイムアップによるゲームオーバー
						modegamenumber = new ModeRoomNumber(keyRoom, gGlobal.keyLoseRoom, FALSE);
						keyRoom = gGlobal.keyLoseRoom;

						if (!TalkFlg[3]) {
							TalkFlg[3] = TRUE;
							ModeTalk* modetalk = new ModeTalk("res/jsonfile/TextData/timeflag.json");
							// ModeGameより上のレイヤーにトークを登録する
							ModeServer::GetInstance()->Add(modetalk, 200, "talk");
						}
					}
					else {
						// ゴール到着によるステージクリア
						modegamenumber = new ModeRoomNumber(keyRoom, gGlobal.keyNextRoom, TRUE);
						keyRoom = gGlobal.keyNextRoom;
					}
					// ModeGameより上のレイヤーにメニューを登録する
					ModeServer::GetInstance()->Add(modegamenumber, 110, "number");

					_flgMap = true;
					_sound.Stop();
					_sound.Delete();
					rData.RoomRelease();
					Rooms->ChangeRoom(keyRoom);
					_chara._flgExit = false;
				}
			}
		}

		// デバッグ
		// ESCキーでメニューを開く
		if (trg & PAD_INPUT_9) {
			ModeMenu* modeMenu = new ModeMenu();
			// ModeGameより上のレイヤーにメニューを登録する
			ModeServer::GetInstance()->Add(modeMenu, 999, "menu");
			// ModeMenuにメニュー項目を追加する
			modeMenu->Add(new MenuItemViewCollision(this, "ViewCollision"));
			modeMenu->Add(new MenuItemViewInfo(this, "ViewInfo"));
		}
	}

	return true;
}

bool ModeGame::Render() {
	SetDrawScreen(render_texture_handle);
	ClearDrawScreen();
	base::Render();

	//if (rData.IsLoad()) {
	//	DrawFormatString(0, 0, GetColor(255, 255, 255), "非同期読み込みの数 %d", GetASyncLoadNum());
	//}
	{

		//if (FullScreenFlg) {
		//	// このモードより下のレイヤーはProcess()を呼ばない
		//	ModeServer::GetInstance()->SkipRenderUnderLayer();
		//}
		//SetDrawArea(0, 0, 1920/2, 1080);
		//SetCameraScreenCenter(1920 / 4, 1080 / 2);

		// 3D基本設定
		SetUseZBuffer3D(TRUE);
		SetWriteZBuffer3D(TRUE);
		SetUseBackCulling(TRUE);
	}

	// ライト設定
	SetUseLighting(TRUE);
#if 1	// 平行ライト
	SetGlobalAmbientLight(GetColorF(0.0f, 0.f, 0.f, 0.f));
	ChangeLightTypeDir(VGet(0, -1, 0));
#endif
#if 0	// ポイントライト
	SetGlobalAmbientLight(GetColorF(0.f, 0.f, 0.f, 0.f));
	ChangeLightTypePoint(VAdd(_chara._vPos,VGet(0,50.f,0)), 1000.f, 0.f, 0.005f, 0.f);
#endif

	if (!rData.IsLoad()) {

		// カメラ設定更新
		SetCameraPositionAndTarget_UpVecY(_cam._vPos, _cam._vTarget);
		SetCameraNearFar(_cam._clipNear, _cam._clipFar);

		if (_bViewCollision) {
			// 0,0,0を中心に線を引く
			{
				float linelength = 1000.f;
				VECTOR v = { 0, 0, 0 };
				DrawLine3D(VAdd(v, VGet(-linelength, 0, 0)), VAdd(v, VGet(linelength, 0, 0)), GetColor(255, 0, 0));
				DrawLine3D(VAdd(v, VGet(0, -linelength, 0)), VAdd(v, VGet(0, linelength, 0)), GetColor(0, 255, 0));
				DrawLine3D(VAdd(v, VGet(0, 0, -linelength)), VAdd(v, VGet(0, 0, linelength)), GetColor(0, 0, 255));
			}

			// カメラターゲットを中心に短い線を引く
			{
				float linelength = 10.f;
				VECTOR v = _cam._vTarget;
				DrawLine3D(VAdd(v, VGet(-linelength, 0, 0)), VAdd(v, VGet(linelength, 0, 0)), GetColor(255, 0, 0));
				DrawLine3D(VAdd(v, VGet(0, -linelength, 0)), VAdd(v, VGet(0, linelength, 0)), GetColor(0, 255, 0));
				DrawLine3D(VAdd(v, VGet(0, 0, -linelength)), VAdd(v, VGet(0, 0, linelength)), GetColor(0, 0, 255));
			}
		}

		// モデルを描画する
		{
			_chara.Render();

			// コリジョン判定用ラインの描画
			if (_bViewCollision) {
				DrawLine3D(VAdd(_chara._vPos, VGet(0, _chara._colSubY, 0)), VAdd(_chara._vPos, VGet(0, -99999.f, 0)), GetColor(255, 0, 0));

				// カプセル
				DrawCapsule3D(VAdd(_chara._vPos, VGet(0, _chara._collLower, 0)), VAdd(_chara._vPos, VGet(0, _chara._collUpper, 0)), _chara._CapsuleR, 8, GetColor(255, 0, 0), GetColor(0, 255, 0), FALSE);
			}
		}

		//丸影の表示
		//USEFUL.DrawRoundShadow(_handleMap,_frameMapCollision, _chara._vPos, _chara._colSubY,30.f,90);


		// マップモデルを描画する
		{
			Rooms->Render(_chara._vPos, _bViewCollision);
		}

		// フォグを有効にする
		SetFogEnable(TRUE);

		// フォグの色を黄色にする
		SetFogColor(255, 255, 255);

		// フォグの開始距離を０、終了距離を１５００にする
		SetFogStartEnd(0.0f, 8000.0f);

		//effekseer描画
		if (keyRoom != 1225) {
			_effekseer.Render();
		}

		// ターゲットをバックバッファに戻して、レンダリングしたテクスチャを使用して描画
		SetDrawScreen(DX_SCREEN_BACK);

		if (FullScreenFlg) {
			SetDrawArea(0, 0, 1920, 1080);
			//３D描画をずらす
			DrawGraph(0, 0, render_texture_handle, TRUE);
		}
		else
		{
			SetDrawArea(0, 0, 1920 / 2, 1080);
			//３D描画をずらす
			DrawGraph(-1920 / 4, 0, render_texture_handle, TRUE);
		}

		int x = 0, y = 300, size = 16;
		// カメラ情報表示
		if(_bViewInfo) {
			SetFontSize(size);

			DrawFormatString(x, y, GetColor(255, 0, 0), "Camera:"); y += size;
			DrawFormatString(x, y, GetColor(255, 0, 0), "  target = (%5.2f, %5.2f, %5.2f)", _cam._vTarget.x, _cam._vTarget.y, _cam._vTarget.z); y += size;
			DrawFormatString(x, y, GetColor(255, 0, 0), "  pos    = (%5.2f, %5.2f, %5.2f)", _chara._vPos.x, _chara._vPos.y, _chara._vPos.z); y += size;
			float sx = _cam._vPos.x - _cam._vTarget.x;
			float sz = _cam._vPos.z - _cam._vTarget.z;
			float length = sqrt(sz * sz + sx * sx);
			float rad = atan2(sz, sx);
			float deg = RAD2DEG(rad);
			DrawFormatString(x, y, GetColor(255, 0, 0), "  len = %5.2f, rad = %5.2f, deg = %5.2f", length, rad, deg); y += size;
			DrawFormatString(x, y, GetColor(255, 0, 0), "  _chara._vDir.x = %5.2f, _chara._vDir.y = %5.2f, _chara._vDir.z = %5.2f", _chara._vDir.x, _chara._vDir.y, _chara._vDir.z); y += size;

			// カプセルと衝突したポリゴン数
			DrawFormatString(x, y, GetColor(255, 0, 0), "  Capsule Collision : %d", _chara.CntHitCapsule); y += size;
			// 当たった床のタイプ
			DrawFormatString(x, y, GetColor(255, 0, 0), "  MapBoxType : %d", _chara._mapBoxType); y += size;
			// 当たったオブジェクトタイプ
			DrawFormatString(x, y, GetColor(255, 0, 0), "  HitObjType : %d", _chara._hitObjType); y += size;
			// マップフラグ
			DrawFormatString(x, y, GetColor(255, 0, 0), "  flgMap : %d", _flgMap); y += size;
			// ピザ出現フラグ
			DrawFormatString(x, y, GetColor(255, 0, 0), "  gPizza : %d", gPizza); y += size;
			// カプセルと衝突したポリゴンの法線ベクトル
			if (_chara._vNormal.size() != 0) {
				for (int i = 0; i < _chara._vNormal.size(); i++) {
					DrawFormatString(x, y, GetColor(255, 0, 0), "  vNormal[%d] : (%5.2f, %5.2f, %5.2f)", i, _chara._vNormal[i].x, _chara._vNormal[i].y, _chara._vNormal[i].z); y += size;
				}
			}

			for (int i = 0; i < _vEffekseer.size(); i++)
			{
				DrawFormatString(x, y, GetColor(255, 0, 0), "  _vEffekseer[i].x:%5.2f", _vEffekseer[i]._position_x); y += size;
				DrawFormatString(x, y, GetColor(255, 0, 0), "  _vEffekseer[i].y:%5.2f", _vEffekseer[i]._position_y); y += size;
				DrawFormatString(x, y, GetColor(255, 0, 0), "  _vEffekseer[i].z:%5.2f", _vEffekseer[i]._position_z); y += size;
			}
		}


		//画面上部UI
		if (FullScreenFlg) {
			if (gamecntdown != -999)
			{
				int DrawCnt[3];
				int saveCnt = gamecntdown / 60;
				int values[] = { 100, 10, 1 };
				int Font = GetFontSize();
				int digit = 0;		//桁数
				SetFontSize(64);
				//カウントダウン
				{
					//カウントダウン背景
					DrawGraph(848, 45, cg_timebg, TRUE);

					for (int i = 2; i >= 0; i--) {
						DrawCnt[i] = saveCnt % 10;	// 最下位桁を取り出し
						saveCnt = saveCnt / 10;			// 数値を右にシフト
					}
					//カウントダウン数字描画
					for (int i = 0; i < 3; i++) {
						if ((gamecntdown / 60) < values[i]) { continue; }
						digit++;
					}
					//カウントダウン数字描画
					for (int i = 0; i < 3; i++) {
						if ((gamecntdown / 60) < values[i]) { continue; }
						switch (digit)
						{
						case 3:
							DrawGraph(891 + 40 * i, 21, cg_countNum[DrawCnt[i]], TRUE);
							break;
						case 2:
							if (gamecntdown / 60 <= 20) {
								//残り時間20秒以下で数字が黄色くなる
								DrawGraph(871 + 40 * i, 21, cg_countNum_y[DrawCnt[i]], TRUE);
							}
							else
							{
								DrawGraph(871 + 40 * i, 21, cg_countNum[DrawCnt[i]], TRUE);
							}
							break;
						case 1:
							//残り時間20秒以下で数字が黄色くなる
							DrawGraph(931, 21, cg_countNum_y[DrawCnt[i]], TRUE);
							break;
						}

					}
				}
				//部屋番号
				{
					int num = 0;
					switch (keyRoom) {
					case 6212: num = 0; break;
					case 1109: num = 1; break;
					case 1114: num = 2; break;
					case 311: num = 3; break;
					case 223: num = 4; break;
					case 4226: num = 5; break;
					case 3215: num = 6; break;
					case 2126: num = 7; break;
					case 0: num = 8; break;
					case 1225: num = 9; break;
					}
					//部屋番号背景
					//for (int i = 47; i > 0; i--)
					//{
					//	DrawGraph(608 - i * 3, i, cgRoomNumber[num], TRUE);
					//}
					DrawGraph(1580, 47, cgRoomNumber[num], TRUE);
				}
				SetFontSize(Font);
			}
		}
		else
		{
			if (gamecntdown != -999)
			{
				int DrawCnt[3];
				int saveCnt = gamecntdown / 60;
				int values[] = { 100, 10, 1 };
				int Font = GetFontSize();
				int digit = 0;		//桁数
				SetFontSize(64);
				//カウントダウン
				{
					//カウントダウン背景
					DrawGraph(367, 45, cg_timebg, TRUE);

					for (int i = 2; i >= 0; i--) {
						DrawCnt[i] = saveCnt % 10;	// 最下位桁を取り出し
						saveCnt = saveCnt / 10;			// 数値を右にシフト
					}
					//カウントダウン数字描画
					for (int i = 0; i < 3; i++) {
						if ((gamecntdown / 60) < values[i]) { continue; }
						digit++;
					}

					//カウントダウン数字描画
					for (int i = 0; i < 3; i++) {
						if ((gamecntdown / 60) < values[i]) { continue; }
						switch (digit)
						{
						case 3:
							DrawGraph(410 + 40 * i, 21, cg_countNum[DrawCnt[i]], TRUE);
							break;
						case 2:
							if (gamecntdown / 60 <= 20) {
								//残り時間20秒以下で数字が黄色くなる
								DrawGraph(390 + 40 * i, 21, cg_countNum_y[DrawCnt[i]], TRUE);
							}
							else
							{
								DrawGraph(390 + 40 * i, 21, cg_countNum[DrawCnt[i]], TRUE);
							}
							break;
						case 1:
							//残り時間20秒以下で数字が黄色くなる
							DrawGraph(450, 21, cg_countNum_y[DrawCnt[i]], TRUE);
							break;
						}

					}
				}
				//部屋番号
				{
					int num = 0;
					switch (keyRoom) {
					case 6212: num = 0; break;
					case 1109: num = 1; break;
					case 1114: num = 2; break;
					case 311: num = 3; break;
					case 223: num = 4; break;
					case 4226: num = 5; break;
					case 3215: num = 6; break;
					case 2126: num = 7; break;
					case 0: num = 8; break;
					case 1225: num = 9; break;
					}
					//部屋番号背景
					//for (int i = 47; i > 0; i--)
					//{
					//	DrawGraph(608 - i * 3, i, cgRoomNumber[num], TRUE);
					//}
					DrawGraph(608, 47, cgRoomNumber[num], TRUE);
				}
				SetFontSize(Font);
			}
		}
		SetDrawArea(0, 0, 1920, 1080);
		DrawGraph(130, 1034, cgUI, TRUE);
	}

	return true;
}
