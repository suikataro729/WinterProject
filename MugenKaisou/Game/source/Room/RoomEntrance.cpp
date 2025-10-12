#include "../ApplicationGlobal.h"
#include "RoomEntrance.h"
#include "../ModeRoomNumber.h"
#include "../ModeTalk.h"
#include "../ModeEnding.h"
#include "../ModeWindow.h"

RoomEntrance::RoomEntrance() {
	SaveRoot[0] = 1;
	TalkFlg[12] = TRUE;
	goolDoor.SetVisible(false);
	flgEffect = true;
	for (int i = 0; i < _vEffekseer.size(); i++) {
		_vEffekseer.erase(_vEffekseer.begin() + i);
	}
}

RoomEntrance::~RoomEntrance() {
	for (int i = 0; i < _vEffekseer.size(); i++) {
		_vEffekseer.erase(_vEffekseer.begin() + i);
	}
}

void RoomEntrance::CharaMove(Chara& chara, Camera& cam, VECTOR& v, VECTOR oldv) {
	
}

void RoomEntrance::Process(Chara& chara, Camera& cam, VECTOR& v, VECTOR oldv) {
	if (RoomClear[0] == 0 && TalkFlg[12])
	{
		TalkFlg[12] = FALSE;
		ModeTalk* modetalk = new ModeTalk("res/jsonfile/TextData/entrance1.json");
		// ModeGameより上のレイヤーにトークを登録する
		ModeServer::GetInstance()->Add(modetalk, 200, "talk");
	}
	else if (RoomClear[0] == 1 && TalkFlg[12])
	{
		TalkFlg[12] = FALSE;
		ModeTalk* modetalk = new ModeTalk("res/jsonfile/TextData/entranceend.json");
		// ModeGameより上のレイヤーにトークを登録する
		ModeServer::GetInstance()->Add(modetalk, 200, "talk");
		ModeEnding* modeEnding = new ModeEnding();
		// ModeGameより上のレイヤーにトークを登録する
		ModeServer::GetInstance()->Add(modeEnding, 150, "ending");
	}
	_isCharaMove = true;	// キャラは移動したかのフラグ
	chara._mapBoxType = 0;
	chara._vNormal.clear();
	// マップとの衝突判定
	for (int i = 0; i < rData._objData.size(); i++) {
		// 主人公の腰位置から下方向への直線
		if (chara.isHitGround(rData._objData[i]._handle, rData._objData[i]._frameCollision)) {
			chara._mapBoxType = 1;
			// ジャンプさせる
			if (gPad[0].gXTrg[XINPUT_BUTTON_B] && chara.jump_flg == 0 && chara._mapBoxType != 0)
			{
				chara.jump_flg = 1;
				chara._jumpMove = 20.f;
			}
		}
		// 主人公（カプセル）と壁の当たり判定
		if (chara.isHitWall(rData._objData[i]._handle, rData._objData[i]._frameCollision, true)) {
			// 壁に当たった。
			chara._hitObjType = rData._objData[i]._objType;
			// 元の座標に戻す
			chara._vPos = chara._oldvPos;
			// 衝突回避
			if (chara.AvoidCollision(v, rData._objData[i]._handle, rData._objData[i]._frameCollision)) {
				_isCharaMove = true;
			}
			else {
				_isCharaMove = false;
			}
		}
	}

	if (_isCharaMove) {
		// カメラ移動
		if (VSize(chara._vSlidePos) != 0.f) {
			// 衝突を回避した。
			cam._vPos = VAdd(cam._vPos, chara._vSlidePos);
			cam._vTarget = VAdd(cam._vTarget, chara._vSlidePos);
			chara._vSlidePos = VGet(0.f, 0.f, 0.f);
		}
		else {
			// 壁に当たらなかった。
			cam._vPos = VAdd(cam._vPos, v);
			cam._vTarget = VAdd(cam._vTarget, v);
		}
	}
	else {
		v = oldv;
	}

	if (TalkFlg[10] && !TalkFlg[11]) {
		PlaySoundMem(se[0], DX_PLAYTYPE_BACK, TRUE);
		TalkFlg[11] = TRUE;
		FullScreenFlg = FALSE;
		ModeWindow* modewindow = new ModeWindow();
		// ModeGameより上のレイヤーにウィンドウを登録する
		ModeServer::GetInstance()->Add(modewindow, 100, "window");
		ModeTalk* modetalk = new ModeTalk("res/jsonfile/TextData/entrance3.json");
		// ModeGameより上のレイヤーにトークを登録する
		ModeServer::GetInstance()->Add(modetalk, 200, "talk");

		//_effekseer.AddEffect("res/Effect/doa/doa.efkefc", 0.0f, 1000.0f, 3200.0f, 999999, 0.25f);
		//_vEffekseer.push_back(_effekseer);
	}

	// タブレット獲得
	if (mymath.IsHitPointBox(chara._vPos, 0.0f, 0.0f, 100, 100) && !TalkFlg[10]) {

		ModeTalk* modetalk = new ModeTalk("res/jsonfile/TextData/entrance2.json");
		// ModeGameより上のレイヤーにトークを登録する
		ModeServer::GetInstance()->Add(modetalk, 200, "talk");
		TalkFlg[10] = TRUE;
		goolDoor.SetVisible(true);
		for (int i = 0; i < _vEffekseer.size(); i++) {
			_vEffekseer.erase(_vEffekseer.begin() + i);
		}
	}

	// ゴール
	if (chara._hitObjType == 7) {
		chara._mapBoxType = 1;
		chara._flgExit = 1;
		RoomClear[0] = 1;
	}

	if (flgEffect) {
		for (int i = 0; i < 3; i++) {
			_effekseer.AddEffect("res/Effect/hikari/sekibannohikari.efkefc", 0.0f, 0.0f, 0.0f, 60);
			_vEffekseer.push_back(_effekseer);
		}
		flgEffect = 0;
	}
	for (int i = 0; i < _vEffekseer.size(); i++) {
		_vEffekseer[i].Process();
	}
}

void RoomEntrance::CameraProcess(Camera& cam) {
	// カメラの当たり判定
	bool flgHitCam = false;
	cam._oldvPos = cam._vPos;
	// マップオブジェクト
	for (int i = 0; i < rData._objData.size(); i++) {
		if (cam.isHit(rData._objData[i]._handle, rData._objData[i]._frameCollision)) {
			flgHitCam = true;
		}
	}
}

void RoomEntrance::Render(VECTOR vPos, bool viewColl) {
	// マップモデル描画
	RenderObjectModel();
	//effekseer描画
	{
		_effekseer.Render();
	}
	//MV1SetPosition(rData._handleSkySphere, VGet(vPos.x, vPos.y, vPos.z + 200));
	//MV1DrawModel(rData._handleSkySphere);
}
