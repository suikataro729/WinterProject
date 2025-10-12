#include "appframe.h"
#include "Room/RoomData.h"
#include "Fade.h"

class ApplicationGlobal
{
public:
	ApplicationGlobal();
	virtual ~ApplicationGlobal();

	bool Init();
public:
	int _cgCursor;

	// 部屋番号用
	int keyNowRoom;
	int keyNextRoom;
	int keyLoseRoom;

	// フェード用
	bool _isFinishFadeIn, _isFinishFadeOut;
	bool _deleteFade;
};

// 部屋（マップ）データ
extern RoomData rData;

// ピザ出現フラグ（右側でピザを注文したら、TURE）
extern bool gPizza;

// キャラクタの死亡フラグ
extern bool gChara_Dead;

extern int gCode[20];

//プロペラ部屋関連
extern float FanSpeed;

// 動かすブロック情報
extern int gMovemap_num;	//動かすmap番号
extern int gMoverot;		//動かす方向  1:右 2:左 3;上 4;下

// ドア切り替え用
extern int gChangeDoor;		// 0:通常ドア, 1:隠しドア

// 部屋番号
extern int keyRoom;

// 他のソースでgGlobalを使えるように
extern ApplicationGlobal		gGlobal;

// 残り時間
extern int gamecntdown;

// リスポーン用フラグ
extern bool respown_flg;

extern int SaveRoot[10];		//0:通っていない、1:通過済み

extern int RoomClear[10];		//0:クリアしてない、1:クリア済み

extern bool TalkFlg[99];

extern bool FullScreenFlg;

extern int chengeRoom;