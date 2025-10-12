#include "AppFrame.h"
#include "Pizza.h"

// ピザ
Pizza::Pizza() {
	_handle = MV1LoadModel("res/3Dart/pizza/piza_wani_syusei.mv1");
	// 位置,向きの初期化
	_vPos = VGet(0, 500, 0);
	_vDir = VGet(0, 0, -1);		// キャラモデルはデフォルトで-Z方向を向いている
	gravity = 0.0f;
	_cntView = 0;
}
Pizza::~Pizza() {
}

void Pizza::AddPizza(float x, float y, float z) {
	_vPos = VGet(x, y + 200, z);
}

void Pizza::Process(int _handleMap, int _frameMapCollision) {

	gravity += 0.6f;

	// 移動した先でコリジョン判定
	MV1_COLL_RESULT_POLY hitPoly;
	hitPoly = MV1CollCheck_Line(_handleMap, _frameMapCollision,
		VGet(0, 10, 0), VAdd(_vPos, VGet(0, -99999.f, 0)));
	if (hitPoly.HitFlag) {
		// 当たった
		if (_vPos.y <= hitPoly.HitPosition.y) {
			gravity = 0;
			// 当たったY位置をキャラ座標にする
			_vPos.y = hitPoly.HitPosition.y;
		}
	}
	//重力の反映
	_vPos.y -= gravity;
}

void Pizza::Render() {
	// 位置
	MV1SetPosition(_handle, _vPos);
	// 描画
	MV1DrawModel(_handle);
}
