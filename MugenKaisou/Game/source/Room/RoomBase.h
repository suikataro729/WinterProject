#pragma once

#include "appframe.h"

#include <string>
#include <vector>
#include <iostream>
#include "../Chara.h"
#include "../Camera.h"
#include "../ShiftBlock.h"
#include "../BeltConveyor.h"
#include "../Pizza.h"
#include "../Door.h"
#include "../ClassEffekseer.h"

class RoomBase
{
public:
	RoomBase();				// インストラクタ
	virtual ~RoomBase();	// デストラクタ

	virtual void SetSpown(Chara& chara, Camera& cam);		// キャラ・カメラのマップ対応初期化
	virtual void Reset();									// マップを初期状態にリセット
	virtual void Process(Chara& chara, Camera& cam, VECTOR& v, VECTOR oldv);	// 処理
	virtual void CameraProcess(Camera& cam);									// カメラ処理
	virtual void Render(VECTOR vPos, bool viewColl);							// 描画

	void RenderObjectModel();		// オブジェクトモデルの描画
public:
	bool _isCharaMove;	// キャラは移動したかのフラグ

	// ドア
	Door goolDoor;

	//エフェクト
	ClassEffekseer _effekseer;
	std::vector<ClassEffekseer> _vEffekseer;

	MyMath mymath;

	//音
	// 0:electsound1
	int se[4];
};
