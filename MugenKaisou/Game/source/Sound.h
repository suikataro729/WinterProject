#include "appframe.h"

// �T�E���h�iBGM�ESE�j
class Sound
{
public:
	Sound();	// �R���X�g���N�^
	~Sound();	// �f�X�g���N�^
	void Load(int num);
	void Play(int type);
	void Stop();
	void Delete();
protected:
	int _handle;	// �T�E���h�f�[�^
};
