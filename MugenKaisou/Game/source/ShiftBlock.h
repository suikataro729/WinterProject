#include "appframe.h"

#include <string>
#include <vector>
#include <iostream>

// �u���b�N���炵
class ShiftBlock
{
public:
	ShiftBlock();	// �R���X�g���N�^
	~ShiftBlock();	// �f�X�g���N�^
	void SetShiftData(int dir, VECTOR& _vToPos, VECTOR& _vMove);
	void Shift(VECTOR& _vPos, VECTOR& _vToPos, VECTOR& _vMove);
protected:
	int _numShiftBlock;
	int _dirShiftBlock;
};
