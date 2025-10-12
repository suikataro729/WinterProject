#include "AppFrame.h"
#include "ShiftBlock.h"

ShiftBlock::ShiftBlock() {
	_numShiftBlock = 0;
	_dirShiftBlock = 0;
}

ShiftBlock::~ShiftBlock() {

}

void ShiftBlock::SetShiftData(int dir, VECTOR& _vToPos, VECTOR& _vMove) {
	// �ړ���
	_dirShiftBlock = dir;
	switch (_dirShiftBlock) {
	case 1:
		_vMove.x = 20.f;
		_vToPos.x += 500.f;
		break;
	case 2:
		_vMove.x = -20.f;
		_vToPos.x -= 500.f;
		break;
	case 3:
		_vMove.z = +20.f;
		_vToPos.z += 500.f;
		break;
	case 4:
		_vMove.z = -20.f;
		_vToPos.z -= 500.f;
		break;
	}
}

void ShiftBlock::Shift(VECTOR& _vPos, VECTOR& _vToPos, VECTOR& _vMove) {
	// x���ړ�
	if (_vMove.x > 0.f) {
		if (_vPos.x < _vToPos.x) {
			_vPos = VAdd(_vPos, _vMove);
			if (_vPos.x >= _vToPos.x) {
				_vPos.x = _vToPos.x;
				_vMove.x = 0.f;
			}
		}
	}
	else if (_vMove.x < 0.f) {
		if (_vPos.x > _vToPos.x) {
			_vPos = VAdd(_vPos, _vMove);
			if (_vPos.x <= _vToPos.x) {
				_vPos.x = _vToPos.x;
				_vMove.x = 0.f;
			}
		}
	}

	// z���ړ�
	if (_vMove.z > 0.f) {
		if (_vPos.z < _vToPos.z) {
			_vPos = VAdd(_vPos, _vMove);
			if (_vPos.z >= _vToPos.z) {
				_vPos.z = _vToPos.z;
				_vMove.z = 0.f;
			}
		}
	}
	else if (_vMove.z < 0.f) {
		if (_vPos.z > _vToPos.z) {
			_vPos = VAdd(_vPos, _vMove);
			if (_vPos.z <= _vToPos.z) {
				_vPos.z = _vToPos.z;
				_vMove.z = 0.f;
			}
		}
	}
}
