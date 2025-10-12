#pragma once

#include "appframe.h"

#include <string>
#include <vector>
#include <iostream>
#include "../Chara.h"
#include "../Camera.h"
#include "../ShiftBlock.h"
#include "../BeltConveyor.h"
#include "../Pizza.h"
#include "../Door.h"
#include "../ClassEffekseer.h"

class RoomBase
{
public:
	RoomBase();				// �C���X�g���N�^
	virtual ~RoomBase();	// �f�X�g���N�^

	virtual void SetSpown(Chara& chara, Camera& cam);		// �L�����E�J�����̃}�b�v�Ή�������
	virtual void Reset();									// �}�b�v��������ԂɃ��Z�b�g
	virtual void Process(Chara& chara, Camera& cam, VECTOR& v, VECTOR oldv);	// ����
	virtual void CameraProcess(Camera& cam);									// �J��������
	virtual void Render(VECTOR vPos, bool viewColl);							// �`��

	void RenderObjectModel();		// �I�u�W�F�N�g���f���̕`��
public:
	bool _isCharaMove;	// �L�����͈ړ��������̃t���O

	// �h�A
	Door goolDoor;

	//�G�t�F�N�g
	ClassEffekseer _effekseer;
	std::vector<ClassEffekseer> _vEffekseer;

	MyMath mymath;

	//��
	// 0:electsound1
	int se[4];
};
