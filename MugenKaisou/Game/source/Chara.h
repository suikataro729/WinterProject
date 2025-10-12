#include "appframe.h"

#include <string>
#include <vector>
#include <iostream>

// �v�Z�p�}�N��
#define	PI	(3.1415926535897932386f)
#define	DEG2RAD(x)			( ((x) / 180.0f ) * PI )
#define	RAD2DEG(x)			( ((x) * 180.0f ) / PI )

#define ANIMMAX	(6)		// 3D���f���A�j���[�V�����ő吔

// �L�����N�^
class Chara {
public:
	// 3D���f���`��p
	int _handle;
	
	VECTOR _vPos;	// �ʒu
	VECTOR _oldvPos;	// �ړ��O�̈ʒu
	VECTOR _vResPos;
	VECTOR _vDir;	// ����
	float _colSubY;	// �R���W�������莞��Y�␳(���ʒu�j
	enum class STATUS {
		NONE,
		WAIT,
		WALK,
		JUMP_START,
		JUMP_LOOP,
		JUMP_DOWN,
		_EOT_
	};
	STATUS _status;
	bool _isWait;
	bool _isDead;

	// 3D���f���A�j���[�V�����p
	int _handleAnim[ANIMMAX];	// �A�j���[�V����
	int _flgJumpAnim;			// �W�����v�A�j���[�V������ԃt���O�i0�F�J�n, 1�F���[�v, 2�F�~���j
	
	// �A�j���[�V���������Ǘ�
	class Animation {
	public:
		Animation() {}
		virtual ~Animation() {}

		int _attach_index;			// �A�^�b�`����A�j���[�V�����ԍ�
		float _total_time;			// ���Đ�����
		float _play_time;			// �Đ�����
		// ���[�V�����u�����h�p
		float _start_total_time;
		float _start_time;
		float _close_total_time;	// ��������
		float _close_time;			// ������
	};
	std::vector<Animation*> _vAnim;

	// 3D���f���R���W�����p�J�v�Z��
	float _collLower, _collUpper;	// �J�v�Z���̉��[�_�Ə�[�_��Y�␳
	float _CapsuleR;				// �J�v�Z���̕��i���a�j
	int CntHitCapsule;				// �J�v�Z���ƏՓ˂����|���S����
	std::vector<VECTOR> _vNormal;	// �J�v�Z���ƏՓ˂����|���S���̖@���x�N�g��
	VECTOR _vSlidePos;				// �Փˉ�����̈ړ���

	int _mapBoxType;	// �������Ă��鏰�̃^�C�v
	int _hitObjType;	// �������Ă���I�u�W�F�N�g�^�C�v

	//�d��
	float gravity;

	// �W�����v�p
	int jump_flg;		// �W�����v��ԃt���O�i0:�W�����v���Ă��Ȃ�, 1:�W�����v���Ă���j
	bool _isLanded;		// �������Ă邩
	float _jumpMove;	// �W�����v�ړ���

	// �o���ɓ���
	int _flgExit;

	void Init();					// ������
	void Spown(bool flgRespown);	// �X�|�[���ݒ�
	bool isHitWall(int handleMap, int frameMapCollision, bool flgCntNormal);	// �ǂƂ̓����蔻��
	bool isHitGround(int handleMap, int frameMapCollision);						// ���Ƃ̓����蔻��
	bool AvoidCollision(VECTOR v, int handle, int frameCollision);				// �ǂƂ̏Փˉ������
	void CheckStuck(int num);													// �L���������܂����m�F
	void ChangeStatus(VECTOR v);				// �L�����N�^�[�X�e�[�^�X�X�V
	void ChangeCharaAnim(STATUS oldStatus);		// �L�����N�^�[�A�j���[�V�����X�V
	void Jump();			// �W�����v����

	void Render();	// �`��
};
