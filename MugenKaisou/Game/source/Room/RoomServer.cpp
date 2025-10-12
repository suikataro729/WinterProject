#include "RoomServer.h"
#include "RoomEntrance.h"
#include "RoomPizza.h"
#include "RoomSlidePuzzle.h"
#include "RoomMuseum.h"
#include "RoomFan.h"
#include "RoomCalcLabyrinth.h"
#include "RoomGrave.h"
#include "RoomCalcHighLevel.h"
#include "RoomChristmas.h"

#include "../ApplicationGlobal.h"

RoomBase* gRoom;

RoomServer::RoomServer() {
	gRoom = NULL;
}

RoomServer::~RoomServer() {

}

void RoomServer::SetSpown(Chara& chara, Camera& cam) {
	gRoom->SetSpown(chara, cam);
}

void RoomServer::Reset() {
	gRoom->Reset();
}

void RoomServer::Process(Chara& chara, Camera& cam, VECTOR& v, VECTOR oldv) {
	gRoom->Process(chara, cam, v, oldv);
}

void RoomServer::CameraProcess(Camera& cam) {
	gRoom->CameraProcess(cam);
}

void RoomServer::Render(VECTOR vPos, bool viewColl) {
	gRoom->Render(vPos, viewColl);
}

void RoomServer::ChangeRoom(int keyRoom) {
	delete gRoom;

	switch (keyRoom) {
	// エントランス(0000)
	case 0:
		// 次の部屋番号設定
		gGlobal.keyNextRoom = 1109;
		gGlobal.keyLoseRoom = 1109;
		//ゲームカウント初期化
		gamecntdown = -999;		//時間なし
		gRoom = new RoomEntrance();
		break;
	// 101回目の誕生日部屋（墓場）(2126)
	case 2126:
		// 次の部屋番号設定
		gGlobal.keyNextRoom = 1225;
		gGlobal.keyLoseRoom = 1225;
		//ゲームカウント初期化
		gamecntdown = 6000;		//999秒
		gRoom = new RoomGrave();
		break;
	// ピザ部屋(6212)
	case 6212:
		// 次の部屋番号設定
		gGlobal.keyNextRoom = 4226;
		gGlobal.keyLoseRoom = 1114;
		//ゲームカウント初期化
		gamecntdown = 5940;		//99秒
		gRoom = new RoomPizza();
		break;
	// スライド部屋(1109, 4226)
	case 1109:
		// 次の部屋番号設定
		gGlobal.keyNextRoom = 311;
		gGlobal.keyLoseRoom = 1114;
		//ゲームカウント初期化
		gamecntdown = 6600;		//110秒
		gRoom = new RoomSlidePuzzle();
		break;
	case 4226:
		// 次の部屋番号設定
		gGlobal.keyNextRoom = 1114;
		gGlobal.keyLoseRoom = 1114;
		//ゲームカウント初期化
		gamecntdown = 6600;		//99秒
		gRoom = new RoomSlidePuzzle();
		break;
	// 博物館部屋(1114)
	case 1114:
		// 次の部屋番号設定
		gGlobal.keyNextRoom = 223;
		gGlobal.keyLoseRoom = 1225;
		//ゲームカウント初期化
		gamecntdown = 9000;		//99秒
		gRoom = new RoomMuseum();
		break;
	// プログラム部屋(0223)
	case 223:
		// 次の部屋番号設定
		gGlobal.keyNextRoom = 3215;
		gGlobal.keyLoseRoom = 1225;
		//ゲームカウント初期化
		gamecntdown = 6000;		//999秒
		gRoom = new RoomFan();
		break;
	// 計算（迷宮）部屋(0311)
	case 311:
		// 次の部屋番号設定
		gGlobal.keyNextRoom = 6212;
		gGlobal.keyLoseRoom = 1114;
		//ゲームカウント初期化
		gamecntdown = 900;		//15秒
		gRoom = new RoomCalcLabyrinth();
		break;
	// 計算（迷宮）部屋上級(3215)
	case 3215:
		// 次の部屋番号設定
		gGlobal.keyNextRoom = 1225;
		gGlobal.keyLoseRoom = 1225;
		//ゲームカウント初期化
		gamecntdown = 6000;		//999秒
		gRoom = new RoomCalcHighLevel();
		break;
	// クリスマス部屋(1225)
	case 1225:
		// 次の部屋番号設定
		gGlobal.keyNextRoom = 0;
		gGlobal.keyLoseRoom = 0;
		//ゲームカウント初期化
		gamecntdown = 4000;		//999秒
		gRoom = new RoomChristmas();
		break;
	}
}
