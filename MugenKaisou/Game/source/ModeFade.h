#include "appframe.h"

#include "Fade.h"
#include <string>
#include <vector>

// �t�F�[�h���ʗp���[�h
class ModeFade : public ModeBase
{
	typedef ModeBase base;
public:
	ModeFade(std::string type);
	~ModeFade();

	virtual bool Initialize();
	virtual bool Process();
	virtual bool Render();
protected:
	int _step;
	std::string _fadeType;

	Fade gFade;
};
