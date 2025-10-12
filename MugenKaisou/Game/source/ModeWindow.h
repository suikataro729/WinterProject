
#include "appframe.h"
#include "nlohmann/json.hpp"
#include <string>
#include <vector>
#include	<iostream>
#include	<fstream>

#define MAP_W_1 9
#define MAP_H_1 6

#define MAP_W_2 6
#define MAP_H_2 8

// ���[�h
class ModeWindow : public ModeBase
{
	typedef ModeBase base;
public:
	virtual bool Initialize();
	virtual bool Process();
	virtual bool Render();

	void AddSaveCode(int codesave);
	bool CheckCode(int codesave);
	void SetCode(int& codesave);
	Useful USEFUL;

private:
	//�摜�`��֘A
	int cgwindow[20];
	int cgNum[10];
	int cgLabyNum[10];
	int cgCalc[2];		//0:�����Z�@1:�|���Z
	int cgAns[2];		//0:�듚�@1:����
	int cgNotNum;
	int cgNumFrame;
	int cgButton;
	int cgBase[3];
	int cgQP_Base[2];
	int cgFullUI;
	int cglabel[12];
	//0:�x�[�X 1:�^�C��(1*1) 2:�^�C��(�D�F) 3:�^�C��(1*2) 4:�^�C��(1*3) 5:�^�C��(2*4) 6:�^�C��(3*2)
	int cgBlock[30];
	int cgDialy[11];
	int cgAreaMapUI[2];
	int cgAreaMapEmpty[4];
	int cgAreaMapNum[2][11];		//0:���A1:���F

	//���f��
	// 0:numberclick 1:page 2:slide 3:propeller
	int se[4];

	int _Keynum[5];

	int gKey;
	int gRel;
	int gTrg;
	bool Keyflg;
	bool CodeButtonflg;
	int Keycnt;
	int codesave;
	int jsonMax;

	int savemouseX[2];
	int savemouseY[2];
	VECTOR MouseLine;

	// 1:�E 2:�� 3;�� 4;��
	int dirflg;		//�u���b�N���炵

	int savemap_num1 = 0;
	int savemap_num2 = 0;
	int m = 0;
	// �����p�f�[�^
	int SlidePuzzle1[MAP_W_1 * MAP_H_1] = {
	99, 99, 99, 99, 99, 99, 99, 99, 99,
	99,  1,  1, 12, 12, 12,  1,  1, 99,
	99,  1, 11, 14, 14, 15,  1, 98, 99,
	99,  1, 11, 14, 14, 16,  1, 98, 99,
	99,  1,  1, 13, 13, 13,  1,  1, 99,
	99, 99, 99, 99, 99, 99, 99, 99, 99
	};
	int SlidePuzzle2[MAP_W_2 * MAP_H_2] = {
	99, 99, 99, 99, 99, 99,
	99,  1,  1,  1,  1, 99,
	99, 22, 23, 24, 24, 99,
	99, 25, 21, 21, 26, 99,
	99, 25, 21, 21, 26, 99,
	99, 27, 27, 28, 29, 99,
	99,  1, 98, 98,  1, 99,
	99, 99, 99, 99, 99, 99
	};
	int map1[MAP_W_1 * MAP_H_1];		//	�}�b�v1
	int map2[MAP_W_2 * MAP_H_2];		//	�}�b�v2
	int oldmap1[MAP_W_1 * MAP_H_1];		//	���}�b�v1
	int oldmap2[MAP_W_2 * MAP_H_2];		//	���}�b�v2
	int num = 0;
	bool reset = 0;

	bool CheckButton;
	int pageMax;		//�y�[�W�̍ő�
	int pagenum;		//���̃y�[�W
	int gRot;

	// json����ǂݍ��񂾃f�[�^
	struct CodeSave {
		bool usecheck;
		int codesave;			//�ۑ����ꂽ�ԍ�
	};
	CodeSave _codesave[20];

	//��蕔���Ŏg�p������͐���
	int Q_Keynum[3];
	bool Q_ans;				//�v���C���[�̓���
	int Q_savenum;			//�v���C���[�̓����ۑ�
	int _Q_savenum[3][5];			//�v���C���[�̓����ۑ�

	//��蕔���Ŏg�p����v�Z
	int Q_quest1[5];			//����
	int Q_quest2[5];			//�E��
	int Q_operator[5];			//���Z�q
	int Q_answer[5];			//����
	int Q_correct[5];			//���𔻒� 0:�����l�A1:�����A2:�듚

	bool Q_stepflg;			//4��ڂ̃G���^�[�L�[��������
	int QnowQuest;			//���̖��

	//��蕔���㋉�Ŏg�p������͐���
	int QP_Keynum[5];
	bool QP_ans;				//�v���C���[�̓���
	int QP_savenum;			//�v���C���[�̓����ۑ�
	int _QP_savenum[3][5];			//�v���C���[�̓����ۑ�

	//��蕔���㋉�Ŏg�p����v�Z
	int QP_quest1[5];			//����
	int QP_quest2[5];			//�E��
	int QP_operator[5];			//���Z�q
	int QP_answer[5];			//����
	int QP_correct[5];			//���𔻒� 0:�����l�A1:�����A2:�듚

	bool QP_stepflg;			//4��ڂ̃G���^�[�L�[��������
	int QPnowQuest;			//���̖��

	int QP_step;			//���̉�
	//�v���y�������Ŏg�p������͐���
	int P_Keynum[3];
	bool P_ans;				//�v���C���[�̓���
	int P_savenum;			//�v���C���[�̓����ۑ�

	int saveW, saveH;			//�w�����摜�̒n�_�̕ۑ�
	int nowPuzzleNum;			//�������Ă���p�Y��
	//�p�Y��
	struct Puzzle {
		int drawOrder;			//�`�揇
		int x, y;				//���W	
		int w, h;				//�T�C�Y
		std::string cghandle;			//�n���h����
		int cgpuzzle;			//�p�Y���摜�ۑ���
	};
	//x���W�Ay���W�Aw���Ah�����A�摜�n���h��
	Puzzle _puzzle[9] = {
		{0, 0, 0, 97, 195,"res/Window/Museum/1.png"},
		{0, 0, 0, 161, 252,"res/Window/Museum/2.png"},
		{0, 0, 0, 301, 187,"res/Window/Museum/3.png"},
		{0, 0, 0, 210, 298,"res/Window/Museum/4.png"},
		{0, 0, 0, 201, 254,"res/Window/Museum/5.png"},
		{0, 0, 0, 312, 231,"res/Window/Museum/6.png"},
		{0, 0, 0, 178, 210,"res/Window/Museum/7.png"},
		{0, 0, 0, 222, 179,"res/Window/Museum/8.png"},
		{0, 0, 0, 152, 248,"res/Window/Museum/9.png"}
	};


	//�J���[�e�[�u��
	struct ColorTbl {
		int r, g, b;				//RGB
	};
	ColorTbl _Color[21] = {
		{ 50, 0 , 0},
		{ 0, 50 , 0},
		{ 0, 0 , 50},
		{ 50, 50 , 0},
		{ 50, 0 , 50},
		{ 0, 50 , 50},
		{ 50, 50 , 50},
		{ 100, 0 , 0},
		{ 0, 100 , 0},
		{ 0, 0 , 100},
		{ 100, 100 , 0},
		{ 0, 100 , 100},
		{ 100, 0 , 100},
		{ 100, 100 , 100},
		{ 200, 0 , 0},
		{ 0, 200 , 0},
		{ 0, 0 , 200},
		{ 200, 200 , 0},
		{ 0, 200 , 200},
		{ 200, 0 , 200},

	};
protected:
	// json����ǂݍ��񂾃f�[�^
	struct JsonData {
		std::string draw;
		int draw_h;
		int code;			//4���ԍ�
	};
	JsonData _jsonData[20];


};
