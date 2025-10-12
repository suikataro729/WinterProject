#include "appframe.h"

#include <string>
#include <vector>
#include <iostream>

// カメラ
class Camera {
public:
	void Init(VECTOR charaPos);		// 初期化
	void Spown(VECTOR charaPos);	// スポーン設定
	bool isHit(int handle, int frameCollision);		//カメラの当たり判定

public:
	VECTOR	_vPos;					// 位置
	VECTOR	_oldvPos;
	VECTOR	_vTarget;				// 距離（注視点）
	float	_clipNear, _clipFar;	// クリップ
	float	_r;						// 当たり判定用の球の半径
};
