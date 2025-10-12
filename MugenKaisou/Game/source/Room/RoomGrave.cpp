#include "../ApplicationGlobal.h"
#include "RoomGrave.h"
#include "../ModeRoomNumber.h"
#include "../ModeTalk.h"
RoomGrave::RoomGrave() {
	goolDoor.SetVisible(true);

	flgEffect = true;
}

RoomGrave::~RoomGrave() {
	for (int i = 0; i < _vEffekseer.size(); i++) {
		_vEffekseer.erase(_vEffekseer.begin() + i);
	}
}

void RoomGrave::CharaMove(Chara& chara, Camera& cam, VECTOR& v, VECTOR oldv) {
	
}

void RoomGrave::Process(Chara& chara, Camera& cam, VECTOR& v, VECTOR oldv) {

	if (!SaveRoot[8]) {

		if (!TalkFlg[20]) {
			chengeRoom = 0;
			ModeTalk* modetalk = new ModeTalk("res/jsonfile/TextData/grave1.json");
			// ModeGameより上のレイヤーにトークを登録する
			ModeServer::GetInstance()->Add(modetalk, 200, "talk");
			TalkFlg[20] = TRUE;
		}

		if (chengeRoom == 1)
		{
			//わかっている
			SaveRoot[8] = 1;
			chengeRoom = 0;
		}
		if (chengeRoom == 2)
		{
			//わかっていない人
			gamecntdown = -100;
			chengeRoom = 0;
		}

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

	// ピザ出現
	if (gPizza) {

		//プレイヤーが0,0,0を向いていると足元にピザが出るから要修正

		// キャラクターの向きベクトルを取得
		VECTOR vUnitDir = VNorm(chara._vDir);
		// 向きベクトルがゼロベクトルの場合、デフォルトの向きを設定
		if (VSize(vUnitDir) == 0.0f) {
			vUnitDir = VGet(0.0f, 0.0f, -1.0f); // デフォルトで-Z方向を向く
		}
		// ピザの出現位置を計算
		float scale = 100.0f;
		VECTOR pizzaPos = VAdd(chara._vPos, VScale(vUnitDir, scale));
		// ピザを出現させる
		pizza.AddPizza(pizzaPos.x, pizzaPos.y + 300, pizzaPos.z);
		_vPizza.push_back(pizza);
		gPizza = false;
	}

	//ピザ落下処理
	if (_vPizza.size() > 0) {
		for (int i = 0; i < _vPizza.size(); i++) {
			VECTOR pOldvPos = _vPizza[i]._vPos;
			if (_vPizza[i]._mapBoxType != 0 && _vPizza[i]._mapBoxType != 1 && _vPizza[i]._mapBoxType != 10) {
				_vPizza[i]._vPos = pOldvPos;
			}
			_vPizza[i].gravity += 0.6;
			for (int n = 0; n < rData._objData.size(); n++)
			{
				//_vPizza[i].Process(_objData[n]._handle, _objData[n]._frameCollision);
				// 移動した先でコリジョン判定
				MV1_COLL_RESULT_POLY hitPoly;
				hitPoly = MV1CollCheck_Line(rData._objData[0]._handle, rData._objData[0]._frameCollision,
					VAdd(_vPizza[i]._vPos, VGet(0, 100, 0)), VAdd(_vPizza[i]._vPos, VGet(0, -99999.f, 0)));
				if (hitPoly.HitFlag) {
					// 当たった
					if (_vPizza[i]._vPos.y <= hitPoly.HitPosition.y) {
						_vPizza[i].gravity = 0;
						// 当たったY位置をキャラ座標にする
						_vPizza[i]._vPos.y = hitPoly.HitPosition.y;
						_vPizza[i]._mapBoxType = rData._objData[n]._mapType;

						// 表示時間カウント
						_vPizza[i]._cntView++;
					}
				}
				//お供え物
				hitPoly = MV1CollCheck_Line(rData._objData[1]._handle, rData._objData[1]._frameCollision,
					VAdd(_vPizza[i]._vPos, VGet(0, 100, 0)), VAdd(_vPizza[i]._vPos, VGet(0, -99999.f, 0)));
				if (hitPoly.HitFlag) {
					// ゴール
					if (_vPizza[i]._vPos.y <= hitPoly.HitPosition.y) {
						chara._mapBoxType = 7;
						keyRoom = 0;
						chara._flgExit = 1;
						RoomClear[8] = 1;
						break;
					}
				}
			}
			//重力の反映
			_vPizza[i]._vPos.y -= _vPizza[i].gravity;

			// 消去処理
			if (_vPizza[i]._vPos.y < -1000 || _vPizza[i]._cntView > 1000) {
				_vPizza.erase(_vPizza.begin() + i);
			}
		}
	}

	if (flgEffect) {
		_effekseer.AddEffect("res/Effect/sakura/sakura.efkefc", chara._vPos.x, chara._vPos.y, chara._vPos.z, 999999);
		_vEffekseer.push_back(_effekseer);
		flgEffect = 0;
	}
	for (int i = 0; i < _vEffekseer.size(); i++) {
		_vEffekseer[i].Process();
	}
}

void RoomGrave::CameraProcess(Camera& cam) {
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

void RoomGrave::Render(VECTOR vPos, bool viewColl) {
	// マップモデル描画
	RenderObjectModel();

	MV1SetPosition(rData._handleSkySphere, VGet(vPos.x, vPos.y, vPos.z + 200));
	MV1DrawModel(rData._handleSkySphere);

	//effekseer描画
	{
		_effekseer.Render();
	}

	// ピザ
	if (_vPizza.size() > 0) {
		for (int i = 0; i < _vPizza.size(); i++) {
			_vPizza[i].Render();
		}
	}
}
