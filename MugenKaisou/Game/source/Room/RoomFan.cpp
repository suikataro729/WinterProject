#include "../ApplicationGlobal.h"
#include "RoomFan.h"
#include "../ModeRoomNumber.h"
#include "../ModeTalk.h"

RoomFan::RoomFan() {
	goolDoor.SetVisible(true);

	FanCnt = 0;
}

RoomFan::~RoomFan() {
	for (int i = 0; i < _vEffekseer.size(); i++) {
		_vEffekseer.erase(_vEffekseer.begin() + i);
	}
}

void RoomFan::CharaMove(Chara& chara, Camera& cam, VECTOR& v, VECTOR oldv) {

}

void RoomFan::Process(Chara& chara, Camera& cam, VECTOR& v, VECTOR oldv) {
	// 設置ブロック別操作
	bool beltcam = false;
	
	if (SaveRoot[6] == 0)
	{
		SaveRoot[6] = 1;
		ModeTalk* modetalk = new ModeTalk("res/jsonfile/TextData/program1.json");
		// ModeGameより上のレイヤーにトークを登録する
		ModeServer::GetInstance()->Add(modetalk, 200, "talk");
		//_effekseer.AddEffect("res/Effect/doa/doa.efkefc", 1000.0f, 0.0f, -500.0f, 500, 0.25f);
		//_vEffekseer.push_back(_effekseer);
	}
	//if (chara.jump_flg == 0)
	{
		if (chara._mapBoxType == 2 || chara._mapBoxType == 3 ||
			chara._mapBoxType == 4 || chara._mapBoxType == 5) {
			// ベルトコンベア
			beltcam = true;
			// キャラ移動
			beltConv.MovePos(chara._vPos, chara._mapBoxType, FanSpeed * 160);
		}
		if (chara.jump_flg == 0) {
			if (chara._hitObjType == 7) {
				// ゴール
				chara._mapBoxType = 1;
				chara._flgExit = 1;
				RoomClear[6] = 1;
			}
		}
	}

	_isCharaMove = true;	// キャラは移動したかのフラグ
	//chara._mapBoxType = 0;
	chara._hitObjType = 0;
	chara._vNormal.clear();
	// マップとの衝突判定
	for (int i = 0; i < rData._objData.size(); i++) {
		// 主人公の腰位置から下方向への直線
		if (chara.isHitGround(rData._objData[i]._handle, rData._objData[i]._frameCollision)) {
			// ベルトコンベア処理
			if (chara.jump_flg == 0) {
				chara._mapBoxType = rData._objData[i]._mapType;
			}
			// ジャンプさせる
			if (gPad[0].gXTrg[XINPUT_BUTTON_B] && chara.jump_flg == 0)
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
			// 通常
			cam._vPos = VAdd(cam._vPos, v);
			cam._vTarget = VAdd(cam._vTarget, v);

			if (chara._mapBoxType == 2 || chara._mapBoxType == 3 ||
				chara._mapBoxType == 4 || chara._mapBoxType == 5) {
				// ベルトコンベア
				beltConv.MovePos(cam._vPos, chara._mapBoxType, FanSpeed * 160);
				beltConv.MovePos(cam._vTarget, chara._mapBoxType, FanSpeed * 160);
			}
		}
	}
	else {
		v = oldv;
	}

	//ファン関連
	{
		FanCnt += FanSpeed;
		for (int i = 0; i < rData._objData.size(); i++) {
			if (rData._objData[i]._objType == 9) {
				MV1SetRotationXYZ(rData._objData[i]._handle, VGet(0.0, 0.0, FanCnt));
				MV1RefreshCollInfo(rData._objData[i]._handle, rData._objData[i]._frameCollision);
			}
		}
		// キャラがファンに当たったか
		if (chara._hitObjType == 9) {
			// 当たった場合、リスポーン
			respown_flg = true;
		}
	}

	for (int i = 0; i < _vEffekseer.size(); i++) {
		_vEffekseer[i].Process();
	}
}

void RoomFan::CameraProcess(Camera& cam) {
	// カメラの当たり判定
	bool flgHitCam = false;
	cam._oldvPos = cam._vPos;
	for (int i = 0; i < rData._objData.size(); i++) {
		if (cam.isHit(rData._objData[i]._handle, rData._objData[i]._frameCollision)) {
			flgHitCam = true;
		}
	}
}

void RoomFan::Render(VECTOR vPos, bool viewColl) {
	MV1SetPosition(rData._handleSkySphere, VGet(vPos.x, vPos.y, vPos.z + 200));
	MV1DrawModel(rData._handleSkySphere);

	// マップモデル描画
	RenderObjectModel();

	//effekseer描画
	{
		_effekseer.Render();
	}
}
