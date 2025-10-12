
#include "appframe.h"

#include <string>
#include <vector>

// ���j���[���ڗp�x�[�X�N���X
class MenuItemBase
{
public:
	MenuItemBase(void* param, std::string text) {
		_param = param;
		_text = text;
	}
	virtual ~MenuItemBase() {
	}

	// ���ڂ����肵���炱�̊֐����Ă΂��
	// return int : 0 = ���j���[�p��, 1 = ���j���[�I��
	virtual int Selected() {
		return 0;
	}

public:
	void* _param;
	std::string		_text;
};

// ���[�h
class ModeMenu : public ModeBase
{
	typedef ModeBase base;
public:
	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

	void	Add(MenuItemBase* itemBase);
	void	Clear();

protected:
	std::vector<MenuItemBase*>	_vItems;

	int		_curPos;
	int		_curAnimCnt;

}; 
