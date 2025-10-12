#include "../ApplicationGlobal.h"
#include "RoomGrave.h"
#include "../ModeRoomNumber.h"
#include "../ModeTalk.h"
RoomGrave::RoomGrave() {
	goolDoor.SetVisible(true);

	flgEffect = true;
}

RoomGrave::~RoomGrave() {
	for (int i = 0; i < _vEffekseer.size(); i++) {
		_vEffekseer.erase(_vEffekseer.begin() + i);
	}
}

void RoomGrave::CharaMove(Chara& chara, Camera& cam, VECTOR& v, VECTOR oldv) {
	
}

void RoomGrave::Process(Chara& chara, Camera& cam, VECTOR& v, VECTOR oldv) {

	if (!SaveRoot[8]) {

		if (!TalkFlg[20]) {
			chengeRoom = 0;
			ModeTalk* modetalk = new ModeTalk("res/jsonfile/TextData/grave1.json");
			// ModeGame����̃��C���[�Ƀg�[�N��o�^����
			ModeServer::GetInstance()->Add(modetalk, 200, "talk");
			TalkFlg[20] = TRUE;
		}

		if (chengeRoom == 1)
		{
			//�킩���Ă���
			SaveRoot[8] = 1;
			chengeRoom = 0;
		}
		if (chengeRoom == 2)
		{
			//�킩���Ă��Ȃ��l
			gamecntdown = -100;
			chengeRoom = 0;
		}

	}
	_isCharaMove = true;	// �L�����͈ړ��������̃t���O
	chara._mapBoxType = 0;
	chara._vNormal.clear();
	// �}�b�v�Ƃ̏Փ˔���
	for (int i = 0; i < rData._objData.size(); i++) {
		// ��l���̍��ʒu���牺�����ւ̒���
		if (chara.isHitGround(rData._objData[i]._handle, rData._objData[i]._frameCollision)) {
			chara._mapBoxType = 1;
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
			// ���̍��W�ɖ߂�
			chara._vPos = chara._oldvPos;
			// �Փˉ��
			if (chara.AvoidCollision(v, rData._objData[i]._handle, rData._objData[i]._frameCollision)) {
				_isCharaMove = true;
			}
			else {
				_isCharaMove = false;
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

	// �s�U�o��
	if (gPizza) {

		//�v���C���[��0,0,0�������Ă���Ƒ����Ƀs�U���o�邩��v�C��

		// �L�����N�^�[�̌����x�N�g�����擾
		VECTOR vUnitDir = VNorm(chara._vDir);
		// �����x�N�g�����[���x�N�g���̏ꍇ�A�f�t�H���g�̌�����ݒ�
		if (VSize(vUnitDir) == 0.0f) {
			vUnitDir = VGet(0.0f, 0.0f, -1.0f); // �f�t�H���g��-Z����������
		}
		// �s�U�̏o���ʒu���v�Z
		float scale = 100.0f;
		VECTOR pizzaPos = VAdd(chara._vPos, VScale(vUnitDir, scale));
		// �s�U���o��������
		pizza.AddPizza(pizzaPos.x, pizzaPos.y + 300, pizzaPos.z);
		_vPizza.push_back(pizza);
		gPizza = false;
	}

	//�s�U��������
	if (_vPizza.size() > 0) {
		for (int i = 0; i < _vPizza.size(); i++) {
			VECTOR pOldvPos = _vPizza[i]._vPos;
			if (_vPizza[i]._mapBoxType != 0 && _vPizza[i]._mapBoxType != 1 && _vPizza[i]._mapBoxType != 10) {
				_vPizza[i]._vPos = pOldvPos;
			}
			_vPizza[i].gravity += 0.6;
			for (int n = 0; n < rData._objData.size(); n++)
			{
				//_vPizza[i].Process(_objData[n]._handle, _objData[n]._frameCollision);
				// �ړ�������ŃR���W��������
				MV1_COLL_RESULT_POLY hitPoly;
				hitPoly = MV1CollCheck_Line(rData._objData[0]._handle, rData._objData[0]._frameCollision,
					VAdd(_vPizza[i]._vPos, VGet(0, 100, 0)), VAdd(_vPizza[i]._vPos, VGet(0, -99999.f, 0)));
				if (hitPoly.HitFlag) {
					// ��������
					if (_vPizza[i]._vPos.y <= hitPoly.HitPosition.y) {
						_vPizza[i].gravity = 0;
						// ��������Y�ʒu���L�������W�ɂ���
						_vPizza[i]._vPos.y = hitPoly.HitPosition.y;
						_vPizza[i]._mapBoxType = rData._objData[n]._mapType;

						// �\�����ԃJ�E���g
						_vPizza[i]._cntView++;
					}
				}
				//��������
				hitPoly = MV1CollCheck_Line(rData._objData[1]._handle, rData._objData[1]._frameCollision,
					VAdd(_vPizza[i]._vPos, VGet(0, 100, 0)), VAdd(_vPizza[i]._vPos, VGet(0, -99999.f, 0)));
				if (hitPoly.HitFlag) {
					// �S�[��
					if (_vPizza[i]._vPos.y <= hitPoly.HitPosition.y) {
						chara._mapBoxType = 7;
						keyRoom = 0;
						chara._flgExit = 1;
						RoomClear[8] = 1;
						break;
					}
				}
			}
			//�d�͂̔��f
			_vPizza[i]._vPos.y -= _vPizza[i].gravity;

			// ��������
			if (_vPizza[i]._vPos.y < -1000 || _vPizza[i]._cntView > 1000) {
				_vPizza.erase(_vPizza.begin() + i);
			}
		}
	}

	if (flgEffect) {
		_effekseer.AddEffect("res/Effect/sakura/sakura.efkefc", chara._vPos.x, chara._vPos.y, chara._vPos.z, 999999);
		_vEffekseer.push_back(_effekseer);
		flgEffect = 0;
	}
	for (int i = 0; i < _vEffekseer.size(); i++) {
		_vEffekseer[i].Process();
	}
}

void RoomGrave::CameraProcess(Camera& cam) {
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

void RoomGrave::Render(VECTOR vPos, bool viewColl) {
	// �}�b�v���f���`��
	RenderObjectModel();

	MV1SetPosition(rData._handleSkySphere, VGet(vPos.x, vPos.y, vPos.z + 200));
	MV1DrawModel(rData._handleSkySphere);

	//effekseer�`��
	{
		_effekseer.Render();
	}

	// �s�U
	if (_vPizza.size() > 0) {
		for (int i = 0; i < _vPizza.size(); i++) {
			_vPizza[i].Render();
		}
	}
}
