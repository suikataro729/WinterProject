
#include "appframe.h"
#include <string>
#include <vector>
#include	<iostream>
#include	<fstream>

// モード
class ModeEnding : public ModeBase
{
	typedef ModeBase base;
public:
	virtual bool Initialize();
	virtual bool Process();
	virtual bool Render();

private:
	//画像描画関連
	int cgwindow[20];
	int cgNum[10];
	int cgLabyNum[10];
	int cgCalc[2];		//0:足し算　1:掛け算
	int cgAns[2];		//0:誤答　1:正解
	int cgNotNum;
	int cgNumFrame;
	int cgButton;
	int cgBase[3];
	int cgQP_Base[2];
	int cgFullUI;
	int cglabel[12];
	//0:ベース 1:タイル(1*1) 2:タイル(灰色) 3:タイル(1*2) 4:タイル(1*3) 5:タイル(2*4) 6:タイル(3*2)
	int cgBlock[30];
	int cgDialy[11];
	int cgAreaMapUI[2];
	int cgAreaMapEmpty[4];
	int cgAreaMapNum[2][11];		//0:白、1:黄色


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
