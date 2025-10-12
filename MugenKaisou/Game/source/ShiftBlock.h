#include "appframe.h"

#include <string>
#include <vector>
#include <iostream>

// ブロックずらし
class ShiftBlock
{
public:
	ShiftBlock();	// コンストラクタ
	~ShiftBlock();	// デストラクタ
	void SetShiftData(int dir, VECTOR& _vToPos, VECTOR& _vMove);
	void Shift(VECTOR& _vPos, VECTOR& _vToPos, VECTOR& _vMove);
protected:
	int _numShiftBlock;
	int _dirShiftBlock;
};
