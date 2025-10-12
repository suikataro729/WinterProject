
#include "appframe.h"

#include	<iostream>
#include	<vector>
#include	<string>
#include	<fstream>
#include	"nlohmann/json.hpp"

#define	DRAW_STRING_COUNT	(4)		// 描画タイミングのカウンタ

// モード
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
	// jsonから読み込んだデータ
	struct JsonData {
		std::string draw;
		std::string bg;
		int drawX, drawY, bgY;
		std::string name;
		std::string message1;
		std::string message2;
		std::string voice;

		// コマンド系
		//	0:セリフ送り中央 1:セリフ送り左 2:セリフ送り右 3:黒背景なしセリフ送り左 4:黒背景なしセリフ送り右 6:アイテムホップアップ 10:会話終了
		int command;
	};
	JsonData _jsonData[999];

	std::string saveMessage[2];		//0:左 1:右
	int save_cgChara[2];
	int save_drawX[2];
	int save_drawY[2];
	int gameCnt;
	int cg_chara;
	int se_voice;
	int _cgBg;
	int messagecnt;
	int cg_MessageBox[3];

	//アイテムポップアップ
	int popupflg;
	float popup_size;
	int cg_popup;

	//会話カウント
	int drawCnt1;
	std::string drawMessage1;				// 描画する文字列（1行）

	//テキスト送り画像関係
	int text_alpha;
	int cgtext;
	int add;
	int text_flg;		//テキスト画像の出現フラグ

	bool ChrismasFlg; // クリスマス部屋用フラグ
	int ChrismasTime; // クリスマス部屋用会話時間
}; 
