
#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ApplicationGlobal.h"
#include "ModeTalk.h"
#include "utf8sjis.h"	// json�̓��{�ꕶ�����g�����߂ɕK�v
#include	<cassert>
#include	<string>

ModeTalk::ModeTalk(std::string TextHandle ,bool Cristmas){
	// json�t�@�C���̓ǂݍ���
	std::ifstream file(TextHandle);
	nlohmann::json json;
	file >> json;
	int i = 0;
	// �f�[�^��ǂݍ���
	for (auto jsonfile : json)
	{
		jsonfile.at("message1").get_to(_jsonData[i].message1);
		jsonfile.at("chara").get_to(_jsonData[i].draw);
		jsonfile.at("charaX").get_to(_jsonData[i].drawX);
		jsonfile.at("charaY").get_to(_jsonData[i].drawY);
		jsonfile.at("command").get_to(_jsonData[i].command);
		jsonfile.at("name").get_to(_jsonData[i].name);
		jsonfile.at("voice").get_to(_jsonData[i].voice);
		jsonfile.at("bgY").get_to(_jsonData[i].bgY);
		jsonfile.at("bg").get_to(_jsonData[i].bg);

		// json�̕�������AUTF-8����Shift-JIS�ɕϊ�
		_jsonData[i].message1 = ConvUTF8toSJIS(_jsonData[i].message1);
		_jsonData[i].draw = ConvUTF8toSJIS(_jsonData[i].draw);
		_jsonData[i].name = ConvUTF8toSJIS(_jsonData[i].name);
		_jsonData[i].voice = ConvUTF8toSJIS(_jsonData[i].voice);
		_jsonData[i].bg = ConvUTF8toSJIS(_jsonData[i].bg);
		i++;
	}
	messagecnt = 0;
	gameCnt = 0;
	_cgBg = 0;
	text_flg = 0;
	cg_chara = LoadGraph(_jsonData[messagecnt].draw.c_str());
	_cgBg = LoadGraph(_jsonData[messagecnt].bg.c_str());
	cg_MessageBox[0] = LoadGraph("res/Talkart/TalkUI/UI_M.png");
	cg_MessageBox[1] = LoadGraph("res/Talkart/TalkUI/UI_R.png");
	cg_MessageBox[2] = LoadGraph("res/Talkart/TalkUI/UI_L.png");

	gameCnt = 0;
	save_cgChara[0] = 0;
	save_cgChara[1] = 0;
	saveMessage[0] = "";
	saveMessage[1] = "";

	ChrismasTime = 0;
	// �N���X�}�X�����p�ɂ���
	ChrismasFlg = Cristmas;
}
ModeTalk::~ModeTalk() {

}
bool ModeTalk::Initialize() {


	return true;
}

bool ModeTalk::Process() {
	base::Process();
	int key = ApplicationMain::GetInstance()->GetKey();
	int trg = ApplicationMain::GetInstance()->GetTrg();

	if (ChrismasFlg) {
		// �{�^���������ꂽ�玟�̃e�L�X�g��
		if (text_flg && ChrismasTime > 60) {
			ChrismasTime = 0;
			messagecnt++;
			cg_chara = LoadGraph(_jsonData[messagecnt].draw.c_str());
			//_cgBg = LoadGraph(_jsonData[messagecnt].bg.c_str());
			gameCnt = 0;
			popupflg = false;
			//�R�}���h�ʂ̓ǂݍ���
			switch (_jsonData[messagecnt].command) {
			case 1:
				saveMessage[0] = _jsonData[messagecnt].message1;
				save_cgChara[1] = LoadGraph(_jsonData[messagecnt].draw.c_str());
				save_drawX[1] = _jsonData[messagecnt].drawX;
				save_drawY[1] = _jsonData[messagecnt].drawY;
				break;
			case 2:
				saveMessage[1] = _jsonData[messagecnt].message1;
				save_cgChara[0] = LoadGraph(_jsonData[messagecnt].draw.c_str());
				save_drawX[0] = _jsonData[messagecnt].drawX;
				save_drawY[0] = _jsonData[messagecnt].drawY;
				break;
			case 6:
				cg_popup = LoadGraph(_jsonData[messagecnt].draw.c_str());
				popupflg = true;
				popup_size = 0.0f;
				break;
			case 10:
				// ���̃��[�h���폜����
				ModeServer::GetInstance()->Del(this);
				break;
			}

		}
		else if (text_flg && ChrismasTime <= 60)
		{
			ChrismasTime++;
		}
	}
	else
	{
		// ���̃��[�h��艺�̃��C���[��Process()���Ă΂Ȃ�
		ModeServer::GetInstance()->SkipProcessUnderLayer();
		if (_jsonData[messagecnt + 1].command == 50)
		{
			if (trg & PAD_INPUT_1)
			{
				chengeRoom = 1;
				// ���̃��[�h���폜����
				ModeServer::GetInstance()->Del(this);
			}
			if (trg & PAD_INPUT_3)
			{
				chengeRoom = 2;
				// ���̃��[�h���폜����
				ModeServer::GetInstance()->Del(this);
			}
		}
		// �{�^���������ꂽ�玟�̃e�L�X�g��
		else if (trg & PAD_INPUT_2){
			if (text_flg) {
				messagecnt++;
				cg_chara = LoadGraph(_jsonData[messagecnt].draw.c_str());
				_cgBg = LoadGraph(_jsonData[messagecnt].bg.c_str());
				gameCnt = 0;
				popupflg = false;
				//�R�}���h�ʂ̓ǂݍ���
				switch (_jsonData[messagecnt].command) {
				case 1:
					saveMessage[0] = _jsonData[messagecnt].message1;
					save_cgChara[1] = LoadGraph(_jsonData[messagecnt].draw.c_str());
					save_drawX[1] = _jsonData[messagecnt].drawX;
					save_drawY[1] = _jsonData[messagecnt].drawY;
					break;
				case 2:
					saveMessage[1] = _jsonData[messagecnt].message1;
					save_cgChara[0] = LoadGraph(_jsonData[messagecnt].draw.c_str());
					save_drawX[0] = _jsonData[messagecnt].drawX;
					save_drawY[0] = _jsonData[messagecnt].drawY;
					break;
				case 6:
					cg_popup = LoadGraph(_jsonData[messagecnt].draw.c_str());
					popupflg = true;
					popup_size = 0.0f;
					break;
				case 10:
					// ���̃��[�h���폜����
					ModeServer::GetInstance()->Del(this);
					break;
				}

			}
			else
			{
				text_flg = 1;
			}
		}

	}

	int i = messagecnt;
	// ��b�p�[�g����
	const char* Message1_String = _jsonData[messagecnt].message1.c_str();

	if (gameCnt == 0) {
		//�J�E���g�n�̏�����
		drawCnt1 = 0;
		text_flg = 0;
		text_alpha = 0;
		//�摜�E�����ǂݍ���
		//if (!popupflg) { cg_chara = LoadGraph(_jsonData[messagecnt].draw.c_str()); }
		DeleteSoundMem(se_voice);
		se_voice = LoadSoundMem(_jsonData[messagecnt].voice.c_str());
		PlaySoundMem(se_voice, DX_PLAYTYPE_BACK);
	}

	if (_jsonData[messagecnt].command == 0 ||
		_jsonData[messagecnt].command == 1 ||
		_jsonData[messagecnt].command == 2) {
		if (gameCnt % DRAW_STRING_COUNT == DRAW_STRING_COUNT - 1) {
			int CharBytes;
			if (Message1_String[drawCnt1] != '\0')
			{
				CharBytes = GetCharBytes(DX_CHARCODEFORMAT_SHIFTJIS, &Message1_String[drawCnt1]);
				drawCnt1 += CharBytes;		// �`��J�E���^
			}
			else
			{
				text_flg = 1;
			}
		}
	}

	float pop_maxsize = 1.0;
	if (text_flg == 0) {
		//�A�C�e���|�b�v�A�b�v
		if (popupflg == 1) {
			//�|�b�v�A�b�v�̃T�C�Y�㏸
			if (popup_size < pop_maxsize) {
				popup_size += 0.07;
				if (popup_size > pop_maxsize) {
					popup_size = pop_maxsize;
					text_flg = 1;
				}
			}
		}
		//drawcnt���̕����o��
		drawMessage1 = _jsonData[i].message1.substr(0, drawCnt1);
	}
	else
	{
		//�|�b�v�A�b�v�ő�
		popup_size = pop_maxsize;
		//���ׂĂ̕����o��
		drawMessage1 = _jsonData[i].message1;
	}
	gameCnt++;
	return true;
}

bool ModeTalk::Render() {
	base::Render();
	int Font = GetFontSize();
	SetFontSize(128);
	DrawGraph(0, 0, _cgBg, FALSE); //�w�i
	int massagefontsize;	//�t�H���g�T�C�Y
	massagefontsize = 28;		//�t�H���g�T�C�Y
	int namefontsize;
	int savefontsize;
	int zurasi = -10;
	savefontsize = GetFontSize();	//���̃t�H���g�T�C�Y��ۑ�
	switch (_jsonData[messagecnt].command) {
	case 0:
		//����
		//�ꖇ�G�̉摜
		DrawGraph(_jsonData[messagecnt].drawX, _jsonData[messagecnt].drawY, cg_chara, TRUE);
		DrawGraph(472, 844, cg_MessageBox[0], TRUE);
		SetFontSize(massagefontsize);
		DrawFormatString(644, 900, GetColor(255, 255, 255), drawMessage1.c_str());							//�Z���t�`��
		SetFontSize(Font);
		break;
	case 1:
		//��
		//-----------���b�Z�[�W�ǂݍ���----------------
		SetFontSize(massagefontsize);
		if (save_cgChara[1] != 0) {
			DrawGraph(save_drawX[0], save_drawY[0], save_cgChara[0], TRUE);										//�Z�[�u�L�����`��
			DrawGraph(1044, 844, cg_MessageBox[1], TRUE);														//���b�Z�[�W�{�b�N�X�`��
			DrawFormatString(1098 - 10 - zurasi, 920 - 10, GetColor(255, 255, 255), saveMessage[1].c_str());						//�����Z�[�u�Z���t�`��
		}
		//�����w�i
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
		DrawBox(0, 0, 1920, 1080, GetColor(0, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		//
		//�ꖇ�G�̉摜
		DrawGraph(_jsonData[messagecnt].drawX, _jsonData[messagecnt].drawY, cg_chara, TRUE);
		DrawGraph(112, 844, cg_MessageBox[2], TRUE);														//���b�Z�[�W�{�b�N�X�`��
		DrawFormatString(165 - 10 - zurasi, 920 - 10, GetColor(255, 255, 255), drawMessage1.c_str());							//�Z���t�`��
		SetFontSize(Font);
		break;
	case 2:
		//�E
		//-----------���b�Z�[�W�ǂݍ���----------------
		SetFontSize(massagefontsize);
		if (save_cgChara[1] != 0)
		{
			DrawGraph(save_drawX[1], save_drawY[1], save_cgChara[1], TRUE);										//�Z�[�u�L�����`��
			DrawGraph(112, 844, cg_MessageBox[2], TRUE);														//���b�Z�[�W�{�b�N�X�`��
			DrawFormatString(165 - 10 - zurasi, 920 - 10, GetColor(255, 255, 255), saveMessage[0].c_str());						//�E���Z�[�u�Z���t�`��
		}

		//�����w�i
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
		DrawBox(0, 0, 1920, 1080, GetColor(0, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		//
		//�ꖇ�G�̉摜
		DrawGraph(_jsonData[messagecnt].drawX, _jsonData[messagecnt].drawY, cg_chara, TRUE);
		DrawGraph(1044, 844, cg_MessageBox[1], TRUE);															//���b�Z�[�W�{�b�N�X�`��
		DrawFormatString(1098 - 10 - zurasi, 920 - 10, GetColor(255, 255, 255), drawMessage1.c_str());				//�Z���t�`��

		SetFontSize(Font);
		break;
	case 3:
		//��
		//-----------���b�Z�[�W�ǂݍ���----------------
		SetFontSize(massagefontsize);
		DrawGraph(save_drawX[0], save_drawY[0], save_cgChara[0], TRUE);										//�Z�[�u�L�����`��
		DrawGraph(1044, 844, cg_MessageBox[1], TRUE);														//���b�Z�[�W�{�b�N�X�`��
		DrawFormatString(1098 - 10, 920 - 10, GetColor(255, 255, 255), saveMessage[1].c_str());						//�����Z�[�u�Z���t�`��
		//�ꖇ�G�̉摜
		DrawGraph(_jsonData[messagecnt].drawX, _jsonData[messagecnt].drawY, cg_chara, TRUE);
		DrawGraph(112, 844, cg_MessageBox[2], TRUE);														//���b�Z�[�W�{�b�N�X�`��
		DrawFormatString(165 - 10, 920 - 10, GetColor(255, 255, 255), drawMessage1.c_str());							//�Z���t�`��
		SetFontSize(Font);
		break;
	case 4:
		//�E
		//-----------���b�Z�[�W�ǂݍ���----------------
		SetFontSize(massagefontsize);
		if (save_cgChara[1] != 0) {
			DrawGraph(save_drawX[1], save_drawY[1], save_cgChara[1], TRUE);										//�Z�[�u�L�����`��
			DrawGraph(112, 844, cg_MessageBox[2], TRUE);														//���b�Z�[�W�{�b�N�X�`��
			DrawFormatString(165 - 10, 920 - 10, GetColor(255, 255, 255), saveMessage[0].c_str());						//�E���Z�[�u�Z���t�`��
		}

		//�ꖇ�G�̉摜
		DrawGraph(save_drawX[0], save_drawY[0], save_cgChara[0], TRUE);										//�Z�[�u�L�����`��
		DrawGraph(1044, 844, cg_MessageBox[1], TRUE);														//���b�Z�[�W�{�b�N�X�`��
		DrawFormatString(1098 - 10, 920 - 10, GetColor(255, 255, 255), saveMessage[1].c_str());						//�����Z�[�u�Z���t�`��

		SetFontSize(Font);
		break;
	case 6:
		//�����Â�
		//-----------���b�Z�[�W�ǂݍ���----------------

		SetFontSize(massagefontsize);


		DrawGraph(save_drawX[1], save_drawY[1], save_cgChara[1], TRUE);										//�Z�[�u�L�����`��
		DrawGraph(112, 844, cg_MessageBox[2], TRUE);														//���b�Z�[�W�{�b�N�X�`��
		DrawFormatString(165 - 10, 920 - 10, GetColor(255, 255, 255), saveMessage[0].c_str());				//�E���Z�[�u�Z���t�`��

		DrawGraph(save_drawX[0], save_drawY[0], save_cgChara[0], TRUE);										//�Z�[�u�L�����`��
		DrawGraph(1044, 844, cg_MessageBox[1], TRUE);														//���b�Z�[�W�{�b�N�X�`��
		DrawFormatString(1098 - 10, 920 - 10, GetColor(255, 255, 255), saveMessage[1].c_str());				//�����Z�[�u�Z���t�`��

		//�����w�i
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
		DrawBox(0, 0, 1920, 1080, GetColor(0, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		break;
	}
	//�A�C�e���|�b�v�A�b�v
	if (popupflg == 1) {
		//�����w�i
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
		DrawBox(0, 0, 1920, 1080, GetColor(0, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		DrawRotaGraph(960, 420, popup_size, 0, cg_popup, TRUE);
	}

	return true;
}

