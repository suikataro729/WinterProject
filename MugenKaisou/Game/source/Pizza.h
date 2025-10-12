#include "appframe.h"

#include <string>
#include <vector>
#include <iostream>

// ピザ
class Pizza
{
public:
	Pizza();	// コンストラクタ
	~Pizza();	// デストラクタ
	void AddPizza(float x, float y, float z);
	void Process(int _handleMap, int _frameMapCollision);
	void Render();

	float gravity;
	VECTOR _vPos;	// 位置
	VECTOR _vDir;	// 向き
	int _cntView;
	int _mapBoxType;
protected:
	int _handle;
};
