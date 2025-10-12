#include "RoomBase.h"

class RoomCalcLabyrinth : public RoomBase
{
public:
	RoomCalcLabyrinth();			// �R���X�g���N�^
	virtual ~RoomCalcLabyrinth();	// �f�X�g���N�^

	void CharaMove(Chara& chara, Camera& cam, VECTOR& v, VECTOR oldv);
	void Process(Chara& chara, Camera& cam, VECTOR& v, VECTOR oldv);
	void CameraProcess(Camera& cam);
	void Render(VECTOR vPos, bool viewColl);
public:
	
};
