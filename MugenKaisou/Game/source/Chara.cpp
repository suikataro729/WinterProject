#include "AppFrame.h"
#include "Chara.h"
#include "ApplicationGlobal.h"

void Chara::Init() {
	// ���f���f�[�^�̃��[�h�i�e�N�X�`�����ǂݍ��܂��j
	//_handle = MV1LoadModel("res/SDChar/Riine/Model/Riine.mv1");
	_handle = MV1LoadModel("res/SDChar/Riine/Animation/Riine_model.mv1");

	// �L�������f���̊g��
	MV1SetScale(_handle, VGet(3.0f, 3.0f, 3.0f));

	// �A�j���[�V�������f���̃��[�h
	_handleAnim[0] = MV1LoadModel("res/SDChar/Riine/Animation/RiineAnim_aidle.mv1");
	_handleAnim[1] = MV1LoadModel("res/SDChar/Riine/Animation/RiineAnim_run.mv1");
	_handleAnim[2] = MV1LoadModel("res/SDChar/Riine/Animation/RiineAnim_jump_up2.mv1");
	_handleAnim[3] = MV1LoadModel("res/SDChar/Riine/Animation/RiineAnim_jump_middle2.mv1");
	_handleAnim[4] = MV1LoadModel("res/SDChar/Riine/Animation/RiineAnim_jump_down2.mv1");
	_handleAnim[5] = MV1LoadModel("res/SDChar/Riine/Animation/RiineAnim_death.mv1");
	// �A�j���[�V����������
	_vAnim.clear();
	_flgJumpAnim = 0;

	// �X�e�[�^�X���u�����v�ɐݒ�
	_status = STATUS::NONE;
	_isWait = false;
	_isDead = false;
	gChara_Dead = false;
	_isLanded = false;
	_jumpMove = 0.f;
	// �ʒu,�����̏�����
	_vPos = VGet(0, 600, -1000);
	_oldvPos = _vPos;
	_vResPos = VGet(0, 600, -1000);
	_vDir = VGet(0, 0, -1);		// �L�������f���̓f�t�H���g��-Z�����������Ă���
	// �������Ă��鏰�̃^�C�v
	_mapBoxType = 1;
	// �������Ă���I�u�W�F�N�g�^�C�v
	_hitObjType = 0;

	// ���ʒu�̐ݒ�
	_colSubY = 40.f;

	// �J�v�Z��
	_CapsuleR = 70.f;
	CntHitCapsule = 0;
	_collLower = 90.f;
	_collUpper = 240.f;
	_vNormal.clear();
	_vSlidePos = VGet(0.f, 0.f, 0.f);

	// ���̑�
	gravity = 0;
	jump_flg = 0;
	_flgExit = 0;
}

void Chara::Spown(bool flgRespown) {
	// �ʒu
	if (flgRespown) { _vPos = _vResPos; }
	else {
		_vPos = VGet(0.f, 600.f, -1000.f);
		_vResPos = _vPos;
	}
	// �J�v�Z��
	_CapsuleR = 70.f;
	// �������Ă��鏰��I�u�W�F�N�g�̃^�C�v
	_mapBoxType = 1;
	_hitObjType = 0;
	// ���S�t���O
	_isDead = false;
}

bool Chara::isHitWall(int handleMap, int frameMapCollision, bool flgCntNormal) {
	CntHitCapsule = 0;
	// �ړ�������ŃR���W��������
	MV1_COLL_RESULT_POLY_DIM hitPolyDim;
	// ��l���i�J�v�Z���j�ƕǂ̓����蔻��
	hitPolyDim = MV1CollCheck_Capsule(handleMap, frameMapCollision,
		VAdd(_vPos, VGet(0, _collLower, 0)), VAdd(_vPos, VGet(0, _collUpper, 0)), _CapsuleR);
	if (hitPolyDim.HitNum > 0) {
		CntHitCapsule = hitPolyDim.HitNum;
		if (flgCntNormal) {
			// �L�����Ɠ��������|���S���̖@���x�N�g��
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
	// �ړ�������ŃR���W��������
	MV1_COLL_RESULT_POLY hitPoly;
	// ��l���̍��ʒu���牺�����ւ̒���
	hitPoly = MV1CollCheck_Line(handleMap, frameMapCollision,
		VAdd(_vPos, VGet(0, _colSubY, 0)), VAdd(_vPos, VGet(0, -99999.f, 0)));
	if (hitPoly.HitFlag) {
		// ��������
		if (_vPos.y <= hitPoly.HitPosition.y) {
			gravity = 0;
			jump_flg = 0;
			_flgJumpAnim = 0;
			// ��������Y�ʒu���L�������W�ɂ���
			_vPos.y = hitPoly.HitPosition.y;
			// �L�����𒅒n��Ԃɂ��A�W�����v�ړ��ʂ�0�ɂ���
			_isLanded = true;
			_jumpMove = 0.f;
		}

		return true;
	}
	else {
		return false;
	}
}

// �ǂƂ̏Փˉ������
bool Chara::AvoidCollision(VECTOR v, int handle, int frameCollision) {
	_vSlidePos = VGet(0.f, 0.f, 0.f);
	if (_vNormal.size() != 0) {
		for (int i = 0; i < _vNormal.size(); i++) {
			if (_vNormal[i].y < 0.5f && _vNormal[i].y > -0.5f) {
				// �Փˉ�����̈ړ��ʂ��v�Z
				_vSlidePos = VCross(v, _vNormal[i]);
				_vSlidePos = VCross(_vNormal[i], _vSlidePos);
				_vSlidePos.y = 0.f;
				_vPos = VAdd(_vPos, _vSlidePos);

				// ����ŕǂƏՓ˂��邩
				if (isHitWall(handle, frameCollision, false)) {
					// �ǂɓ��������B
					// ���̍��W�ɖ߂�
					_vPos = _oldvPos;
					_vSlidePos = VGet(0.f, 0.f, 0.f);
				}
				else {
					// ������Ȃ������B
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

// �L�����N�^�[�X�e�[�^�X�X�V
void Chara::ChangeStatus(VECTOR v) {
	if (VSize(v) > 0.f) {		// �ړ����Ă��Ȃ����͖������邽��
		_vDir = v;
		_status = STATUS::WALK;
	}
	else {
		_status = STATUS::WAIT;
	}

	// �ʏ�E�ҋ@
	if (_isWait) {
		_status = STATUS::WAIT;
	}

	// �W�����v
	if (jump_flg) {
		if (_flgJumpAnim == 0) {
			// �W�����v�J�n
			_status = STATUS::JUMP_START;
		}
		else if (_flgJumpAnim == 1) {
			// �W�����v���[�v
			_status = STATUS::JUMP_LOOP;
		}
	}

	if (jump_flg && _flgJumpAnim == 2) {
		// �W�����v���n�E�~��
		_status = STATUS::JUMP_DOWN;
	}
}

// �L�����N�^�[�A�j���[�V�����X�V
void Chara::ChangeCharaAnim(STATUS oldStatus) {
	// �X�e�[�^�X���ς���Ă��Ȃ����H
	if (oldStatus != _status) {
		// ���ɃA�^�b�`����Ă���A�j���[�V�����ɁA�����Ԃ�ݒ肷��
		for (auto iteAnim = _vAnim.begin(); iteAnim != _vAnim.end(); ++iteAnim) {
			if ((*iteAnim)->_close_time == 0.f) {
				(*iteAnim)->_close_time = 6.f;		// �u�����h����t���[����
				(*iteAnim)->_close_total_time = (*iteAnim)->_close_time;
			}
		}
		
		// �V�����A�j���[�V������ǉ�
		Animation* anim = new Animation();
		// �X�e�[�^�X�ɍ��킹�ăA�j���[�V�����̃A�^�b�`
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
		// �A�^�b�`�����A�j���[�V�����̑��Đ����Ԃ��擾����
		anim->_total_time = MV1GetAttachAnimTotalTime(_handle, anim->_attach_index);
		// �Đ����Ԃ�������
		anim->_play_time = 0.0f;
		anim->_close_time = 0.0f;
		anim->_start_time = 0.0f;
		anim->_start_total_time = 6.f;
		// �A�j���[�V�����ǉ�
		_vAnim.push_back(anim);
	}

	// �A�j���[�V�������ԏ���
	for (auto iteAnim = _vAnim.begin(); iteAnim != _vAnim.end();) {
		if ((*iteAnim)->_close_time == 0.f) {
			// �Đ����Ԃ�i�߂�
			(*iteAnim)->_play_time += 0.5;
			(*iteAnim)->_start_time += 1.f;
			// �Đ����Ԃ��A�j���[�V�����̑��Đ����ԂɒB������Đ����Ԃ��O�ɖ߂�
			if ((*iteAnim)->_play_time >= (*iteAnim)->_total_time) {
				(*iteAnim)->_play_time = 0.0f;
				
				// �W�����v�J�n���̃A�j���[�V�����̏ꍇ�A�W�����v���[�v�̃A�j���[�V�����ɕύX
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
			// �u�����h����ύX����
			MV1SetAttachAnimBlendRate(_handle, (*iteAnim)->_attach_index, (*iteAnim)->_start_time / (*iteAnim)->_start_total_time);
		}
		else {
			// �����Ԃ����炷
			(*iteAnim)->_close_time -= 1.f;
			// �����Ԃ��I��������H
			if ((*iteAnim)->_close_time <= 0.f) {
				// �A�j���[�V�������A�^�b�`����Ă�����A�f�^�b�`����
				MV1DetachAnim(_handle, (*iteAnim)->_attach_index);
				// ���̃A�j���[�V�������폜
				delete (*iteAnim);
				iteAnim = _vAnim.erase(iteAnim);
				continue;
			}
			// �u�����h����ύX����
			MV1SetAttachAnimBlendRate(_handle, (*iteAnim)->_attach_index, (*iteAnim)->_close_time / (*iteAnim)->_close_total_time);
		}
		++iteAnim;
	}
}

// �W�����v����
void Chara::Jump() {
	_isLanded = false;
	_vPos.y += _jumpMove;
}

void Chara::Render() {
	// �Đ����Ԃ��Z�b�g����
	for (auto iteAnim = _vAnim.begin(); iteAnim != _vAnim.end(); ++iteAnim) {
		MV1SetAttachAnimTime(_handle, (*iteAnim)->_attach_index, (*iteAnim)->_play_time);
	}

	// �ʒu
	MV1SetPosition(_handle, _vPos);
	// ��������Y����]���Z�o
	VECTOR vRot = { 0,0,0 };
	vRot.y = atan2(_vDir.x * -1, _vDir.z * -1);		// ���f�����W���łǂ���������Ă��邩�Ŏ����ς��(�����-z�������Ă���ꍇ)
	MV1SetRotationXYZ(_handle, vRot);
	// �`��
	MV1DrawModel(_handle);
}
