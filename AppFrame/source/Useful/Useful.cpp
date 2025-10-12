#include "dxlib.h"
#include "Useful.h"

//�ۉe�̕\��
void Useful::DrawRoundShadow(int _handleMap,int _frameMapCollision,VECTOR _vPos, float _colSubY,float radMax,int radMag) {
	MV1_COLL_RESULT_POLY hitPoly;
	// ��l���̍��ʒu���牺�����ւ̒���
	hitPoly = MV1CollCheck_Line(_handleMap, _frameMapCollision,
		VAdd(_vPos, VGet(0, _colSubY, 0)), VAdd(_vPos, VGet(0, -99999.f, 0)));
	if (hitPoly.HitFlag) {
		float rad = radMax - (_vPos.y - hitPoly.HitPosition.y) / radMag;		//�e�̔��a
		if (rad < 1.0f) { rad = 1.0; }		//�e�̍ŏ����a
		DrawCone3D(VGet(_vPos.x, hitPoly.HitPosition.y, _vPos.z), VGet(_vPos.x, hitPoly.HitPosition.y + 3, _vPos.z), rad, 16, GetColor(0, 0, 0), GetColor(0, 0, 0), TRUE);
	}
}

// posBaseX = -1:������, 0:����, 1:�E����
void Useful::DrawPosString(int x, int y, int posBaseX, unsigned int color, const char* str) {
    int w = GetDrawStringWidth(str, strlen(str));	// �`�悷�镶���̉��T�C�Y�𓾂�
    if (posBaseX == 0) {
        // ���������Ȃ̂�x�ʒu�����ɔ������炷
        x -= w / 2;
    }
    else if (posBaseX > 0) {
        // �E�����Ȃ̂�x�ʒu�����ɂ��炷
        x -= w;
    }
    DrawString(x, y, str, color);
}