#include "RoomBase.h"

#define MAPSIZE 5 * 18
#define MAP_W	(5)
#define MAP_H	(18)
#define BOX_W	(400)

class RoomFan : public RoomBase
{
public:
	RoomFan();			// インストラクタ
	virtual ~RoomFan();	// デストラクタ

	void CharaMove(Chara& chara, Camera& cam, VECTOR& v, VECTOR oldv);
	void Process(Chara& chara, Camera& cam, VECTOR& v, VECTOR oldv);
	void CameraProcess(Camera& cam);
	void Render(VECTOR vPos, bool viewColl);
public:
	int _handleFan;
	int _FanframeMapCollision;
	float FanCnt;

	// ベルトコンベア
	BeltConveyor beltConv;
	VECTOR respownSave;
};

