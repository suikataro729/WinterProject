#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ApplicationGlobal.h"
#include "ModeEffekseer.h"

bool ModeEffekseer::Initialize(float x, float y, float z) {
	if (!base::Initialize()) { return false; }
	_position_x = x;
	_position_y = y;
	_position_z = z;
	// �G�t�F�N�g���\�[�X��ǂݍ��ށB
	// �ǂݍ��ގ��ɑ傫�����w�肷��B
	_effectResourceHandle = LoadEffekseerEffect("res/Laser01.efkefc", 100.0f);

	return true;
}

bool ModeEffekseer::Terminate() {
	base::Terminate();

	// �G�t�F�N�g���\�[�X���폜����B
	DeleteEffekseerEffect(_effectResourceHandle);


	return true;
}


bool ModeEffekseer::Process() {
	base::Process();
	int key = ApplicationMain::GetInstance()->GetKey();
	int trg = ApplicationMain::GetInstance()->GetTrg();

	// ���̃��[�h��艺�̃��C���[��Process()���Ă΂Ȃ�
	//ModeServer::GetInstance()->SkipProcessUnderLayer();

	// ���[�h�J�E���^���g����60fps�ŃG�t�F�N�g�𐶐�
	if (GetModeCount() % 60 == 0) {
		// �G�t�F�N�g���Đ�����B
		_playingEffectHandle = PlayEffekseer3DEffect(_effectResourceHandle);

		// �G�t�F�N�g�̈ʒu�����Z�b�g����B
		SetPosPlayingEffekseer3DEffect(_playingEffectHandle, _position_x, 50.0f, 0.0f);
		SetRotationPlayingEffekseer3DEffect(_playingEffectHandle, 0.0f, 0.0f, 0.0f);
		SetScalePlayingEffekseer3DEffect(_playingEffectHandle, 1.0f, 1.0f, 1.0f);

	}

	// �Đ����̃G�t�F�N�g���ړ�����B
	// SetRotationPlayingEffekseer3DEffect
	// SetPosPlayingEffekseer3DEffect(_playingEffectHandle, 0, 50.f, 0);
	_position_x += 1.f;

	// Effekseer�ɂ��Đ����̃G�t�F�N�g���X�V����B
	UpdateEffekseer3D();


	// ����
	if (trg & PAD_INPUT_9) {
		// ���̃��[�h���폜����
		ModeServer::GetInstance()->Del(this);
	}

	return true;
}

bool ModeEffekseer::Render() {
	base::Render();

	//SetDrawArea(0, 65, 1280 / 2, 720);

	// DX���C�u�����̃J������Effekseer�̃J�����𓯊�����B
	Effekseer_Sync3DSetting();

	// Effekseer�ɂ��Đ����̃G�t�F�N�g��`�悷��B
	DrawEffekseer3D();

	//DrawFormatString(0, 300, GetColor(255, 255, 255), "���ӂ�����");
	return true;
}
