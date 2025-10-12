#include "RoomCalcLabyrinth.h"
#include "../ApplicationGlobal.h"
#include "../ModeRoomNumber.h"
#include "../ModeTalk.h"

RoomCalcLabyrinth::RoomCalcLabyrinth() {
	goolDoor.SetVisible(true);
	//難しくない迷路
	for (int i = 0; i < _vEffekseer.size(); i++) {
		_vEffekseer.erase(_vEffekseer.begin() + i);
	}
}

RoomCalcLabyrinth::~RoomCalcLabyrinth() {
	for (int i = 0; i < _vEffekseer.size(); i++) {
		_vEffekseer.erase(_vEffekseer.begin() + i);
	}
}

void RoomCalcLabyrinth::CharaMove(Chara& chara, Camera& cam, VECTOR& v, VECTOR oldv) {

}

void RoomCalcLabyrinth::Process(Chara& chara, Camera& cam, VECTOR& v, VECTOR oldv) {
	if (SaveRoot[2] == 0)
	{
		SaveRoot[2] = 1;
		ModeTalk* modetalk = new ModeTalk("res/jsonfile/TextData/calculation1.json");
		// ModeGameより上のレイヤーにトークを登録する
		ModeServer::GetInstance()->Add(modetalk, 200, "talk");
		//_effekseer.AddEffect("res/Effect/doa/doa.efkefc", 10500.0f, 0.0f, -5750.0f, 999999, 0.25f);
		//_vEffekseer.push_back(_effekseer);
	}
	
	_isCharaMove = true;	// キャラは移動したかのフラグ
	chara._mapBoxType = 0;
	chara._hitObjType = 0;
	chara._vNormal.clear();
	// マップとの衝突判定
	for (int i = 0; i < rData._objData.size(); i++) {
		// 主人公の腰位置から下方向への直線
		if (chara.isHitGround(rData._objData[i]._handle, rData._objData[i]._frameCollision)) {
			chara._mapBoxType = rData._objData[i]._mapType;
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

	// ゴール
	if (chara._hitObjType == 7) {
		chara._mapBoxType = 1;
		chara._flgExit = 1;
		if (keyRoom == 311) {
			RoomClear[2] = 1;
			//ModeTalk* modetalk = new ModeTalk("res/jsonfile/TextData/calculation2.json");
			//// ModeGameより上のレイヤーにトークを登録する
			//ModeServer::GetInstance()->Add(modetalk, 200, "talk");
		}
	}

	for (int i = 0; i < _vEffekseer.size(); i++) {
		_vEffekseer[i].Process();
	}
}

void RoomCalcLabyrinth::CameraProcess(Camera& cam) {
	// カメラの当たり判定
	bool flgHitCam = false;
	cam._oldvPos = cam._vPos;
	for (int i = 0; i < rData._objData.size(); i++) {
		if (cam.isHit(rData._objData[i]._handle, rData._objData[i]._frameCollision)) {
			flgHitCam = true;
		}
	}
}

void RoomCalcLabyrinth::Render(VECTOR vPos, bool viewColl) {
	// マップモデル描画
	RenderObjectModel();

	MV1SetPosition(rData._handleSkySphere, VGet(vPos.x, vPos.y, vPos.z + 200));
	MV1DrawModel(rData._handleSkySphere);

	//effekseer描画
	{
		_effekseer.Render();
	}
}
