
#include "appframe.h"

#include <string>
#include <vector>
#include <iostream>
#include "ModeMenu.h"
#include "ModeGameOver.h"
#include "ModeEffekseer.h"
#include "ModeWindow.h"
#include "ModeTalk.h"
#include "ModeRoomNumber.h"
#include "ModeEnding.h"
#include "Room/RoomServer.h"
#include "Sound.h"

// モード
class ModeGame : public ModeBase
{
	typedef ModeBase base;
public:
	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

	bool GetDebugViewColloion() { return _bViewCollision; }
	void SetDebugViewColloion(bool b) { _bViewCollision = b; }
	bool GetDebugViewInfo() { return _bViewInfo; }
	void SetDebugViewInfo(bool b) { _bViewInfo = b; }

protected:
	// インスタンス
	//-----------------------------------------------------------------
	Camera	_cam;		// カメラ
	Chara _chara;		// キャラクタ
	RoomServer* Rooms;	// 部屋（マップ）
	//エフェクト
	ClassEffekseer _effekseer;
	std::vector<ClassEffekseer> _vEffekseer;
	Sound _sound;		// サウンド（BGM・SE）

	Useful USEFUL;
	MyMath mymath;

	// 変数
	//-----------------------------------------------------------------
	int render_texture_handle = -1;		// テクスチャレンダリング用
	bool _flgMap;						// ステージ変更フラグ
	bool _flgPlay;						// 操作可能フラグ（ture：操作可能, false：操作不可能）
	bool _flgEffect;					// エフェクトフラグ
	int clear_cnt;						// クリア時カウント
	int cgUI;							// UI画像
	// 制限時間画像
	int cg_timebg;
	int cg_countNum[10];		//数字の画像
	int cg_countNum_y[10];		//黄色の数字
	int cgRoomNumber[10];		//部屋番号
	//音素材
	// 0:move 1:electsound1
	int se[4];

	// デバッグ用
	//-----------------------------------------------------------------
	bool _bViewCollision;	// コリジョン表示・非表示
	bool _bViewInfo;
}; 
