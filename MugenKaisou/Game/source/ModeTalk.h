
#include "appframe.h"

#include	<iostream>
#include	<vector>
#include	<string>
#include	<fstream>
#include	"nlohmann/json.hpp"

#define	DRAW_STRING_COUNT	(4)		// �`��^�C�~���O�̃J�E���^

// ���[�h
class ModeTalk : public ModeBase
{
	typedef ModeBase base;
	
public:
	ModeTalk(std::string TextHandle, bool Cristmas = FALSE);
	~ModeTalk();
	virtual bool Initialize();
	virtual bool Process();
	virtual bool Render();

	Useful USEFUL;
protected:
	// json����ǂݍ��񂾃f�[�^
	struct JsonData {
		std::string draw;
		std::string bg;
		int drawX, drawY, bgY;
		std::string name;
		std::string message1;
		std::string message2;
		std::string voice;

		// �R�}���h�n
		//	0:�Z���t���蒆�� 1:�Z���t���荶 2:�Z���t����E 3:���w�i�Ȃ��Z���t���荶 4:���w�i�Ȃ��Z���t����E 6:�A�C�e���z�b�v�A�b�v 10:��b�I��
		int command;
	};
	JsonData _jsonData[999];

	std::string saveMessage[2];		//0:�� 1:�E
	int save_cgChara[2];
	int save_drawX[2];
	int save_drawY[2];
	int gameCnt;
	int cg_chara;
	int se_voice;
	int _cgBg;
	int messagecnt;
	int cg_MessageBox[3];

	//�A�C�e���|�b�v�A�b�v
	int popupflg;
	float popup_size;
	int cg_popup;

	//��b�J�E���g
	int drawCnt1;
	std::string drawMessage1;				// �`�悷�镶����i1�s�j

	//�e�L�X�g����摜�֌W
	int text_alpha;
	int cgtext;
	int add;
	int text_flg;		//�e�L�X�g�摜�̏o���t���O

	bool ChrismasFlg; // �N���X�}�X�����p�t���O
	int ChrismasTime; // �N���X�}�X�����p��b����
}; 
