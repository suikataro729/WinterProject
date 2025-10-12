#include "../ApplicationGlobal.h"
#include "RoomMuseum.h"
#include "../ModeRoomNumber.h"
#include "../ModeTalk.h"

RoomMuseum::RoomMuseum() {
	goolDoor.SetVisible(false);
	SaveRoot[5] = 1;
	for (int i = 0; i < _vEffekseer.size(); i++) {
		_vEffekseer.erase(_vEffekseer.begin() + i);
	}
	//タイムアップした時の会話はこの部屋以降出さない
	TalkFlg[3] = TRUE;
}

RoomMuseum::~RoomMuseum() {
	for (int i = 0; i < _vEffekseer.size(); i++) {
		_vEffekseer.erase(_vEffekseer.begin() + i);
	}
}

void RoomMuseum::CharaMove(Chara& chara, Camera& cam, VECTOR& v, VECTOR oldv) {
	
}

void RoomMuseum::Process(Chara& chara, Camera& cam, VECTOR& v, VECTOR oldv) {
	if (!TalkFlg[13])
	{
		TalkFlg[13] = true;
		ModeTalk* modetalk = new ModeTalk("res/jsonfile/TextData/museum1.json");
		// ModeGameより上のレイヤーにトークを登録する
		ModeServer::GetInstance()->Add(modetalk, 200, "talk");
	}

	_isCharaMove = true;	// キャラは移動したかのフラグ
	chara._mapBoxType = 0;
	chara._vNormal.clear();
	// マップとの衝突判定
	// 主人公の腰位置から下方向への直線
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

	// 謎解きクリア
	if ((CheckHitKey(KEY_INPUT_2)) && gPad[0].gXKey[XINPUT_BUTTON_B])
	{
		goolDoor.SetVisible(true);
		//_effekseer.AddEffect("res/Effect/doa/doa.efkefc", 0.0f, 0.0f, 1600.0f, 999999, 0.25f);
		//_vEffekseer.push_back(_effekseer);
	}

	// ゴール
	if (chara._hitObjType == 7) {
		if (goolDoor.GetVisible()) {
			chara._mapBoxType = 1;
			chara._flgExit = 1;
			RoomClear[5] = 1;
		}
	}

	for (int i = 0; i < _vEffekseer.size(); i++) {
		_vEffekseer[i].Process();
	}
}

void RoomMuseum::CameraProcess(Camera& cam) {
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

void RoomMuseum::Render(VECTOR vPos, bool viewColl) {
	// マップモデル描画
	RenderObjectModel();

	MV1SetPosition(rData._handleSkySphere, VGet(vPos.x, vPos.y, vPos.z + 200));
	MV1DrawModel(rData._handleSkySphere);

	//effekseer描画
	{
		_effekseer.Render();
	}
}
