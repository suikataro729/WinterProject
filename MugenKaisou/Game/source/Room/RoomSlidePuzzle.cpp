#include "RoomSlidePuzzle.h"
#include "../ApplicationGlobal.h"
#include "../ModeRoomNumber.h"
#include "../ModeTalk.h"

RoomSlidePuzzle::RoomSlidePuzzle() {
	goolDoor.SetVisible(true);
	for (int i = 0; i < _vEffekseer.size(); i++) {
		_vEffekseer.erase(_vEffekseer.begin() + i);
	}
}

RoomSlidePuzzle::~RoomSlidePuzzle() {
	for (int i = 0; i < _vEffekseer.size(); i++) {
		_vEffekseer.erase(_vEffekseer.begin() + i);
	}
}

void RoomSlidePuzzle::Process(Chara& chara, Camera& cam, VECTOR& v, VECTOR oldv) {
	if (keyRoom == 1109 && SaveRoot[1] == 0) {
		SaveRoot[1] = 1;
		ModeTalk* modetalk = new ModeTalk("res/jsonfile/TextData/slidepuzzle2.json");
		// ModeGame����̃��C���[�Ƀg�[�N��o�^����
		ModeServer::GetInstance()->Add(modetalk, 200, "talk");
		//_effekseer.AddEffect("res/Effect/doa/doa.efkefc", 9500.0f, 500.0f, -500.0f, 999999, 0.25f);
		//_vEffekseer.push_back(_effekseer);
	}
	else if (keyRoom == 4226 && SaveRoot[4] == 0) {

		if (!TalkFlg[19]) {
			chengeRoom = 0;
			ModeTalk* modetalk = new ModeTalk("res/jsonfile/TextData/meteorite1.json");
			// ModeGame����̃��C���[�Ƀg�[�N��o�^����
			ModeServer::GetInstance()->Add(modetalk, 200, "talk");
			TalkFlg[19] = TRUE;
		}

		if(chengeRoom == 1)
		{
			//�킩���Ă���
			SaveRoot[4] = 1;
			chengeRoom = 0;
		}
		if(chengeRoom == 2)
		{
			//�킩���Ă��Ȃ��l
			gamecntdown = -100;
			chengeRoom = 0;
		}
		//_effekseer.AddEffect("res/Effect/doa/doa.efkefc", 1500.0f, 0.0f, -2500.0f, 999999, 0.25f);
		//_vEffekseer.push_back(_effekseer);
	}
	
	// �I�u�W�F�N�g�ړ��i�X���C�h�j����
	for (int i = 0; i < rData._objData.size(); i++) {
		if (rData._objData[i]._isMove == 1) {
			if (rData._objData[i]._mapType == gMovemap_num) {
				_shiftBlock.SetShiftData(gMoverot, rData._objData[i]._vToPos, rData._objData[i]._vMove);
				gMovemap_num = 0;
			}
			_shiftBlock.Shift(rData._objData[i]._vPos, rData._objData[i]._vToPos, rData._objData[i]._vMove);
			MV1SetPosition(rData._objData[i]._handle, rData._objData[i]._vPos);
			MV1RefreshCollInfo(rData._objData[i]._handle, rData._objData[i]._frameCollision);
		}
	}

	_isCharaMove = true;	// �L�����͈ړ��������̃t���O
	chara._mapBoxType = 0;
	chara._hitObjType = 0;
	chara._vNormal.clear();
	// �Փ˔���
	for (int i = 0; i < rData._objData.size(); i++) {
		// ��l���̍��ʒu���牺�����ւ̒���
		if (chara.isHitGround(rData._objData[i]._handle, rData._objData[i]._frameCollision)) {
			chara._mapBoxType = rData._objData[i]._mapType;
			// �W�����v������
			if (gPad[0].gXTrg[XINPUT_BUTTON_B] && chara.jump_flg == 0 && chara._mapBoxType != 0)
			{
				chara.jump_flg = 1;
				chara._jumpMove = 20.f;
			}
		}
		// ��l���i�J�v�Z���j�ƕǂ̓����蔻��
		if (chara.isHitWall(rData._objData[i]._handle, rData._objData[i]._frameCollision, true)) {
			// �ǂɓ��������B
			chara._hitObjType = rData._objData[i]._objType;
			// ���̍��W�ɖ߂�
			chara._vPos = chara._oldvPos;
			_isCharaMove = false;
			if (rData._objData[i]._isMove == 1 && VSize(rData._objData[i]._vMove) > 0.f) {
				// ���������I�u�W�F�N�g���ړ����Ă��镪�A�L�������ړ���������
				// �L�����ړ�
				chara._vPos = VAdd(chara._vPos, rData._objData[i]._vMove);
				// �J�����ړ�
				cam._vPos = VAdd(cam._vPos, rData._objData[i]._vMove);
				cam._vTarget = VAdd(cam._vTarget, rData._objData[i]._vMove);
			}

			// �Փˉ��
			if (chara.AvoidCollision(v, rData._objData[i]._handle, rData._objData[i]._frameCollision)) {
				_isCharaMove = true;
			}
			else {
				_isCharaMove = false;
			}

			// �L���������܂邩�ǂ���
			if (rData._objData[i]._objType != 1) {
				int newHitNormal = chara._vNormal.size();
				for (int j = 0; j < rData._objData.size(); j++) {
					if (j != i) {
						if (rData._objData[j]._objType != 1) {
							if (chara.isHitWall(rData._objData[j]._handle, rData._objData[j]._frameCollision, true)) {
								//chara._isDead = true;
								//break;
								chara.CheckStuck(newHitNormal);
							}
						}
					}
				}
			}
		}
	}

	if (_isCharaMove) {
		// �J�����ړ�
		if (VSize(chara._vSlidePos) != 0.f) {
			// �Փ˂���������B
			cam._vPos = VAdd(cam._vPos, chara._vSlidePos);
			cam._vTarget = VAdd(cam._vTarget, chara._vSlidePos);
			chara._vSlidePos = VGet(0.f, 0.f, 0.f);
		}
		else {
			// �ǂɓ�����Ȃ������B
			cam._vPos = VAdd(cam._vPos, v);
			cam._vTarget = VAdd(cam._vTarget, v);
		}
	}
	else {
		v = oldv;
	}

	// �S�[��
	if (chara._hitObjType == 7) {
		chara._mapBoxType = 1;
		chara._flgExit = 1;
		if (keyRoom == 1109) {
			RoomClear[1] = 1;
		}
		else if (keyRoom == 4226) {
			RoomClear[4] = 1;
		}
	}

	for (int i = 0; i < _vEffekseer.size(); i++) {
		_vEffekseer[i].Process();
	}
}

void RoomSlidePuzzle::CameraProcess(Camera& cam) {
	// �J�����̓����蔻��
	bool flgHitCam = false;
	cam._oldvPos = cam._vPos;
	// �}�b�v�I�u�W�F�N�g
	for (int i = 0; i < rData._objData.size(); i++) {
		if (cam.isHit(rData._objData[i]._handle, rData._objData[i]._frameCollision)) {
			flgHitCam = true;
		}
	}
}

void RoomSlidePuzzle::Render(VECTOR vPos, bool viewColl) {
	// �}�b�v���f���`��
	RenderObjectModel();
	
	//MV1SetPosition(rData._handleSkySphere, VGet(vPos.x, vPos.y, vPos.z + 200));
	MV1SetPosition(rData._handleSkySphere, VGet(5200.f, 0.f, -750.f));
	MV1DrawModel(rData._handleSkySphere);

	//effekseer�`��
	{
		_effekseer.Render();
	}
}
