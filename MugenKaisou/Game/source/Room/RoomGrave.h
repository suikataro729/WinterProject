#include "RoomBase.h"

class RoomGrave : public RoomBase
{
public:
	RoomGrave();				// インストラクタ
	virtual ~RoomGrave();	// デストラクタ

	void CharaMove(Chara& chara, Camera& cam, VECTOR& v, VECTOR oldv);
	void Process(Chara& chara, Camera& cam, VECTOR& v, VECTOR oldv);
	void CameraProcess(Camera& cam);
	void Render(VECTOR vPos, bool viewColl);
public:
	MyMath mymath;
	bool flgEffect;

	// ピザ
	Pizza pizza;
	std::vector<Pizza> _vPizza;
};
