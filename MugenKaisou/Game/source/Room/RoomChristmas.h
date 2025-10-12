#include "RoomBase.h"

class RoomChristmas : public RoomBase
{
public:
	RoomChristmas();				// インストラクタ
	virtual ~RoomChristmas();	// デストラクタ

	void CharaMove(Chara& chara, Camera& cam, VECTOR& v, VECTOR oldv);
	void Process(Chara& chara, Camera& cam, VECTOR& v, VECTOR oldv);
	void CameraProcess(Camera& cam);
	void Render(VECTOR vPos, bool viewColl);
public:
	MyMath mymath;
	int _cgBg;
};
