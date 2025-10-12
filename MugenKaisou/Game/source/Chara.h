#include "appframe.h"

#include <string>
#include <vector>
#include <iostream>

// 計算用マクロ
#define	PI	(3.1415926535897932386f)
#define	DEG2RAD(x)			( ((x) / 180.0f ) * PI )
#define	RAD2DEG(x)			( ((x) * 180.0f ) / PI )

#define ANIMMAX	(6)		// 3Dモデルアニメーション最大数

// キャラクタ
class Chara {
public:
	// 3Dモデル描画用
	int _handle;
	
	VECTOR _vPos;	// 位置
	VECTOR _oldvPos;	// 移動前の位置
	VECTOR _vResPos;
	VECTOR _vDir;	// 向き
	float _colSubY;	// コリジョン判定時のY補正(腰位置）
	enum class STATUS {
		NONE,
		WAIT,
		WALK,
		JUMP_START,
		JUMP_LOOP,
		JUMP_DOWN,
		_EOT_
	};
	STATUS _status;
	bool _isWait;
	bool _isDead;

	// 3Dモデルアニメーション用
	int _handleAnim[ANIMMAX];	// アニメーション
	int _flgJumpAnim;			// ジャンプアニメーション状態フラグ（0：開始, 1：ループ, 2：降下）
	
	// アニメーション複数管理
	class Animation {
	public:
		Animation() {}
		virtual ~Animation() {}

		int _attach_index;			// アタッチするアニメーション番号
		float _total_time;			// 総再生時間
		float _play_time;			// 再生時間
		// モーションブレンド用
		float _start_total_time;
		float _start_time;
		float _close_total_time;	// 総閉じ時間
		float _close_time;			// 閉じ時間
	};
	std::vector<Animation*> _vAnim;

	// 3Dモデルコリジョン用カプセル
	float _collLower, _collUpper;	// カプセルの下端点と上端点のY補正
	float _CapsuleR;				// カプセルの幅（半径）
	int CntHitCapsule;				// カプセルと衝突したポリゴン数
	std::vector<VECTOR> _vNormal;	// カプセルと衝突したポリゴンの法線ベクトル
	VECTOR _vSlidePos;				// 衝突回避時の移動量

	int _mapBoxType;	// 当たっている床のタイプ
	int _hitObjType;	// 当たっているオブジェクトタイプ

	//重力
	float gravity;

	// ジャンプ用
	int jump_flg;		// ジャンプ状態フラグ（0:ジャンプしていない, 1:ジャンプしている）
	bool _isLanded;		// 着陸してるか
	float _jumpMove;	// ジャンプ移動量

	// 出口に到着
	int _flgExit;

	void Init();					// 初期化
	void Spown(bool flgRespown);	// スポーン設定
	bool isHitWall(int handleMap, int frameMapCollision, bool flgCntNormal);	// 壁との当たり判定
	bool isHitGround(int handleMap, int frameMapCollision);						// 床との当たり判定
	bool AvoidCollision(VECTOR v, int handle, int frameCollision);				// 壁との衝突回避処理
	void CheckStuck(int num);													// キャラが挟まった確認
	void ChangeStatus(VECTOR v);				// キャラクターステータス更新
	void ChangeCharaAnim(STATUS oldStatus);		// キャラクターアニメーション更新
	void Jump();			// ジャンプ処理

	void Render();	// 描画
};
