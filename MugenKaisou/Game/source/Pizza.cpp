#include "AppFrame.h"
#include "Pizza.h"

// �s�U
Pizza::Pizza() {
	_handle = MV1LoadModel("res/3Dart/pizza/piza_wani_syusei.mv1");
	// �ʒu,�����̏�����
	_vPos = VGet(0, 500, 0);
	_vDir = VGet(0, 0, -1);		// �L�������f���̓f�t�H���g��-Z�����������Ă���
	gravity = 0.0f;
	_cntView = 0;
}
Pizza::~Pizza() {
}

void Pizza::AddPizza(float x, float y, float z) {
	_vPos = VGet(x, y + 200, z);
}

void Pizza::Process(int _handleMap, int _frameMapCollision) {

	gravity += 0.6f;

	// �ړ�������ŃR���W��������
	MV1_COLL_RESULT_POLY hitPoly;
	hitPoly = MV1CollCheck_Line(_handleMap, _frameMapCollision,
		VGet(0, 10, 0), VAdd(_vPos, VGet(0, -99999.f, 0)));
	if (hitPoly.HitFlag) {
		// ��������
		if (_vPos.y <= hitPoly.HitPosition.y) {
			gravity = 0;
			// ��������Y�ʒu���L�������W�ɂ���
			_vPos.y = hitPoly.HitPosition.y;
		}
	}
	//�d�͂̔��f
	_vPos.y -= gravity;
}

void Pizza::Render() {
	// �ʒu
	MV1SetPosition(_handle, _vPos);
	// �`��
	MV1DrawModel(_handle);
}
