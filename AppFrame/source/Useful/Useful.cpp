#include "dxlib.h"
#include "Useful.h"

//丸影の表示
void Useful::DrawRoundShadow(int _handleMap,int _frameMapCollision,VECTOR _vPos, float _colSubY,float radMax,int radMag) {
	MV1_COLL_RESULT_POLY hitPoly;
	// 主人公の腰位置から下方向への直線
	hitPoly = MV1CollCheck_Line(_handleMap, _frameMapCollision,
		VAdd(_vPos, VGet(0, _colSubY, 0)), VAdd(_vPos, VGet(0, -99999.f, 0)));
	if (hitPoly.HitFlag) {
		float rad = radMax - (_vPos.y - hitPoly.HitPosition.y) / radMag;		//影の半径
		if (rad < 1.0f) { rad = 1.0; }		//影の最小半径
		DrawCone3D(VGet(_vPos.x, hitPoly.HitPosition.y, _vPos.z), VGet(_vPos.x, hitPoly.HitPosition.y + 3, _vPos.z), rad, 16, GetColor(0, 0, 0), GetColor(0, 0, 0), TRUE);
	}
}

// posBaseX = -1:左揃え, 0:中央, 1:右揃え
void Useful::DrawPosString(int x, int y, int posBaseX, unsigned int color, const char* str) {
    int w = GetDrawStringWidth(str, strlen(str));	// 描画する文字の横サイズを得る
    if (posBaseX == 0) {
        // 中央揃えなのでx位置を左に半分ずらす
        x -= w / 2;
    }
    else if (posBaseX > 0) {
        // 右揃えなのでx位置を左にずらす
        x -= w;
    }
    DrawString(x, y, str, color);
}