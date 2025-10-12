#include "AppFrame.h"
#include "../ApplicationMain.h"
#include "../ApplicationGlobal.h"
#include "RoomBase.h"

RoomBase::RoomBase() {
	se[0] = LoadSoundMem("res/sound/SE/electsound1.wav");
}

RoomBase::~RoomBase() {

}

void RoomBase::SetSpown(Chara& chara, Camera& cam) {
	for (int s = 0; s < rData._mapSteps; s++) {
		for (int i = 0; i < rData._mapSize; i++) {
			int mapType = rData.GetMapTip(s, i);
			int n = i / rData._mapW;
			//�L�����E�J�����X�|�[���ݒ�
			if (mapType == 6) {
				// �L����
				chara._vPos = VGet((i % rData._mapW) * rData._boxSize, 600, -n * rData._boxSize);
				chara._vResPos = VGet((i % rData._mapW) * rData._boxSize, 600, -n * rData._boxSize);
				// �J����
				cam._vPos = VGet(chara._vPos.x, chara._vPos.y + 600.f, chara._vPos.z - 800.f);
				cam._oldvPos = cam._vPos;
				cam._vTarget = VGet(chara._vPos.x, chara._vPos.y + 160, chara._vPos.z);
			}
		}
	}
}

// �}�b�v��������ԂɃ��Z�b�g
void RoomBase::Reset() {
	for (int i = 0; i < rData._objData.size(); i++) {
		if (rData._objData[i]._isMove == 1) {
			// �I�u�W�F�N�g��JSON�f�[�^�̃C���f�b�N�X�擾
			int indexObj = rData.GetIndexObj(rData._objData[i]._objType);
			// ���Z�b�g�f�[�^��JSON�f�[�^����擾
			// �ʒu���
			rData._objData[i]._vPos = rData.GetObjVPos(indexObj);
			rData._objData[i]._vPos.y += 250.f;
			// ���f���ʒu�Z�b�g
			MV1SetPosition(rData._objData[i]._handle, rData._objData[i]._vPos);
			// ���f���̃R���W�������X�V
			MV1RefreshCollInfo(rData._objData[i]._handle, rData._objData[i]._frameCollision);
			// �ړ������p
			rData._objData[i]._vDir = VGet(0.f, 0.f, -1.f);
			rData._objData[i]._vMove = VGet(0.f, 0.f, 0.f);
			rData._objData[i]._vToPos = rData._objData[i]._vPos;
		}
	}
}

void RoomBase::Process(Chara& chara, Camera& cam, VECTOR& v, VECTOR oldv) {

}

void RoomBase::CameraProcess(Camera& cam) {

}

void RoomBase::Render(VECTOR vPos, bool viewColl) {

}

void RoomBase::RenderObjectModel() {
	// �}�b�v���f���`��
	for (int i = 0; i < rData._objData.size(); i++) {
		MV1SetPosition(rData._objData[i]._handle, rData._objData[i]._vPos);
		//MV1DrawModel(_objData[i]._handle);
		if (rData._objData[i]._objType == 7) {
			if (goolDoor.GetVisible()) {
				MV1DrawModel(rData._objData[i]._handle);
			}
		}
		else {
			MV1DrawModel(rData._objData[i]._handle);
		}
	}
}
