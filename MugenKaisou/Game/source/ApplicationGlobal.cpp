
#include "AppFrame.h"
#include "ApplicationGlobal.h"

// 実体
ApplicationGlobal		gGlobal;
RoomData				rData;

ApplicationGlobal::ApplicationGlobal() {
}

ApplicationGlobal::~ApplicationGlobal() {
}


bool ApplicationGlobal::Init() {
	_cgCursor = LoadGraph("res/cursor.png");

	// 部屋番号用
	keyNowRoom = 0;
	keyNextRoom = 0;
	keyLoseRoom = 0;

	// フェード用
	_isFinishFadeIn = false;
	_isFinishFadeOut = false;
	_deleteFade = false;

	return true;
}

// ピザ出現フラグ（右側でピザを注文したら、TURE）
bool gPizza = 0;

// キャラクタの死亡フラグ
bool gChara_Dead = 0;

int gCode[20];

// 動かすブロック情報
int gMovemap_num = 0;	//動かすmap番号
int gMoverot = 0;		//動かす方向  1:右 2:左 3;上 4;下

// ドア切り替え用
int gChangeDoor;

// 部屋番号
int keyRoom = 0;

int gamecntdown;
bool respown_flg;

//プロペラ部屋関連
float FanSpeed = 0.15f;

//仮データ
int SaveRoot[] = { 0,0,0,0,0,0,0,0,0,0 };
//int SaveRoot[] = { 1,1,1,1,1,1,1,1,1,1 };

int RoomClear[] = { 0,0,0,0,0,0,0,0,0,0 };		//0:クリアしてない、1:クリア済み
//int RoomClear[] = { 1,1,1,1,1,1,1,1,1,1 };		//0:クリアしてない、1:クリア済み

//0:slidepuzzle1 1:slidepuzzle5 2:slidepuzzle3 3:timeflag 4:respawn 5:pizza2 6:pizza4 7:meteorite2 8:meteorite3 9:calculation2 10:entrance4 
// 11:entrance5 12:christmas 13:museum1 14:pizza2 15:meteorite4 16:entranceend 17:calculationB3 18:grave4 19:meteorite1 20:grave1 21:
bool TalkFlg[] = { FALSE };

bool FullScreenFlg;

//0: 初期値 1:その部屋のまま 2:部屋交換
int chengeRoom;