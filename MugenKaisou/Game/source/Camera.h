#include "appframe.h"

#include <string>
#include <vector>
#include <iostream>

// �J����
class Camera {
public:
	void Init(VECTOR charaPos);		// ������
	void Spown(VECTOR charaPos);	// �X�|�[���ݒ�
	bool isHit(int handle, int frameCollision);		//�J�����̓����蔻��

public:
	VECTOR	_vPos;					// �ʒu
	VECTOR	_oldvPos;
	VECTOR	_vTarget;				// �����i�����_�j
	float	_clipNear, _clipFar;	// �N���b�v
	float	_r;						// �����蔻��p�̋��̔��a
};
