
#include "appframe.h"

#include <string>
#include <vector>


// ÉÇÅ[Éh
class ModeGameOver : public ModeBase
{
	typedef ModeBase base;
public:
	virtual bool Initialize();
	virtual bool Process();
	virtual bool Render();

	int alpha_cnt;
	Useful USEFUL;
};
