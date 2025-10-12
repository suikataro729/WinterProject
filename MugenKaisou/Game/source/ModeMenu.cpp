
#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ApplicationGlobal.h"
#include "ModeMenu.h"


bool ModeMenu::Initialize() {
	if (!base::Initialize()) { return false; }

	_curPos = 0;
	_curAnimCnt = 0;

	return true;
}

bool ModeMenu::Terminate() {
	base::Terminate();
	Clear();
	return true;
}

void ModeMenu::Clear() {
	// �o�^����item��S���폜����
	for (auto ite = _vItems.begin(); ite != _vItems.end();) {
		delete (*ite);
		ite = _vItems.erase(ite);
	}
}

void ModeMenu::Add(MenuItemBase* itemBase) {
	_vItems.push_back(itemBase);
}

bool ModeMenu::Process() {
	base::Process();
	int key = ApplicationMain::GetInstance()->GetKey();
	int trg = ApplicationMain::GetInstance()->GetTrg();

	// ���̃��[�h��艺�̃��C���[��Process()���Ă΂Ȃ�
	ModeServer::GetInstance()->SkipProcessUnderLayer();


	// ESC�L�[�Ń��j���[�����
	bool close = false;
	if (trg & PAD_INPUT_9) {
		close = true;
	}

	// �㉺�ŃJ�[�\�����ړ�����
	if (trg & PAD_INPUT_UP) { _curPos--; _curAnimCnt = 0; }
	if (trg & PAD_INPUT_DOWN) { _curPos++; _curAnimCnt = 0; }

	// �J�[�\���ʒu���㉺���[�v
	int itemNum = _vItems.size();
	_curPos = (_curPos + itemNum) % itemNum;

	// ����ŃA�C�e����Selected()���Ă�
	if (trg & PAD_INPUT_1) {
		int ret = _vItems[_curPos]->Selected();
		if (ret == 1) {
			// ���j���[�����
			close = true;
		}
	}


	// ���j���[�����
	if (close) {
		// ���̃��[�h���폜����
		ModeServer::GetInstance()->Del(this);
	}

	// �J�[�\���A�j���J�E���^
	_curAnimCnt++;


	return true;
}

bool ModeMenu::Render() {
	base::Render();

	SetDrawArea(0, 0, 1920, 1080);
	// ���j���[���ڂ̊m�F
	int x = 128, y = 128, w = 0, h = 0, fontSize = 32, fontPitch = fontSize + 8;
	SetFontSize(fontSize);
	for (auto ite = _vItems.begin(); ite != _vItems.end();ite++) {
		int item_w = GetDrawStringWidth((*ite)->_text.c_str(), strlen((*ite)->_text.c_str()));
		if (w < item_w) {
			w = item_w;
		}
		h += fontPitch;
	}
	// �J�[�\��, �g���̃T�C�Y�g��
	w += 64 + 16; h += 16;

	// ���n�̕`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawBox(x, y, x + w, y + h, GetColor(0, 0, 255), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawBox(x, y, x + w, y + h, GetColor(0, 0, 255), TRUE);

	// ���j���[���ڂ̕`��
	int startY = 16 / 2;
	h = 0;
	for (auto ite = _vItems.begin(); ite != _vItems.end(); ite++) {
		DrawString(x + 64, y + startY + h, (*ite)->_text.c_str(), GetColor(255,0,0));
		h += fontPitch;
	}
	// �J�[�\���̕`��
	// x���W�̓A�j���[�V��������
	DrawGraph(x + 4 + ( (_curAnimCnt/6) % 4 ) * 4, y + startY + fontPitch * _curPos, gGlobal._cgCursor, TRUE);

	return true;
}

