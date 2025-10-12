#include "Camera.h"

void Camera::Init(VECTOR charaPos) {
	// �J�����̐ݒ�i�킩��₷���ʒu�Ɂj
	_vPos = VGet(charaPos.x, charaPos.y + 600.f, charaPos.z - 800.f);
	//_cam._vPos = VGet(0, 1000.f, -800.f);
	_oldvPos = _vPos;
	_vTarget = VGet(charaPos.x, charaPos.y + 160, charaPos.z);
	//_cam._vTarget = VGet(0, 320, 0);
	_clipNear = 20.f;
	_clipFar = 50000.f;
}

void Camera::Spown(VECTOR charaPos) {
	// �ʒu
	_vPos = VGet(charaPos.x, charaPos.y + 600.f, charaPos.z - 800.f);
	_oldvPos = _vPos;
	// �^�[�Q�b�g�ʒu
	_vTarget = VGet(charaPos.x, charaPos.y + 160, charaPos.z);
}

bool Camera::isHit(int handle, int frameCollision) {
	// �ړ�������ŃR���W��������
	MV1_COLL_RESULT_POLY hitPoly;
	// �J�����ʒu���璍���_�ւ̐����Ɠ����蔻��
	hitPoly = MV1CollCheck_Line(handle, frameCollision, _vTarget, _vPos);
	if (hitPoly.HitFlag) {
		_vPos = hitPoly.HitPosition;
		return true;
	}
	else {
		return false;
	}
}
