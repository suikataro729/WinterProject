#pragma once

#include "RoomBase.h"
#include <string>

class RoomServer
{
public:
	RoomServer();
	virtual ~RoomServer();

	void SetSpown(Chara& chara, Camera& cam);
	void Reset();
	void Process(Chara& chara, Camera& cam, VECTOR& v, VECTOR oldv);
	void CameraProcess(Camera& cam);
	void Render(VECTOR vPos, bool viewColl);
	void ChangeRoom(int keyRoom);
};
