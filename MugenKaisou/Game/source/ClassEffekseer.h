#include "appframe.h"

#include <string>
#include <vector>


// ���[�h
class ClassEffekseer
{
public:
	ClassEffekseer();
	~ClassEffekseer();
	void AddEffect(const TCHAR* EffectHandle,float x, float y, float z,int EffectCntMax, float Rotate = 0.0f);
	void Process();
	void Render();


	int EffectCnt;
	int EffectCntMax;
	int		breakFlag = 0;

	// �G�t�F�N�g�ʒu
	float	_position_x = 0.0f;
	float	_position_y = 0.0f;
	float	_position_z = 0.0f;
protected:
	VECTOR _vPos;	// �ʒu
	int		_effectResourceHandle;		// �G�t�F�N�g�t�@�C�������[�h����n���h��
	int		_playingEffectHandle;		// ���[�h�����G�t�F�N�g�t�@�C������A�G�t�F�N�g�𐶐���������
	
	float _Rotate;

};
