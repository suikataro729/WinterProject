#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ApplicationGlobal.h"
#include "ModeEffekseer.h"

bool ModeEffekseer::Initialize(float x, float y, float z) {
	if (!base::Initialize()) { return false; }
	_position_x = x;
	_position_y = y;
	_position_z = z;
	// エフェクトリソースを読み込む。
	// 読み込む時に大きさを指定する。
	_effectResourceHandle = LoadEffekseerEffect("res/Laser01.efkefc", 100.0f);

	return true;
}

bool ModeEffekseer::Terminate() {
	base::Terminate();

	// エフェクトリソースを削除する。
	DeleteEffekseerEffect(_effectResourceHandle);


	return true;
}


bool ModeEffekseer::Process() {
	base::Process();
	int key = ApplicationMain::GetInstance()->GetKey();
	int trg = ApplicationMain::GetInstance()->GetTrg();

	// このモードより下のレイヤーはProcess()を呼ばない
	//ModeServer::GetInstance()->SkipProcessUnderLayer();

	// モードカウンタを使って60fpsでエフェクトを生成
	if (GetModeCount() % 60 == 0) {
		// エフェクトを再生する。
		_playingEffectHandle = PlayEffekseer3DEffect(_effectResourceHandle);

		// エフェクトの位置をリセットする。
		SetPosPlayingEffekseer3DEffect(_playingEffectHandle, _position_x, 50.0f, 0.0f);
		SetRotationPlayingEffekseer3DEffect(_playingEffectHandle, 0.0f, 0.0f, 0.0f);
		SetScalePlayingEffekseer3DEffect(_playingEffectHandle, 1.0f, 1.0f, 1.0f);

	}

	// 再生中のエフェクトを移動する。
	// SetRotationPlayingEffekseer3DEffect
	// SetPosPlayingEffekseer3DEffect(_playingEffectHandle, 0, 50.f, 0);
	_position_x += 1.f;

	// Effekseerにより再生中のエフェクトを更新する。
	UpdateEffekseer3D();


	// 閉じる
	if (trg & PAD_INPUT_9) {
		// このモードを削除する
		ModeServer::GetInstance()->Del(this);
	}

	return true;
}

bool ModeEffekseer::Render() {
	base::Render();

	//SetDrawArea(0, 65, 1280 / 2, 720);

	// DXライブラリのカメラとEffekseerのカメラを同期する。
	Effekseer_Sync3DSetting();

	// Effekseerにより再生中のエフェクトを描画する。
	DrawEffekseer3D();

	//DrawFormatString(0, 300, GetColor(255, 255, 255), "えふぇくと");
	return true;
}
