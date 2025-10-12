#include "Camera.h"

void Camera::Init(VECTOR charaPos) {
	// カメラの設定（わかりやすい位置に）
	_vPos = VGet(charaPos.x, charaPos.y + 600.f, charaPos.z - 800.f);
	//_cam._vPos = VGet(0, 1000.f, -800.f);
	_oldvPos = _vPos;
	_vTarget = VGet(charaPos.x, charaPos.y + 160, charaPos.z);
	//_cam._vTarget = VGet(0, 320, 0);
	_clipNear = 20.f;
	_clipFar = 50000.f;
}

void Camera::Spown(VECTOR charaPos) {
	// 位置
	_vPos = VGet(charaPos.x, charaPos.y + 600.f, charaPos.z - 800.f);
	_oldvPos = _vPos;
	// ターゲット位置
	_vTarget = VGet(charaPos.x, charaPos.y + 160, charaPos.z);
}

bool Camera::isHit(int handle, int frameCollision) {
	// 移動した先でコリジョン判定
	MV1_COLL_RESULT_POLY hitPoly;
	// カメラ位置から注視点への線分と当たり判定
	hitPoly = MV1CollCheck_Line(handle, frameCollision, _vTarget, _vPos);
	if (hitPoly.HitFlag) {
		_vPos = hitPoly.HitPosition;
		return true;
	}
	else {
		return false;
	}
}
