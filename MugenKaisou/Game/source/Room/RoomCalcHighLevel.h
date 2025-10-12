#include "RoomBase.h"

class RoomCalcHighLevel : public RoomBase
{
public:
	RoomCalcHighLevel();			// インストラクタ
	virtual ~RoomCalcHighLevel();	// デストラクタ

	void Process(Chara& chara, Camera& cam, VECTOR& v, VECTOR oldv);
	void CameraProcess(Camera& cam);
	void Render(VECTOR vPos, bool viewColl);
public:
	// ベルトコンベア
	BeltConveyor beltConv;
};
