#include "RoomBase.h"

class RoomCalcLabyrinth : public RoomBase
{
public:
	RoomCalcLabyrinth();			// コンストラクタ
	virtual ~RoomCalcLabyrinth();	// デストラクタ

	void CharaMove(Chara& chara, Camera& cam, VECTOR& v, VECTOR oldv);
	void Process(Chara& chara, Camera& cam, VECTOR& v, VECTOR oldv);
	void CameraProcess(Camera& cam);
	void Render(VECTOR vPos, bool viewColl);
public:
	
};
