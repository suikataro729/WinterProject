
#include "appframe.h"

#include <string>
#include <vector>

// ���[�h
class ModeTitle : public ModeBase
{
	typedef ModeBase base;
public:
	virtual bool Initialize();
	virtual bool Process();
	virtual bool Render();

	Useful USEFUL;
protected:
	int cg_bg[10];
	float bookY;
	float bookSaveY;

	int buttonY;
	int buttonSaveY;
	bool flgGameStart;	// �Q�[���N�����t���O
}; 
