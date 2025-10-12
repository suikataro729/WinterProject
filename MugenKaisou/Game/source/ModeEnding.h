
#include "appframe.h"
#include <string>
#include <vector>
#include	<iostream>
#include	<fstream>

// ���[�h
class ModeEnding : public ModeBase
{
	typedef ModeBase base;
public:
	virtual bool Initialize();
	virtual bool Process();
	virtual bool Render();

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


	int _Keynum[5];

	int gKey;
	int gRel;
	int gTrg;
	bool Keyflg;
	bool CodeButtonflg;
	int Keycnt;
	int codesave;
	int jsonMax;

	bool ResetGame;
};
