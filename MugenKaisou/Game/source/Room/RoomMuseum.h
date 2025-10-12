#include "RoomBase.h"

class RoomMuseum : public RoomBase
{
public:
	RoomMuseum();				// インストラクタ
	virtual ~RoomMuseum();	// デストラクタ

	void CharaMove(Chara& chara, Camera& cam, VECTOR& v, VECTOR oldv);
	void Process(Chara& chara, Camera& cam, VECTOR& v, VECTOR oldv);
	void CameraProcess(Camera& cam);
	void Render(VECTOR vPos, bool viewColl);
public:
	
};
