#include "appframe.h"

#include <string>
#include <vector>
#include <iostream>

class BeltConveyor
{
public:
	BeltConveyor();		// �C���X�g���N�^
	~BeltConveyor();	// �f�X�g���N�^

	void Init();
	void Process();
	void MovePos(VECTOR &vCharaPos, int boxType, int MoveSpeed);
	void Render();

public:
	
};
