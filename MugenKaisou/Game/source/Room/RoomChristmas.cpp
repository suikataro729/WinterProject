#include "../ApplicationGlobal.h"
#include "RoomChristmas.h"
#include "../ModeTalk.h"
#include "../ModeRoomNumber.h"

RoomChristmas::RoomChristmas() {
	FullScreenFlg = TRUE;
	SaveRoot[9] = 1;
	_cgBg = LoadGraph("res/UI/kaiwapart.jpg");
}

RoomChristmas::~RoomChristmas() {

}

void RoomChristmas::CharaMove(Chara& chara, Camera& cam, VECTOR& v, VECTOR oldv) {
	
}

void RoomChristmas::Process(Chara& chara, Camera& cam, VECTOR& v, VECTOR oldv) {
	if (gamecntdown < 0) {
		chara._flgExit = 1;
		RoomClear[9] = 1;
	}
	if (!TalkFlg[12])
	{
		ModeTalk* modetalk = new ModeTalk("res/jsonfile/TextData/christmas.json",TRUE);
		// ModeGameÇÊÇËè„ÇÃÉåÉCÉÑÅ[Ç…ÉgÅ[ÉNÇìoò^Ç∑ÇÈ
		ModeServer::GetInstance()->Add(modetalk, 200, "talk");

		TalkFlg[12] = TRUE;
	}
	chara._vPos = VGet(0, 2000, 0);
}

void RoomChristmas::CameraProcess(Camera& cam) {
	
}

void RoomChristmas::Render(VECTOR vPos, bool viewColl) {
	DrawGraph(0, 0, _cgBg, FALSE); //îwåi
}
