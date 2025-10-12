#include "RoomBase.h"

class RoomPizza : public RoomBase
{
public:
	RoomPizza();			// �C���X�g���N�^
	virtual ~RoomPizza();	// �f�X�g���N�^

	void Process(Chara& chara, Camera& cam, VECTOR& v, VECTOR oldv);
	void CameraProcess(Camera& cam);
	void Render(VECTOR vPos, bool viewColl);
public:
	// �s�U
	Pizza pizza;
	std::vector<Pizza> _vPizza;		// �s�U
	// �x���g�R���x�A
	BeltConveyor beltConv;
};
