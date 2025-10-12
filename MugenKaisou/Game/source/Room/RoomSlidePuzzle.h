#include "RoomBase.h"

class RoomSlidePuzzle : public RoomBase
{
public:
	RoomSlidePuzzle();				// �C���X�g���N�^
	virtual ~RoomSlidePuzzle();	// �f�X�g���N�^

	void Process(Chara& chara, Camera& cam, VECTOR& v, VECTOR oldv);
	void CameraProcess(Camera& cam);
	void Render(VECTOR vPos, bool viewColl);
public:
	// ���点��u���b�N�ƃI�u�W�F�N�g
	ShiftBlock _shiftBlock;
	std::vector<ShiftBlock> _vShiftBlock;
};
