
#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ApplicationGlobal.h"
#include "ModeGame.h"
#include "ModeTitle.h"
#include "ModeFade.h"

// ���j���[����
class MenuItemViewCollision : public MenuItemBase {
public:
	MenuItemViewCollision(void* param, std::string text) : MenuItemBase(param, text) {}

	// ���ڂ����肵���炱�̊֐����Ă΂��
	// return int : 0 = ���j���[�p��, 1 = ���j���[�I��
	virtual int Selected() {
		ModeGame* mdGame = static_cast<ModeGame*>(_param);
		mdGame->SetDebugViewColloion(!mdGame->GetDebugViewColloion());
		return 1;
	}
};

class MenuItemViewInfo : public MenuItemBase {
public:
	MenuItemViewInfo(void* param, std::string text) : MenuItemBase(param, text) {}

	// ���ڂ����肵���炱�̊֐����Ă΂��
	// return int : 0 = ���j���[�p��, 1 = ���j���[�I��
	virtual int Selected() {
		ModeGame* mdGame = static_cast<ModeGame*>(_param);
		mdGame->SetDebugViewInfo(!mdGame->GetDebugViewInfo());
		return 0;
	}
};


bool ModeGame::Initialize() {
	if (!base::Initialize()) { return false; }

	se[0] = LoadSoundMem("res/sound/SE/move.wav");
	cgUI = LoadGraph("res/UI/UI_L.png");

	// �L����������
	_chara.Init();
	// �J����������
	_cam.Init(_chara._vPos);

	// �}�b�v�w��
	Rooms->ChangeRoom(keyRoom = 0);
	_flgMap = false;
	rData.RoomLoad(keyRoom);
	// �L�����E�J�����̃}�b�v�Ή�������
	Rooms->SetSpown(_chara, _cam);

	// �񓯊������J�n---------------------------------------------------
	SetUseASyncLoadFlag(TRUE);

	// �I�u�W�F�N�g��3D���f���擾
	rData.LoadModelHandle();

	// �񓯊������I��---------------------------------------------------
	SetUseASyncLoadFlag(FALSE);

	// �}�b�v������
	rData.RoomInit();

	// �T�E���h
	_sound.Load(keyRoom);

	// �J�E���g�摜�ǂݍ���
	for (int n = 0; n < 10; n++)
	{
		std::string img = "res/UI/L_UI/countNum/";
		img += std::to_string(n);
		img += ".png";
		cg_countNum[n] = LoadGraph(img.c_str());
	}
	for (int n = 0; n < 10; n++)
	{
		std::string img = "res/UI/L_UI/countNum_y/";
		img += std::to_string(n);
		img += ".png";
		cg_countNum_y[n] = LoadGraph(img.c_str());
	}
	cg_timebg = LoadGraph("res/UI/L_UI/TIMELIMIT.png");

	// �����ԍ��摜�ǂݍ���
	cgRoomNumber[0] = LoadGraph("res/UI/L_UI/RoomNum/6212.png");
	cgRoomNumber[1] = LoadGraph("res/UI/L_UI/RoomNum/1109.png");
	cgRoomNumber[2] = LoadGraph("res/UI/L_UI/RoomNum/1114.png");
	cgRoomNumber[3] = LoadGraph("res/UI/L_UI/RoomNum/0311.png");
	cgRoomNumber[4] = LoadGraph("res/UI/L_UI/RoomNum/0223.png");
	cgRoomNumber[5] = LoadGraph("res/UI/L_UI/RoomNum/beforetheday.png");
	cgRoomNumber[6] = LoadGraph("res/UI/L_UI/RoomNum/3215.png");
	cgRoomNumber[7] = LoadGraph("res/UI/L_UI/RoomNum/101birthday.png");
	cgRoomNumber[8] = LoadGraph("res/UI/L_UI/RoomNum/entrance.png");
	cgRoomNumber[9] = LoadGraph("res/UI/L_UI/RoomNum/theChristmas.png");

	// �񓯊������I��---------------------------------------------------
	//SetUseASyncLoadFlag(FALSE);

	// �G�t�F�N�g�p
	_flgEffect = false;

	// ���̑�������
	_bViewCollision = FALSE;
	_bViewInfo = FALSE;
	respown_flg = false;
	clear_cnt = -1;
	FullScreenFlg = TRUE;
	_flgPlay = true;

	SetMouseDispFlag(true);

#if 0
	ModeTalk* modetalk = new ModeTalk("res/jsonfile/TextData/christmas.json");
	// ModeGame����̃��C���[�Ƀg�[�N��o�^����
	ModeServer::GetInstance()->Add(modetalk, 200, "talk");
#endif
#if 0
	ModeEnding* modetalk = new ModeEnding();
	// ModeGame����̃��C���[�Ƀg�[�N��o�^����
	ModeServer::GetInstance()->Add(modetalk, 200, "talk");
#endif
#if 0
	ModeRoomNumber* modegamenumber = new ModeRoomNumber(keyRoom, 1109, TRUE);
	// ModeGame����̃��C���[�Ƀ��j���[��o�^����
	ModeServer::GetInstance()->Add(modegamenumber, 110, "number");
#endif
#if 0
	ModeEffekseer* modeeffekseer = new ModeEffekseer();
	modeeffekseer->Initialize(0.0f, 0.0f, 0.0f); // �G�t�F�N�g�̈ʒu��ݒ�
	// ModeGame����̃��C���[�Ƀ��j���[��o�^����
	ModeServer::GetInstance()->Add(modeeffekseer, 120, "effekseer");
#endif
//�E�B���h�E�o��
#if 0
	FullScreenFlg = FALSE;
	ModeWindow* modewindow = new ModeWindow();
	ModeServer::GetInstance()->Add(modewindow, 100, "window");
#endif
	//_vEffekseer[0].AddEffect("res/Laser01.efkefc", 0.0f, 500.0f, 0.0f);
	// �e�N�X�`�������_�����O�p�̉摜�쐬
	render_texture_handle = MakeScreen(1920, 1080);

	// BGM�Đ�
	_sound.Play(DX_PLAYTYPE_LOOP);

	return true;
}

bool ModeGame::Terminate() {
	base::Terminate();

	return true;
}

bool ModeGame::Process() {
	base::Process();
	int key = ApplicationMain::GetInstance()->GetKey();
	int trg = ApplicationMain::GetInstance()->GetTrg();
	int rel = ApplicationMain::GetInstance()->GetRel();


	if (!rData.IsLoad()) {

		// �����O�̃X�e�[�^�X��ۑ����Ă���
		Chara::STATUS oldStatus = _chara._status;

		// ESC�L�[��ModeEffekseer���J��
		//if (trg & PAD_INPUT_9) {
		//	gamecntdown = 0;
		//}

		// �Q�[���p�b�h�Ή��iXInput�j
		float lx, ly, rx, ry;	// ���E�A�i���O�X�e�B�b�N�̍��W
		float analogMin = 0.3f;	// �A�i���O臒l
		lx = (float)gPad[0].xinput_pad.ThumbLX / 32768.f; ly = (float)gPad[0].xinput_pad.ThumbLY / -32768.f;
		rx = (float)gPad[0].xinput_pad.ThumbRX / 32768.f; ry = (float)gPad[0].xinput_pad.ThumbRY / 32768.f;

		// �}�b�v�؂�ւ�
		if (_flgMap) {
			// �L�����N�^�[������
			_chara.Spown(respown_flg);
			// �J����������
			_cam.Spown(_chara._vPos);
			
			rData.RoomLoad(keyRoom);
			Rooms->SetSpown(_chara, _cam);
			_sound.Delete();

			// �񓯊������J�n-------------------------
			SetUseASyncLoadFlag(TRUE);

			// �I�u�W�F�N�g��3D���f���擾
			rData.LoadModelHandle();

			// �񓯊������I��-------------------------
			SetUseASyncLoadFlag(FALSE);

			// �}�b�v������
			rData.RoomInit();
			// �T�E���h
			_sound.Load(keyRoom);

			_flgMap = false;
			_flgPlay = true;

			//BGM��~
			_sound.Stop();
			// BGM�Đ�
			_sound.Play(DX_PLAYTYPE_LOOP);
		}

		//���X�|�[���t���O�������Ă����珉���l�ɂ���
		if (respown_flg) {
			// �L�����̃��X�|�[���Ə�����
			_chara.Spown(respown_flg);
			// ����������
			Rooms->Reset();
			// �J����������
			_cam.Spown(_chara._vPos);
			respown_flg = false;

			if (!TalkFlg[4]) {
				TalkFlg[4] = TRUE;
				ModeTalk* modetalk = new ModeTalk("res/jsonfile/TextData/respawn.json");
				// ModeGame����̃��C���[�Ƀg�[�N��o�^����
				ModeServer::GetInstance()->Add(modetalk, 200, "talk");
			}
		}

		// �L�����ړ�(�J�����ݒ�ɍ��킹��)

		// �J�����̌����Ă���p�x���擾
		float sx = _cam._vPos.x - _cam._vTarget.x;
		float sz = _cam._vPos.z - _cam._vTarget.z;
		float camrad = atan2(sz, sx);

		// �ړ����������߂�
		VECTOR v = { 0,0,0 };
		float mvSpeed;
		float length = sqrt(lx * lx + ly * ly);
		float rad = atan2(lx, ly);

		{
			mvSpeed = 6.f;
			if (length < analogMin) {
				// ���͂������������瓮���Ȃ��������Ƃɂ���
				length = 0.f;
			}
			else {
				length = mvSpeed;
			}
			// v��rad����]������
			v.x = cos(rad + camrad) * length;
			v.z = sin(rad + camrad) * length;
		}

		// �ړ��ʐݒ�
		v = VScale(v, 2.f);
		// �ړ��O�̈ʒu��ۑ�
		_chara._oldvPos = _chara._vPos;
		VECTOR oldv = v;
		_cam._vPos = _cam._oldvPos;

		// v�̕��ړ�
		_chara._vPos = VAdd(_chara._vPos, v);

		// �d�͑���
		if (_chara.gravity < 100.f) {
			_chara.gravity += 0.6f;
		}
		else {
			_chara.gravity = 100.f;
		}

		// �L�����ړ�����
		// �����ɂ�鏈��
		Rooms->Process(_chara, _cam, v, oldv);

		if (_chara.jump_flg == 1) {
			if (_chara._isLanded)
			{
				_effekseer.AddEffect("res/Effect/jump/jump.efkefc", _chara._vPos.x, _chara._vPos.y, _chara._vPos.z, 30);
				_vEffekseer.push_back(_effekseer);
			}
			// �W�����v����
			_chara.Jump();
		}

		//�d�͂̔��f
		_chara._vPos.y -= _chara.gravity;

		// �L�������~�����i���Ɉړ����Ă���j��
		if (_chara.jump_flg && _chara._vPos.y < _chara._oldvPos.y) {
			// �~���A�j���[�V�����ɕύX
			_chara._flgJumpAnim = 2;
		}

		// �L�������㉺�Ɉړ������ʂ����A�ړ��ʂ��C��
		v.y += _chara._vPos.y - _chara._oldvPos.y;

		// �J�����C��
		_cam._vPos.y += v.y;
		_cam._vTarget.y += v.y;

		//�������Ɍ��̍��W�ɖ߂�
		if (_chara._vPos.y < -400 || _chara._isDead)
		{
			respown_flg = true;
			gChara_Dead = true;
		}

		// �ړ��ʂ����̂܂܃L�����̌����ɂ���
		// �L�����N�^�[�X�e�[�^�X�X�V
		_chara.ChangeStatus(v);

		// �J����������s���i�E�X�e�B�b�N�j
		{
			// Y����]
			float sx = _cam._vPos.x - _cam._vTarget.x;
			float sz = _cam._vPos.z - _cam._vTarget.z;
			float rad = atan2(sz, sx);
			float length = sqrt(sz * sz + sx * sx);
			if (rx > analogMin) { rad -= 0.05f; }
			if (rx < -analogMin) { rad += 0.05f; }
			_cam._vPos.x = _cam._vTarget.x + cos(rad) * length;
			_cam._vPos.z = _cam._vTarget.z + sin(rad) * length;

			// Y�ʒu
			if (ry > analogMin) { _cam._vPos.y -= 5.f; }
			if (ry < -analogMin) { _cam._vPos.y += 5.f; }
		}

		// �J���������蔻��
		Rooms->CameraProcess(_cam);

		// �L�����N�^�[�A�j���[�V�����X�V
		_chara.ChangeCharaAnim(oldStatus);

		//�J�E���g�_�E��
		{
			if (gamecntdown != -999)
			{
				gamecntdown -= 1;
				if (-60 > gamecntdown)
				{
					//�O�b�ɂȂ���
					_chara._flgExit = true;
				}
			}
		}
		// �G�t�F�N�g����
		if (keyRoom != 1225)
		{
			if (VSize(v) > 0.f) {		// �ړ����Ă��Ȃ����͖������邽��
				if (GetModeCount() % 11 == 0 && _chara._isLanded == true) {
					_effekseer.AddEffect("res/Effect/dash/dash.efkefc", _chara._vPos.x, _chara._vPos.y, _chara._vPos.z, 37);
					_vEffekseer.push_back(_effekseer);
				}
				if (GetModeCount() % 45 == 0 && _chara._isLanded == true) {
					PlaySoundMem(se[0], DX_PLAYTYPE_BACK, TRUE);
				}
			}

			//if (gPad[0].gXTrg[XINPUT_BUTTON_X]) {
			//_effekseer.AddEffect("res/Laser01.efkefc", _chara._vPos.x, _chara._vPos.y, _chara._vPos.z);
			//_vEffekseer.push_back(_effekseer);
			//}
			for (int i = 0; i < _vEffekseer.size(); i++) {
				_vEffekseer[i].Process();

				// ��������
				if (_vEffekseer[i].EffectCnt > _vEffekseer[i].EffectCntMax) {
					_vEffekseer.erase(_vEffekseer.begin() + i);
				}
			}
			// Effekseer�ɂ��Đ����̃G�t�F�N�g���X�V����B
			UpdateEffekseer3D();
		}

		// �o��
		if (_chara._flgExit) {
			if (_flgPlay) {
				// �t�F�[�h�C���A�E�g
				ModeServer::GetInstance()->Add(new ModeFade("OUT"), 998, "fade");
				_flgPlay = false;
			}
			else {
				if (gGlobal._isFinishFadeOut) {
					// �t�F�[�h�A�E�g�I��
					ModeRoomNumber* modegamenumber;
					if (-60 > gamecntdown && gamecntdown != -999) {
						// �^�C���A�b�v�ɂ��Q�[���I�[�o�[
						modegamenumber = new ModeRoomNumber(keyRoom, gGlobal.keyLoseRoom, FALSE);
						keyRoom = gGlobal.keyLoseRoom;

						if (!TalkFlg[3]) {
							TalkFlg[3] = TRUE;
							ModeTalk* modetalk = new ModeTalk("res/jsonfile/TextData/timeflag.json");
							// ModeGame����̃��C���[�Ƀg�[�N��o�^����
							ModeServer::GetInstance()->Add(modetalk, 200, "talk");
						}
					}
					else {
						// �S�[�������ɂ��X�e�[�W�N���A
						modegamenumber = new ModeRoomNumber(keyRoom, gGlobal.keyNextRoom, TRUE);
						keyRoom = gGlobal.keyNextRoom;
					}
					// ModeGame����̃��C���[�Ƀ��j���[��o�^����
					ModeServer::GetInstance()->Add(modegamenumber, 110, "number");

					_flgMap = true;
					_sound.Stop();
					_sound.Delete();
					rData.RoomRelease();
					Rooms->ChangeRoom(keyRoom);
					_chara._flgExit = false;
				}
			}
		}

		// �f�o�b�O
		// ESC�L�[�Ń��j���[���J��
		if (trg & PAD_INPUT_9) {
			ModeMenu* modeMenu = new ModeMenu();
			// ModeGame����̃��C���[�Ƀ��j���[��o�^����
			ModeServer::GetInstance()->Add(modeMenu, 999, "menu");
			// ModeMenu�Ƀ��j���[���ڂ�ǉ�����
			modeMenu->Add(new MenuItemViewCollision(this, "ViewCollision"));
			modeMenu->Add(new MenuItemViewInfo(this, "ViewInfo"));
		}
	}

	return true;
}

bool ModeGame::Render() {
	SetDrawScreen(render_texture_handle);
	ClearDrawScreen();
	base::Render();

	//if (rData.IsLoad()) {
	//	DrawFormatString(0, 0, GetColor(255, 255, 255), "�񓯊��ǂݍ��݂̐� %d", GetASyncLoadNum());
	//}
	{

		//if (FullScreenFlg) {
		//	// ���̃��[�h��艺�̃��C���[��Process()���Ă΂Ȃ�
		//	ModeServer::GetInstance()->SkipRenderUnderLayer();
		//}
		//SetDrawArea(0, 0, 1920/2, 1080);
		//SetCameraScreenCenter(1920 / 4, 1080 / 2);

		// 3D��{�ݒ�
		SetUseZBuffer3D(TRUE);
		SetWriteZBuffer3D(TRUE);
		SetUseBackCulling(TRUE);
	}

	// ���C�g�ݒ�
	SetUseLighting(TRUE);
#if 1	// ���s���C�g
	SetGlobalAmbientLight(GetColorF(0.0f, 0.f, 0.f, 0.f));
	ChangeLightTypeDir(VGet(0, -1, 0));
#endif
#if 0	// �|�C���g���C�g
	SetGlobalAmbientLight(GetColorF(0.f, 0.f, 0.f, 0.f));
	ChangeLightTypePoint(VAdd(_chara._vPos,VGet(0,50.f,0)), 1000.f, 0.f, 0.005f, 0.f);
#endif

	if (!rData.IsLoad()) {

		// �J�����ݒ�X�V
		SetCameraPositionAndTarget_UpVecY(_cam._vPos, _cam._vTarget);
		SetCameraNearFar(_cam._clipNear, _cam._clipFar);

		if (_bViewCollision) {
			// 0,0,0�𒆐S�ɐ�������
			{
				float linelength = 1000.f;
				VECTOR v = { 0, 0, 0 };
				DrawLine3D(VAdd(v, VGet(-linelength, 0, 0)), VAdd(v, VGet(linelength, 0, 0)), GetColor(255, 0, 0));
				DrawLine3D(VAdd(v, VGet(0, -linelength, 0)), VAdd(v, VGet(0, linelength, 0)), GetColor(0, 255, 0));
				DrawLine3D(VAdd(v, VGet(0, 0, -linelength)), VAdd(v, VGet(0, 0, linelength)), GetColor(0, 0, 255));
			}

			// �J�����^�[�Q�b�g�𒆐S�ɒZ����������
			{
				float linelength = 10.f;
				VECTOR v = _cam._vTarget;
				DrawLine3D(VAdd(v, VGet(-linelength, 0, 0)), VAdd(v, VGet(linelength, 0, 0)), GetColor(255, 0, 0));
				DrawLine3D(VAdd(v, VGet(0, -linelength, 0)), VAdd(v, VGet(0, linelength, 0)), GetColor(0, 255, 0));
				DrawLine3D(VAdd(v, VGet(0, 0, -linelength)), VAdd(v, VGet(0, 0, linelength)), GetColor(0, 0, 255));
			}
		}

		// ���f����`�悷��
		{
			_chara.Render();

			// �R���W��������p���C���̕`��
			if (_bViewCollision) {
				DrawLine3D(VAdd(_chara._vPos, VGet(0, _chara._colSubY, 0)), VAdd(_chara._vPos, VGet(0, -99999.f, 0)), GetColor(255, 0, 0));

				// �J�v�Z��
				DrawCapsule3D(VAdd(_chara._vPos, VGet(0, _chara._collLower, 0)), VAdd(_chara._vPos, VGet(0, _chara._collUpper, 0)), _chara._CapsuleR, 8, GetColor(255, 0, 0), GetColor(0, 255, 0), FALSE);
			}
		}

		//�ۉe�̕\��
		//USEFUL.DrawRoundShadow(_handleMap,_frameMapCollision, _chara._vPos, _chara._colSubY,30.f,90);


		// �}�b�v���f����`�悷��
		{
			Rooms->Render(_chara._vPos, _bViewCollision);
		}

		// �t�H�O��L���ɂ���
		SetFogEnable(TRUE);

		// �t�H�O�̐F�����F�ɂ���
		SetFogColor(255, 255, 255);

		// �t�H�O�̊J�n�������O�A�I���������P�T�O�O�ɂ���
		SetFogStartEnd(0.0f, 8000.0f);

		//effekseer�`��
		if (keyRoom != 1225) {
			_effekseer.Render();
		}

		// �^�[�Q�b�g���o�b�N�o�b�t�@�ɖ߂��āA�����_�����O�����e�N�X�`�����g�p���ĕ`��
		SetDrawScreen(DX_SCREEN_BACK);

		if (FullScreenFlg) {
			SetDrawArea(0, 0, 1920, 1080);
			//�RD�`������炷
			DrawGraph(0, 0, render_texture_handle, TRUE);
		}
		else
		{
			SetDrawArea(0, 0, 1920 / 2, 1080);
			//�RD�`������炷
			DrawGraph(-1920 / 4, 0, render_texture_handle, TRUE);
		}

		int x = 0, y = 300, size = 16;
		// �J�������\��
		if(_bViewInfo) {
			SetFontSize(size);

			DrawFormatString(x, y, GetColor(255, 0, 0), "Camera:"); y += size;
			DrawFormatString(x, y, GetColor(255, 0, 0), "  target = (%5.2f, %5.2f, %5.2f)", _cam._vTarget.x, _cam._vTarget.y, _cam._vTarget.z); y += size;
			DrawFormatString(x, y, GetColor(255, 0, 0), "  pos    = (%5.2f, %5.2f, %5.2f)", _chara._vPos.x, _chara._vPos.y, _chara._vPos.z); y += size;
			float sx = _cam._vPos.x - _cam._vTarget.x;
			float sz = _cam._vPos.z - _cam._vTarget.z;
			float length = sqrt(sz * sz + sx * sx);
			float rad = atan2(sz, sx);
			float deg = RAD2DEG(rad);
			DrawFormatString(x, y, GetColor(255, 0, 0), "  len = %5.2f, rad = %5.2f, deg = %5.2f", length, rad, deg); y += size;
			DrawFormatString(x, y, GetColor(255, 0, 0), "  _chara._vDir.x = %5.2f, _chara._vDir.y = %5.2f, _chara._vDir.z = %5.2f", _chara._vDir.x, _chara._vDir.y, _chara._vDir.z); y += size;

			// �J�v�Z���ƏՓ˂����|���S����
			DrawFormatString(x, y, GetColor(255, 0, 0), "  Capsule Collision : %d", _chara.CntHitCapsule); y += size;
			// �����������̃^�C�v
			DrawFormatString(x, y, GetColor(255, 0, 0), "  MapBoxType : %d", _chara._mapBoxType); y += size;
			// ���������I�u�W�F�N�g�^�C�v
			DrawFormatString(x, y, GetColor(255, 0, 0), "  HitObjType : %d", _chara._hitObjType); y += size;
			// �}�b�v�t���O
			DrawFormatString(x, y, GetColor(255, 0, 0), "  flgMap : %d", _flgMap); y += size;
			// �s�U�o���t���O
			DrawFormatString(x, y, GetColor(255, 0, 0), "  gPizza : %d", gPizza); y += size;
			// �J�v�Z���ƏՓ˂����|���S���̖@���x�N�g��
			if (_chara._vNormal.size() != 0) {
				for (int i = 0; i < _chara._vNormal.size(); i++) {
					DrawFormatString(x, y, GetColor(255, 0, 0), "  vNormal[%d] : (%5.2f, %5.2f, %5.2f)", i, _chara._vNormal[i].x, _chara._vNormal[i].y, _chara._vNormal[i].z); y += size;
				}
			}

			for (int i = 0; i < _vEffekseer.size(); i++)
			{
				DrawFormatString(x, y, GetColor(255, 0, 0), "  _vEffekseer[i].x:%5.2f", _vEffekseer[i]._position_x); y += size;
				DrawFormatString(x, y, GetColor(255, 0, 0), "  _vEffekseer[i].y:%5.2f", _vEffekseer[i]._position_y); y += size;
				DrawFormatString(x, y, GetColor(255, 0, 0), "  _vEffekseer[i].z:%5.2f", _vEffekseer[i]._position_z); y += size;
			}
		}


		//��ʏ㕔UI
		if (FullScreenFlg) {
			if (gamecntdown != -999)
			{
				int DrawCnt[3];
				int saveCnt = gamecntdown / 60;
				int values[] = { 100, 10, 1 };
				int Font = GetFontSize();
				int digit = 0;		//����
				SetFontSize(64);
				//�J�E���g�_�E��
				{
					//�J�E���g�_�E���w�i
					DrawGraph(848, 45, cg_timebg, TRUE);

					for (int i = 2; i >= 0; i--) {
						DrawCnt[i] = saveCnt % 10;	// �ŉ��ʌ������o��
						saveCnt = saveCnt / 10;			// ���l���E�ɃV�t�g
					}
					//�J�E���g�_�E�������`��
					for (int i = 0; i < 3; i++) {
						if ((gamecntdown / 60) < values[i]) { continue; }
						digit++;
					}
					//�J�E���g�_�E�������`��
					for (int i = 0; i < 3; i++) {
						if ((gamecntdown / 60) < values[i]) { continue; }
						switch (digit)
						{
						case 3:
							DrawGraph(891 + 40 * i, 21, cg_countNum[DrawCnt[i]], TRUE);
							break;
						case 2:
							if (gamecntdown / 60 <= 20) {
								//�c�莞��20�b�ȉ��Ő��������F���Ȃ�
								DrawGraph(871 + 40 * i, 21, cg_countNum_y[DrawCnt[i]], TRUE);
							}
							else
							{
								DrawGraph(871 + 40 * i, 21, cg_countNum[DrawCnt[i]], TRUE);
							}
							break;
						case 1:
							//�c�莞��20�b�ȉ��Ő��������F���Ȃ�
							DrawGraph(931, 21, cg_countNum_y[DrawCnt[i]], TRUE);
							break;
						}

					}
				}
				//�����ԍ�
				{
					int num = 0;
					switch (keyRoom) {
					case 6212: num = 0; break;
					case 1109: num = 1; break;
					case 1114: num = 2; break;
					case 311: num = 3; break;
					case 223: num = 4; break;
					case 4226: num = 5; break;
					case 3215: num = 6; break;
					case 2126: num = 7; break;
					case 0: num = 8; break;
					case 1225: num = 9; break;
					}
					//�����ԍ��w�i
					//for (int i = 47; i > 0; i--)
					//{
					//	DrawGraph(608 - i * 3, i, cgRoomNumber[num], TRUE);
					//}
					DrawGraph(1580, 47, cgRoomNumber[num], TRUE);
				}
				SetFontSize(Font);
			}
		}
		else
		{
			if (gamecntdown != -999)
			{
				int DrawCnt[3];
				int saveCnt = gamecntdown / 60;
				int values[] = { 100, 10, 1 };
				int Font = GetFontSize();
				int digit = 0;		//����
				SetFontSize(64);
				//�J�E���g�_�E��
				{
					//�J�E���g�_�E���w�i
					DrawGraph(367, 45, cg_timebg, TRUE);

					for (int i = 2; i >= 0; i--) {
						DrawCnt[i] = saveCnt % 10;	// �ŉ��ʌ������o��
						saveCnt = saveCnt / 10;			// ���l���E�ɃV�t�g
					}
					//�J�E���g�_�E�������`��
					for (int i = 0; i < 3; i++) {
						if ((gamecntdown / 60) < values[i]) { continue; }
						digit++;
					}

					//�J�E���g�_�E�������`��
					for (int i = 0; i < 3; i++) {
						if ((gamecntdown / 60) < values[i]) { continue; }
						switch (digit)
						{
						case 3:
							DrawGraph(410 + 40 * i, 21, cg_countNum[DrawCnt[i]], TRUE);
							break;
						case 2:
							if (gamecntdown / 60 <= 20) {
								//�c�莞��20�b�ȉ��Ő��������F���Ȃ�
								DrawGraph(390 + 40 * i, 21, cg_countNum_y[DrawCnt[i]], TRUE);
							}
							else
							{
								DrawGraph(390 + 40 * i, 21, cg_countNum[DrawCnt[i]], TRUE);
							}
							break;
						case 1:
							//�c�莞��20�b�ȉ��Ő��������F���Ȃ�
							DrawGraph(450, 21, cg_countNum_y[DrawCnt[i]], TRUE);
							break;
						}

					}
				}
				//�����ԍ�
				{
					int num = 0;
					switch (keyRoom) {
					case 6212: num = 0; break;
					case 1109: num = 1; break;
					case 1114: num = 2; break;
					case 311: num = 3; break;
					case 223: num = 4; break;
					case 4226: num = 5; break;
					case 3215: num = 6; break;
					case 2126: num = 7; break;
					case 0: num = 8; break;
					case 1225: num = 9; break;
					}
					//�����ԍ��w�i
					//for (int i = 47; i > 0; i--)
					//{
					//	DrawGraph(608 - i * 3, i, cgRoomNumber[num], TRUE);
					//}
					DrawGraph(608, 47, cgRoomNumber[num], TRUE);
				}
				SetFontSize(Font);
			}
		}
		SetDrawArea(0, 0, 1920, 1080);
		DrawGraph(130, 1034, cgUI, TRUE);
	}

	return true;
}
