#include "RoomBase.h"

class RoomPizza : public RoomBase
{
public:
	RoomPizza();			// インストラクタ
	virtual ~RoomPizza();	// デストラクタ

	void Process(Chara& chara, Camera& cam, VECTOR& v, VECTOR oldv);
	void CameraProcess(Camera& cam);
	void Render(VECTOR vPos, bool viewColl);
public:
	// ピザ
	Pizza pizza;
	std::vector<Pizza> _vPizza;		// ピザ
	// ベルトコンベア
	BeltConveyor beltConv;
};
