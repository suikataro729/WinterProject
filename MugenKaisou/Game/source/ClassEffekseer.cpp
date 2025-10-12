#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ApplicationGlobal.h"
#include "ClassEffekseer.h"

ClassEffekseer::ClassEffekseer() {
	_effectResourceHandle = -1;
	breakFlag = 1;
	_position_x = 0;
	_position_y = 0;
	_position_z = 0;
}

ClassEffekseer::~ClassEffekseer() {
	// �G�t�F�N�g���\�[�X���폜����B
	StopEffekseer3DEffect(_effectResourceHandle);
	DeleteEffekseerEffect(_effectResourceHandle);
}
void ClassEffekseer::AddEffect(const TCHAR* EffectHandle, float x, float y, float z,int _EffectCntMax ,float Rotate) {
	_effectResourceHandle = LoadEffekseerEffect(EffectHandle, 100.0f);
	_position_x = x;
	_position_y = y;
	_position_z = z;
	EffectCnt = 0;
	EffectCntMax = _EffectCntMax;
	_Rotate = Rotate;
}


void ClassEffekseer::Process() {

    if (EffectCnt % EffectCntMax == 0) {
        // �G�t�F�N�g���Đ�����B
        _playingEffectHandle = PlayEffekseer3DEffect(_effectResourceHandle);

        // �G�t�F�N�g�̈ʒu�����Z�b�g����B
        SetPosPlayingEffekseer3DEffect(_playingEffectHandle, _position_x, _position_y, _position_z);
        SetRotationPlayingEffekseer3DEffect(_playingEffectHandle, 0.0f, _Rotate, 0.0f);
		breakFlag = false;
    }

    EffectCnt++;
}

void ClassEffekseer::Render() {

	// DX���C�u�����̃J������Effekseer�̃J�����𓯊�����B
	Effekseer_Sync3DSetting();

	// Effekseer�ɂ��Đ����̃G�t�F�N�g��`�悷��B
	DrawEffekseer3D();
}
