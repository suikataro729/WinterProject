#include "AppFrame.h"
#include "../ApplicationMain.h"
#include "../ApplicationGlobal.h"
#include "RoomBase.h"

RoomBase::RoomBase() {
	se[0] = LoadSoundMem("res/sound/SE/electsound1.wav");
}

RoomBase::~RoomBase() {

}

void RoomBase::SetSpown(Chara& chara, Camera& cam) {
	for (int s = 0; s < rData._mapSteps; s++) {
		for (int i = 0; i < rData._mapSize; i++) {
			int mapType = rData.GetMapTip(s, i);
			int n = i / rData._mapW;
			//キャラ・カメラスポーン設定
			if (mapType == 6) {
				// キャラ
				chara._vPos = VGet((i % rData._mapW) * rData._boxSize, 600, -n * rData._boxSize);
				chara._vResPos = VGet((i % rData._mapW) * rData._boxSize, 600, -n * rData._boxSize);
				// カメラ
				cam._vPos = VGet(chara._vPos.x, chara._vPos.y + 600.f, chara._vPos.z - 800.f);
				cam._oldvPos = cam._vPos;
				cam._vTarget = VGet(chara._vPos.x, chara._vPos.y + 160, chara._vPos.z);
			}
		}
	}
}

// マップを初期状態にリセット
void RoomBase::Reset() {
	for (int i = 0; i < rData._objData.size(); i++) {
		if (rData._objData[i]._isMove == 1) {
			// オブジェクトのJSONデータのインデックス取得
			int indexObj = rData.GetIndexObj(rData._objData[i]._objType);
			// リセットデータをJSONデータから取得
			// 位置情報
			rData._objData[i]._vPos = rData.GetObjVPos(indexObj);
			rData._objData[i]._vPos.y += 250.f;
			// モデル位置セット
			MV1SetPosition(rData._objData[i]._handle, rData._objData[i]._vPos);
			// モデルのコリジョン情報更新
			MV1RefreshCollInfo(rData._objData[i]._handle, rData._objData[i]._frameCollision);
			// 移動処理用
			rData._objData[i]._vDir = VGet(0.f, 0.f, -1.f);
			rData._objData[i]._vMove = VGet(0.f, 0.f, 0.f);
			rData._objData[i]._vToPos = rData._objData[i]._vPos;
		}
	}
}

void RoomBase::Process(Chara& chara, Camera& cam, VECTOR& v, VECTOR oldv) {

}

void RoomBase::CameraProcess(Camera& cam) {

}

void RoomBase::Render(VECTOR vPos, bool viewColl) {

}

void RoomBase::RenderObjectModel() {
	// マップモデル描画
	for (int i = 0; i < rData._objData.size(); i++) {
		MV1SetPosition(rData._objData[i]._handle, rData._objData[i]._vPos);
		//MV1DrawModel(_objData[i]._handle);
		if (rData._objData[i]._objType == 7) {
			if (goolDoor.GetVisible()) {
				MV1DrawModel(rData._objData[i]._handle);
			}
		}
		else {
			MV1DrawModel(rData._objData[i]._handle);
		}
	}
}
