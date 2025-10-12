
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

// モード
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

	//音素材
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

	// 1:右 2:左 3;上 4;下
	int dirflg;		//ブロックずらし

	int savemap_num1 = 0;
	int savemap_num2 = 0;
	int m = 0;
	// 実装用データ
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
	int map1[MAP_W_1 * MAP_H_1];		//	マップ1
	int map2[MAP_W_2 * MAP_H_2];		//	マップ2
	int oldmap1[MAP_W_1 * MAP_H_1];		//	元マップ1
	int oldmap2[MAP_W_2 * MAP_H_2];		//	元マップ2
	int num = 0;
	bool reset = 0;

	bool CheckButton;
	int pageMax;		//ページの最大
	int pagenum;		//今のページ
	int gRot;

	// jsonから読み込んだデータ
	struct CodeSave {
		bool usecheck;
		int codesave;			//保存された番号
	};
	CodeSave _codesave[20];

	//問題部屋で使用する入力数字
	int Q_Keynum[3];
	bool Q_ans;				//プレイヤーの答え
	int Q_savenum;			//プレイヤーの答え保存
	int _Q_savenum[3][5];			//プレイヤーの答え保存

	//問題部屋で使用する計算
	int Q_quest1[5];			//左項
	int Q_quest2[5];			//右項
	int Q_operator[5];			//演算子
	int Q_answer[5];			//答え
	int Q_correct[5];			//正解判定 0:初期値、1:正解、2:誤答

	bool Q_stepflg;			//4回目のエンターキー押下判定
	int QnowQuest;			//今の問題

	//問題部屋上級で使用する入力数字
	int QP_Keynum[5];
	bool QP_ans;				//プレイヤーの答え
	int QP_savenum;			//プレイヤーの答え保存
	int _QP_savenum[3][5];			//プレイヤーの答え保存

	//問題部屋上級で使用する計算
	int QP_quest1[5];			//左項
	int QP_quest2[5];			//右項
	int QP_operator[5];			//演算子
	int QP_answer[5];			//答え
	int QP_correct[5];			//正解判定 0:初期値、1:正解、2:誤答

	bool QP_stepflg;			//4回目のエンターキー押下判定
	int QPnowQuest;			//今の問題

	int QP_step;			//問題の回数
	//プロペラ部屋で使用する入力数字
	int P_Keynum[3];
	bool P_ans;				//プレイヤーの答え
	int P_savenum;			//プレイヤーの答え保存

	int saveW, saveH;			//指した画像の地点の保存
	int nowPuzzleNum;			//今さしているパズル
	//パズル
	struct Puzzle {
		int drawOrder;			//描画順
		int x, y;				//座標	
		int w, h;				//サイズ
		std::string cghandle;			//ハンドル名
		int cgpuzzle;			//パズル画像保存先
	};
	//x座標、y座標、w幅、h高さ、画像ハンドル
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


	//カラーテーブル
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
	// jsonから読み込んだデータ
	struct JsonData {
		std::string draw;
		int draw_h;
		int code;			//4桁番号
	};
	JsonData _jsonData[20];


};
