#include "appframe.h"

#include <string>
#include <vector>


// ���[�h
class ModeEffekseer : public ModeBase
{
	typedef ModeBase base;
public:
	virtual bool Initialize(float x, float y, float z);
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

protected:
	VECTOR _vPos;	// �ʒu
	int		_effectResourceHandle;		// �G�t�F�N�g�t�@�C�������[�h����n���h��
	int		_playingEffectHandle;		// ���[�h�����G�t�F�N�g�t�@�C������A�G�t�F�N�g�𐶐���������

	// �G�t�F�N�g�ʒu
	float	_position_x = 0.0f;
	float	_position_y = 0.0f;
	float	_position_z = 0.0f;
};
