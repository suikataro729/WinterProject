#include "RoomBase.h"

class RoomMuseum : public RoomBase
{
public:
	RoomMuseum();				// �C���X�g���N�^
	virtual ~RoomMuseum();	// �f�X�g���N�^

	void CharaMove(Chara& chara, Camera& cam, VECTOR& v, VECTOR oldv);
	void Process(Chara& chara, Camera& cam, VECTOR& v, VECTOR oldv);
	void CameraProcess(Camera& cam);
	void Render(VECTOR vPos, bool viewColl);
public:
	
};
