#include "appframe.h"


// �h�A
class Door
{
public:
	Door();		// �R���X�g���N�^
	~Door();	// �f�X�g���N�^
	void SetVisible(bool flg);					// �h�A�\���E��\����Ԃ̐ݒ�
	bool GetVisible() { return _flgVisible; }	// �h�A�\���E��\����Ԃ̎擾
	void ChangeDoor(int ChangeDoor);			// �h�A�؂�ւ�
	int GetDoorType() { return _objTypeDoor; }	// �\������h�A�̃^�C�v�̎擾
	void Clear();

protected:
	bool _flgVisible;	// �h�A�̕\���t���O
	int _objTypeDoor;	// �\������h�A�̃I�u�W�F�N�g�^�C�v
};
