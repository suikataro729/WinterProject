#include "RoomBase.h"

class RoomSlidePuzzle : public RoomBase
{
public:
	RoomSlidePuzzle();				// インストラクタ
	virtual ~RoomSlidePuzzle();	// デストラクタ

	void Process(Chara& chara, Camera& cam, VECTOR& v, VECTOR oldv);
	void CameraProcess(Camera& cam);
	void Render(VECTOR vPos, bool viewColl);
public:
	// ずらせるブロックとオブジェクト
	ShiftBlock _shiftBlock;
	std::vector<ShiftBlock> _vShiftBlock;
};
