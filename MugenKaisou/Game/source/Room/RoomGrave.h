#include "RoomBase.h"

class RoomGrave : public RoomBase
{
public:
	RoomGrave();				// �C���X�g���N�^
	virtual ~RoomGrave();	// �f�X�g���N�^

	void CharaMove(Chara& chara, Camera& cam, VECTOR& v, VECTOR oldv);
	void Process(Chara& chara, Camera& cam, VECTOR& v, VECTOR oldv);
	void CameraProcess(Camera& cam);
	void Render(VECTOR vPos, bool viewColl);
public:
	MyMath mymath;
	bool flgEffect;

	// �s�U
	Pizza pizza;
	std::vector<Pizza> _vPizza;
};
