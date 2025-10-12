#pragma once

#include <list>
#include "ModeBase.h"


class	ModeServer
{
	typedef	std::list<ModeBase*>		lstModeBase;

public:
	ModeServer();
	virtual	~ModeServer();
	static ModeServer		*_lpInstance;
	static ModeServer*GetInstance() { return (ModeServer*)_lpInstance; }

	int Add(ModeBase *mode, int layer, const char *name);		// �o�^�͂��邪�A��x���C�����񂳂Ȃ��Ƃ����Ȃ�
	int Del(ModeBase *mode);		// �폜�\��
	ModeBase *Get(int uid);
	ModeBase *Get(const char *name);
	int GetId(ModeBase* mode);
	int GetId(const char *name);
	const char *GetName(ModeBase* mode);
	const char *GetName(int uid);
	void Clear();
	int	LayerTop() { return INT32_MAX; }

	static bool modeSort(const ModeBase *x, const ModeBase *y) {
		return x->_layer < y->_layer;
	}

	int ProcessInit();	// �v���Z�X���񂷂��߂̏�����
	int Process();		// ���C���[�̏�̕����珈��
	int ProcessFinish();		// �v���Z�X���񂵂���̌�n��

	int RenderInit();		// �`����񂷂��߂̏�����
	int Render();		// ���C���[�̉��̕����珈��
	int RenderFinish();		// �`����񂵂���̌�n��

	int SkipProcessUnderLayer();		// ��Process�ŁA���������Ă��郌�C���[��艺�̃��C���[�́A�������Ă΂Ȃ�
	int SkipRenderUnderLayer();			// ��Process�ŁA���������Ă��郌�C���[��艺�̃��C���[�́A�`����Ă΂Ȃ�
	int PauseProcessUnderLayer();		// ��Process�ŁA���������Ă��郌�C���[��艺�̃��C���[�́A���Ԍo�߂��~�߂�

private:
	int Release(ModeBase *mode);		// �폜��delete
	bool IsDelRegist(ModeBase *mode);	// �폜�\�񂳂�Ă��邩�H
	bool IsAdd(ModeBase *mode);		// ���X�g�ɂ��邩�H


public:


private:
	lstModeBase		_vMode;			// ���[�h���X�g
	int				_uid_count;		// uid�J�E���^
	lstModeBase		_vModeAdd;		// �ǉ��\��
	lstModeBase		_vModeDel;		// �폜�\��

	ModeBase		*_nowMode;		// ���݌Ăяo�����̃��[�h
	ModeBase		*_skipProcessMode;	// ���̃��[�h��艺��Process���Ă΂Ȃ�
	ModeBase		*_skipRenderMode;	// ���̃��[�h��艺��Render���Ă΂Ȃ�
	ModeBase		*_pauseProcessMode;	// ���̃��[�h��艺��Process���Ɏ��Ԍo�߂������Ȃ�

};
