#include "AppFrame.h"
#include "Chara.h"
#include "ApplicationGlobal.h"

void Chara::Init() {
	// モデルデータのロード（テクスチャも読み込まれる）
	//_handle = MV1LoadModel("res/SDChar/Riine/Model/Riine.mv1");
	_handle = MV1LoadModel("res/SDChar/Riine/Animation/Riine_model.mv1");

	// キャラモデルの拡大
	MV1SetScale(_handle, VGet(3.0f, 3.0f, 3.0f));

	// アニメーションモデルのロード
	_handleAnim[0] = MV1LoadModel("res/SDChar/Riine/Animation/RiineAnim_aidle.mv1");
	_handleAnim[1] = MV1LoadModel("res/SDChar/Riine/Animation/RiineAnim_run.mv1");
	_handleAnim[2] = MV1LoadModel("res/SDChar/Riine/Animation/RiineAnim_jump_up2.mv1");
	_handleAnim[3] = MV1LoadModel("res/SDChar/Riine/Animation/RiineAnim_jump_middle2.mv1");
	_handleAnim[4] = MV1LoadModel("res/SDChar/Riine/Animation/RiineAnim_jump_down2.mv1");
	_handleAnim[5] = MV1LoadModel("res/SDChar/Riine/Animation/RiineAnim_death.mv1");
	// アニメーション初期化
	_vAnim.clear();
	_flgJumpAnim = 0;

	// ステータスを「無し」に設定
	_status = STATUS::NONE;
	_isWait = false;
	_isDead = false;
	gChara_Dead = false;
	_isLanded = false;
	_jumpMove = 0.f;
	// 位置,向きの初期化
	_vPos = VGet(0, 600, -1000);
	_oldvPos = _vPos;
	_vResPos = VGet(0, 600, -1000);
	_vDir = VGet(0, 0, -1);		// キャラモデルはデフォルトで-Z方向を向いている
	// 当たっている床のタイプ
	_mapBoxType = 1;
	// 当たっているオブジェクトタイプ
	_hitObjType = 0;

	// 腰位置の設定
	_colSubY = 40.f;

	// カプセル
	_CapsuleR = 70.f;
	CntHitCapsule = 0;
	_collLower = 90.f;
	_collUpper = 240.f;
	_vNormal.clear();
	_vSlidePos = VGet(0.f, 0.f, 0.f);

	// その他
	gravity = 0;
	jump_flg = 0;
	_flgExit = 0;
}

void Chara::Spown(bool flgRespown) {
	// 位置
	if (flgRespown) { _vPos = _vResPos; }
	else {
		_vPos = VGet(0.f, 600.f, -1000.f);
		_vResPos = _vPos;
	}
	// カプセル
	_CapsuleR = 70.f;
	// 当たっている床やオブジェクトのタイプ
	_mapBoxType = 1;
	_hitObjType = 0;
	// 死亡フラグ
	_isDead = false;
}

bool Chara::isHitWall(int handleMap, int frameMapCollision, bool flgCntNormal) {
	CntHitCapsule = 0;
	// 移動した先でコリジョン判定
	MV1_COLL_RESULT_POLY_DIM hitPolyDim;
	// 主人公（カプセル）と壁の当たり判定
	hitPolyDim = MV1CollCheck_Capsule(handleMap, frameMapCollision,
		VAdd(_vPos, VGet(0, _collLower, 0)), VAdd(_vPos, VGet(0, _collUpper, 0)), _CapsuleR);
	if (hitPolyDim.HitNum > 0) {
		CntHitCapsule = hitPolyDim.HitNum;
		if (flgCntNormal) {
			// キャラと当たったポリゴンの法線ベクトル
			for (int i = 0; i < CntHitCapsule; i++) {
				_vNormal.push_back(hitPolyDim.Dim[i].Normal);
			}
		}

		return true;
	}
	else {
		return false;
	}
}

bool Chara::isHitGround(int handleMap, int frameMapCollision) {
	// 移動した先でコリジョン判定
	MV1_COLL_RESULT_POLY hitPoly;
	// 主人公の腰位置から下方向への直線
	hitPoly = MV1CollCheck_Line(handleMap, frameMapCollision,
		VAdd(_vPos, VGet(0, _colSubY, 0)), VAdd(_vPos, VGet(0, -99999.f, 0)));
	if (hitPoly.HitFlag) {
		// 当たった
		if (_vPos.y <= hitPoly.HitPosition.y) {
			gravity = 0;
			jump_flg = 0;
			_flgJumpAnim = 0;
			// 当たったY位置をキャラ座標にする
			_vPos.y = hitPoly.HitPosition.y;
			// キャラを着地状態にし、ジャンプ移動量を0にする
			_isLanded = true;
			_jumpMove = 0.f;
		}

		return true;
	}
	else {
		return false;
	}
}

// 壁との衝突回避処理
bool Chara::AvoidCollision(VECTOR v, int handle, int frameCollision) {
	_vSlidePos = VGet(0.f, 0.f, 0.f);
	if (_vNormal.size() != 0) {
		for (int i = 0; i < _vNormal.size(); i++) {
			if (_vNormal[i].y < 0.5f && _vNormal[i].y > -0.5f) {
				// 衝突回避時の移動量を計算
				_vSlidePos = VCross(v, _vNormal[i]);
				_vSlidePos = VCross(_vNormal[i], _vSlidePos);
				_vSlidePos.y = 0.f;
				_vPos = VAdd(_vPos, _vSlidePos);

				// 回避先で壁と衝突するか
				if (isHitWall(handle, frameCollision, false)) {
					// 壁に当たった。
					// 元の座標に戻す
					_vPos = _oldvPos;
					_vSlidePos = VGet(0.f, 0.f, 0.f);
				}
				else {
					// 当たらなかった。
					return true;
				}
			}
		}
	}
	return false;
}

void Chara::CheckStuck(int num) {
	for (int i = 0; i < num; i++) {
		for (int j = num; j < _vNormal.size(); j++) {
			float sx = _vNormal[j].x - _vNormal[i].x;
			float sz = _vNormal[j].z - _vNormal[i].z;
			float rad = atan2(sz, sx);
			if (cos(rad) == -1) {
				_isDead = true;
				break;
			}
		}
	}

	_vNormal.erase(_vNormal.begin() + num, _vNormal.begin() + _vNormal.size());
}

// キャラクターステータス更新
void Chara::ChangeStatus(VECTOR v) {
	if (VSize(v) > 0.f) {		// 移動していない時は無視するため
		_vDir = v;
		_status = STATUS::WALK;
	}
	else {
		_status = STATUS::WAIT;
	}

	// 通常・待機
	if (_isWait) {
		_status = STATUS::WAIT;
	}

	// ジャンプ
	if (jump_flg) {
		if (_flgJumpAnim == 0) {
			// ジャンプ開始
			_status = STATUS::JUMP_START;
		}
		else if (_flgJumpAnim == 1) {
			// ジャンプループ
			_status = STATUS::JUMP_LOOP;
		}
	}

	if (jump_flg && _flgJumpAnim == 2) {
		// ジャンプ着地・降下
		_status = STATUS::JUMP_DOWN;
	}
}

// キャラクターアニメーション更新
void Chara::ChangeCharaAnim(STATUS oldStatus) {
	// ステータスが変わっていないか？
	if (oldStatus != _status) {
		// 既にアタッチされているアニメーションに、閉じ時間を設定する
		for (auto iteAnim = _vAnim.begin(); iteAnim != _vAnim.end(); ++iteAnim) {
			if ((*iteAnim)->_close_time == 0.f) {
				(*iteAnim)->_close_time = 6.f;		// ブレンドするフレーム数
				(*iteAnim)->_close_total_time = (*iteAnim)->_close_time;
			}
		}
		
		// 新しいアニメーションを追加
		Animation* anim = new Animation();
		// ステータスに合わせてアニメーションのアタッチ
		switch (_status) {
		case STATUS::WAIT:
			anim->_attach_index = MV1AttachAnim(_handle, MV1GetAnimIndex(_handleAnim[0], "aidle-new"), _handleAnim[0], FALSE);
			break;
		case STATUS::WALK:
			anim->_attach_index = MV1AttachAnim(_handle, MV1GetAnimIndex(_handleAnim[1], "run"), _handleAnim[1], FALSE);
			break;
		case STATUS::JUMP_START:
			anim->_attach_index = MV1AttachAnim(_handle, MV1GetAnimIndex(_handleAnim[2], "jump up"), _handleAnim[2], FALSE);
			break;
		case STATUS::JUMP_LOOP:
			anim->_attach_index = MV1AttachAnim(_handle, MV1GetAnimIndex(_handleAnim[3], "jump middle"), _handleAnim[3], FALSE);
			break;
		case STATUS::JUMP_DOWN:
			anim->_attach_index = MV1AttachAnim(_handle, MV1GetAnimIndex(_handleAnim[4], "jump down"), _handleAnim[4], FALSE);
			break;
		}
		// アタッチしたアニメーションの総再生時間を取得する
		anim->_total_time = MV1GetAttachAnimTotalTime(_handle, anim->_attach_index);
		// 再生時間を初期化
		anim->_play_time = 0.0f;
		anim->_close_time = 0.0f;
		anim->_start_time = 0.0f;
		anim->_start_total_time = 6.f;
		// アニメーション追加
		_vAnim.push_back(anim);
	}

	// アニメーション時間処理
	for (auto iteAnim = _vAnim.begin(); iteAnim != _vAnim.end();) {
		if ((*iteAnim)->_close_time == 0.f) {
			// 再生時間を進める
			(*iteAnim)->_play_time += 0.5;
			(*iteAnim)->_start_time += 1.f;
			// 再生時間がアニメーションの総再生時間に達したら再生時間を０に戻す
			if ((*iteAnim)->_play_time >= (*iteAnim)->_total_time) {
				(*iteAnim)->_play_time = 0.0f;
				
				// ジャンプ開始時のアニメーションの場合、ジャンプループのアニメーションに変更
				if (_status == STATUS::JUMP_START) {
					_flgJumpAnim = 1;
					(*iteAnim)->_play_time = (*iteAnim)->_total_time;
				}

				if (_status == STATUS::JUMP_DOWN) {
					(*iteAnim)->_play_time = (*iteAnim)->_total_time;
				}
			}
			if ((*iteAnim)->_start_time >= (*iteAnim)->_start_total_time) {
				(*iteAnim)->_start_time = (*iteAnim)->_start_total_time;
			}
			// ブレンド率を変更する
			MV1SetAttachAnimBlendRate(_handle, (*iteAnim)->_attach_index, (*iteAnim)->_start_time / (*iteAnim)->_start_total_time);
		}
		else {
			// 閉じ時間を減らす
			(*iteAnim)->_close_time -= 1.f;
			// 閉じ時間が終わったか？
			if ((*iteAnim)->_close_time <= 0.f) {
				// アニメーションがアタッチされていたら、デタッチする
				MV1DetachAnim(_handle, (*iteAnim)->_attach_index);
				// このアニメーションを削除
				delete (*iteAnim);
				iteAnim = _vAnim.erase(iteAnim);
				continue;
			}
			// ブレンド率を変更する
			MV1SetAttachAnimBlendRate(_handle, (*iteAnim)->_attach_index, (*iteAnim)->_close_time / (*iteAnim)->_close_total_time);
		}
		++iteAnim;
	}
}

// ジャンプ処理
void Chara::Jump() {
	_isLanded = false;
	_vPos.y += _jumpMove;
}

void Chara::Render() {
	// 再生時間をセットする
	for (auto iteAnim = _vAnim.begin(); iteAnim != _vAnim.end(); ++iteAnim) {
		MV1SetAttachAnimTime(_handle, (*iteAnim)->_attach_index, (*iteAnim)->_play_time);
	}

	// 位置
	MV1SetPosition(_handle, _vPos);
	// 向きからY軸回転を算出
	VECTOR vRot = { 0,0,0 };
	vRot.y = atan2(_vDir.x * -1, _vDir.z * -1);		// モデルが標準でどちらを向いているかで式が変わる(これは-zを向いている場合)
	MV1SetRotationXYZ(_handle, vRot);
	// 描画
	MV1DrawModel(_handle);
}
