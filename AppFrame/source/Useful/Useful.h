#pragma once

#include	<string>

class		Useful
{
public:
	void DrawRoundShadow(int _handleMap, int _frameMapCollision, VECTOR _vPos, float _colSubY, float radMax, int radMag);
	void DrawPosString(int x, int y, int posBaseX, unsigned int color, const char* str);
};


