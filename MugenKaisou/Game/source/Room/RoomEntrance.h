#include "RoomBase.h"

class RoomEntrance : public RoomBase
{
public:
	RoomEntrance();				// インストラクタ
	virtual ~RoomEntrance();	// デストラクタ

	void CharaMove(Chara& chara, Camera& cam, VECTOR& v, VECTOR oldv);
	void Process(Chara& chara, Camera& cam, VECTOR& v, VECTOR oldv);
	void CameraProcess(Camera& cam);
	void Render(VECTOR vPos, bool viewColl);
public:
	MyMath mymath;
	bool flgEffect;
};
