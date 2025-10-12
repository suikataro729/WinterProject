#include "appframe.h"

#include <string>
#include <vector>
#include <iostream>

class BeltConveyor
{
public:
	BeltConveyor();		// インストラクタ
	~BeltConveyor();	// デストラクタ

	void Init();
	void Process();
	void MovePos(VECTOR &vCharaPos, int boxType, int MoveSpeed);
	void Render();

public:
	
};
