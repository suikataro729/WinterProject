#include "RoomBase.h"

class RoomEntrance : public RoomBase
{
public:
	RoomEntrance();				// �C���X�g���N�^
	virtual ~RoomEntrance();	// �f�X�g���N�^

	void CharaMove(Chara& chara, Camera& cam, VECTOR& v, VECTOR oldv);
	void Process(Chara& chara, Camera& cam, VECTOR& v, VECTOR oldv);
	void CameraProcess(Camera& cam);
	void Render(VECTOR vPos, bool viewColl);
public:
	MyMath mymath;
	bool flgEffect;
};
