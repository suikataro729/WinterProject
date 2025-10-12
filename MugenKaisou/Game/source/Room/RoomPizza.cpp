#include "RoomPizza.h"
#include "../ApplicationGlobal.h"
#include "../ModeRoomNumber.h"
#include "../ModeTalk.h"

RoomPizza::RoomPizza() {
	goolDoor.SetVisible(true);
	SaveRoot[3] = 1;
	for (int i = 0; i < _vEffekseer.size(); i++) {
		_vEffekseer.erase(_vEffekseer.begin() + i);
	}
}

RoomPizza::~RoomPizza() {
	for (int i = 0; i < _vEffekseer.size(); i++) {
		_vEffekseer.erase(_vEffekseer.begin() + i);
	}
}

void RoomPizza::Process(Chara& chara, Camera& cam, VECTOR& v, VECTOR oldv) {
	if (SaveRoot[3] == 0)
	{
		SaveRoot[3] = 1;
		ModeTalk* modetalk = new ModeTalk("res/jsonfile/TextData/pizza1.json");
		// ModeGame����̃��C���[�Ƀg�[�N��o�^����
		ModeServer::GetInstance()->Add(modetalk, 200, "talk");
		//_effekseer.AddEffect("res/Effect/doa/doa.efkefc", 3500.0f, 0.0f, -1000.0f, 999999, 0.25f);
		//_vEffekseer.push_back(_effekseer);
	}
	
	// �ݒu�u���b�N�ʑ���
	if (chara.jump_flg == 0) {
		if (chara._mapBoxType == 2 || chara._mapBoxType == 3 ||
			chara._mapBoxType == 4 || chara._mapBoxType == 5) {
			// �x���g�R���x�A
			// �L�����ړ�
			chara._vPos = chara._oldvPos;
			beltConv.MovePos(chara._vPos, chara._mapBoxType, 32);
		}
		else if (chara._hitObjType == 7) {
			// �S�[��
			chara._mapBoxType = 1;
			chara._flgExit = 1;
			//ModeTalk* modetalk = new ModeTalk("res/jsonfile/TextData/pizza3.json");
			//// ModeGame����̃��C���[�Ƀg�[�N��o�^����
			//ModeServer::GetInstance()->Add(modetalk, 200, "talk");
			RoomClear[3] = 1;
		}
	}
	
	_isCharaMove = true;	// �L�����͈ړ��������̃t���O
	chara._mapBoxType = 0;
	chara._hitObjType = 0;
	chara._vNormal.clear();
	// �}�b�v�Ƃ̏Փ˔���
	for (int i = 0; i < rData._objData.size(); i++) {
		// ��l���̍��ʒu���牺�����ւ̒���
		if (chara.isHitGround(rData._objData[i]._handle, rData._objData[i]._frameCollision)) {
			// �x���g�R���x�A����
			chara._mapBoxType = rData._objData[i]._mapType;
			// �W�����v������
			if (gPad[0].gXTrg[XINPUT_BUTTON_B] && chara.jump_flg == 0 && chara._mapBoxType == 1)
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
		if ((chara._mapBoxType == 2 || chara._mapBoxType == 3 ||
			chara._mapBoxType == 4 || chara._mapBoxType == 5)
			&& chara.jump_flg == 0) {
			// �x���g�R���x�A
			beltConv.MovePos(cam._vPos, chara._mapBoxType, 32);
			beltConv.MovePos(cam._vTarget, chara._mapBoxType, 32);
		}
		else {
			// �ʏ�
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
	}
	else {
		v = oldv;
	}

	// �x���g�R���x�A��ł̓A�j���[�V������WAIT�ɂ���
	if (chara._mapBoxType == 2 || chara._mapBoxType == 3 ||
		chara._mapBoxType == 4 || chara._mapBoxType == 5) {
		if (chara.jump_flg == 0) {
			chara._isWait = true;
		}
	}
	else { chara._isWait = false; }

	// �s�U�o��
	if (gPizza) {
		int sign;
		if (GetRand(100) % 2 == 0) { sign = 1; }
		else { sign = -1; }
		int xrand = GetRand(600) * sign;
		if (GetRand(100) % 2 == 0) { sign = 1; }
		else { sign = -1; }
		int zrand = GetRand(600) * sign;
		pizza.AddPizza(chara._vPos.x + xrand, chara._vPos.y + 300, chara._vPos.z + zrand);
		_vPizza.push_back(pizza);
		gPizza = false;
		//if (!TalkFlg[5]) {
		//	TalkFlg[5] = TRUE;
		//	ModeTalk* modetalk = new ModeTalk("res/jsonfile/TextData/pizza2.json");
		//	// ModeGame����̃��C���[�Ƀg�[�N��o�^����
		//	ModeServer::GetInstance()->Add(modetalk, 200, "talk");
		//}
	}

	//�s�U��������
	if (_vPizza.size() > 0) {
		for (int i = 0; i < _vPizza.size(); i++) {
			VECTOR pOldvPos = _vPizza[i]._vPos;
			if (_vPizza[i]._mapBoxType != 0 && _vPizza[i]._mapBoxType != 1 && _vPizza[i]._mapBoxType != 10) {
				_vPizza[i]._vPos = pOldvPos;
				beltConv.MovePos(_vPizza[i]._vPos, _vPizza[i]._mapBoxType, 32);
			}
			_vPizza[i].gravity += 0.6;
			for (int n = 0; n < rData._objData.size(); n++)
			{
				//_vPizza[i].Process(_objData[n]._handle, _objData[n]._frameCollision);
				// �ړ�������ŃR���W��������
				MV1_COLL_RESULT_POLY hitPoly;
				hitPoly = MV1CollCheck_Line(rData._objData[n]._handle, rData._objData[n]._frameCollision,
					VAdd(_vPizza[i]._vPos, VGet(0, 100, 0)), VAdd(_vPizza[i]._vPos, VGet(0, -99999.f, 0)));
				if (hitPoly.HitFlag) {
					// ��������
					if (_vPizza[i]._vPos.y <= hitPoly.HitPosition.y) {
						if (!TalkFlg[14])
						{
							TalkFlg[14] = TRUE;
							ModeTalk* modetalk = new ModeTalk("res/jsonfile/TextData/pizza2.json");
							// ModeGame����̃��C���[�Ƀg�[�N��o�^����
							ModeServer::GetInstance()->Add(modetalk, 200, "talk");
						}
						
						_vPizza[i].gravity = 0;
						// ��������Y�ʒu���L�������W�ɂ���
						_vPizza[i]._vPos.y = hitPoly.HitPosition.y;
						_vPizza[i]._mapBoxType = rData._objData[n]._mapType;

						// �\�����ԃJ�E���g
						_vPizza[i]._cntView++;
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

	for (int i = 0; i < _vEffekseer.size(); i++) {
		_vEffekseer[i].Process();
	}
}

void RoomPizza::CameraProcess(Camera& cam) {
	// �J�����̓����蔻��
	bool flgHitCam = false;
	cam._oldvPos = cam._vPos;
	for (int i = 0; i < rData._objData.size(); i++) {
		if (cam.isHit(rData._objData[i]._handle, rData._objData[i]._frameCollision)) {
			flgHitCam = true;
		}
	}
}

void RoomPizza::Render(VECTOR vPos, bool viewColl) {
	// �}�b�v���f���`��
	RenderObjectModel();

	MV1SetPosition(rData._handleSkySphere, VGet(vPos.x, vPos.y, vPos.z + 200));
	MV1DrawModel(rData._handleSkySphere);

	// �s�U
	if (_vPizza.size() > 0) {
		for (int i = 0; i < _vPizza.size(); i++) {
			_vPizza[i].Render();
		}
	}

	//effekseer�`��
	{
		_effekseer.Render();
	}
}
