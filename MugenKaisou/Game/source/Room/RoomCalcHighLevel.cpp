#include "RoomCalcHighLevel.h"
#include "../ApplicationGlobal.h"
#include "../ModeRoomNumber.h"
#include "../ModeTalk.h"

RoomCalcHighLevel::RoomCalcHighLevel() {
	goolDoor.SetVisible(true);
	for (int i = 0; i < _vEffekseer.size(); i++) {
		_vEffekseer.erase(_vEffekseer.begin() + i);
	}
}

RoomCalcHighLevel::~RoomCalcHighLevel() {
	for (int i = 0; i < _vEffekseer.size(); i++) {
		_vEffekseer.erase(_vEffekseer.begin() + i);
	}
}

void RoomCalcHighLevel::Process(Chara& chara, Camera& cam, VECTOR& v, VECTOR oldv) {
	if (SaveRoot[7] == 0) {
		SaveRoot[7] = 1;
		//_effekseer.AddEffect("res/Effect/doa/doa.efkefc", 3000.0f, 0.0f, 0.0f, 999999, 0.25f);
		//_vEffekseer.push_back(_effekseer);
	}
	// 設置ブロック別操作
	if (chara.jump_flg == 0) {
		if (chara._mapBoxType == 2 || chara._mapBoxType == 3 ||
			chara._mapBoxType == 4 || chara._mapBoxType == 5) {
			// ベルトコンベア
			// キャラ移動
			chara._vPos = chara._oldvPos;
			beltConv.MovePos(chara._vPos, chara._mapBoxType, 32);
		}
		else if (chara._hitObjType == 7 && gChangeDoor == 0) {
			// ゴール
			chara._mapBoxType = 1;
			chara._flgExit = 1;
			RoomClear[7] = 1;
		}
		else if (chara._hitObjType == 7 && gChangeDoor == 1) {
			// ゴール
			chara._mapBoxType = 1;
			chara._flgExit = 1;
			gGlobal.keyNextRoom = 2126;
			RoomClear[7] = 1;
			//keyRoom = 2126;
		}
	}
	
	_isCharaMove = true;	// キャラは移動したかのフラグ
	chara._mapBoxType = 0;
	chara._hitObjType = 0;
	chara._vNormal.clear();
	// マップとの衝突判定
	for (int i = 0; i < rData._objData.size(); i++) {
		// 主人公の腰位置から下方向への直線
		if (chara.isHitGround(rData._objData[i]._handle, rData._objData[i]._frameCollision)) {
			// ベルトコンベア処理
			chara._mapBoxType = rData._objData[i]._mapType;
			// ジャンプさせる
			if (gPad[0].gXTrg[XINPUT_BUTTON_B] && chara.jump_flg == 0 && chara._mapBoxType == 1)
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
		if ((chara._mapBoxType == 2 || chara._mapBoxType == 3 ||
			chara._mapBoxType == 4 || chara._mapBoxType == 5)
			&& chara.jump_flg == 0) {
			// ベルトコンベア
			beltConv.MovePos(cam._vPos, chara._mapBoxType, 32);
			beltConv.MovePos(cam._vTarget, chara._mapBoxType, 32);
		}
		else {
			// 通常
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
	}
	else {
		v = oldv;
	}

	// ベルトコンベア上ではアニメーションをWAITにする
	if (chara._mapBoxType == 2 || chara._mapBoxType == 3 ||
		chara._mapBoxType == 4 || chara._mapBoxType == 5) {
		if (chara.jump_flg == 0) {
			chara._isWait = true;
		}
	}
	else { chara._isWait = false; }

	// ドア切り替え
	// デバッグ用
	if (gPad[0].gXTrg[XINPUT_BUTTON_X]) {
		if (gChangeDoor == 0) { gChangeDoor = 1; }
		else if (gChangeDoor == 1) { gChangeDoor = 0; }
	}
	goolDoor.ChangeDoor(gChangeDoor);
	for (int i = 0; i < _vEffekseer.size(); i++) {
		_vEffekseer[i].Process();
	}
}

void RoomCalcHighLevel::CameraProcess(Camera& cam) {
	// カメラの当たり判定
	bool flgHitCam = false;
	cam._oldvPos = cam._vPos;
	for (int i = 0; i < rData._objData.size(); i++) {
		if (cam.isHit(rData._objData[i]._handle, rData._objData[i]._frameCollision)) {
			flgHitCam = true;
		}
	}
}

void RoomCalcHighLevel::Render(VECTOR vPos, bool viewColl) {
	// マップモデル描画
	for (int i = 0; i < rData._objData.size(); i++) {
		MV1SetPosition(rData._objData[i]._handle, rData._objData[i]._vPos);
		//MV1DrawModel(_objData[i]._handle);
		if (rData._objData[i]._objType == 7 || rData._objData[i]._objType == 8) {
			if (rData._objData[i]._objType == goolDoor.GetDoorType()) {
				MV1DrawModel(rData._objData[i]._handle);
			}
		}
		else {
			MV1DrawModel(rData._objData[i]._handle);
		}
	}

	MV1SetPosition(rData._handleSkySphere, VGet(vPos.x, vPos.y, vPos.z + 200));
	MV1DrawModel(rData._handleSkySphere);

	//effekseer描画
	{
		_effekseer.Render();
	}
}
