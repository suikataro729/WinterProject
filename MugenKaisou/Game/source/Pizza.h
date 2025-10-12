#include "appframe.h"

#include <string>
#include <vector>
#include <iostream>

// �s�U
class Pizza
{
public:
	Pizza();	// �R���X�g���N�^
	~Pizza();	// �f�X�g���N�^
	void AddPizza(float x, float y, float z);
	void Process(int _handleMap, int _frameMapCollision);
	void Render();

	float gravity;
	VECTOR _vPos;	// �ʒu
	VECTOR _vDir;	// ����
	int _cntView;
	int _mapBoxType;
protected:
	int _handle;
};
