
#include "dxlib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../Mode//ModeServer.h"
#include "gamepad.h"

// EffekseerForDXLib.h���C���N���[�h���܂��B
#include "EffekseerForDXLib.h"

class ApplicationBase
{
public:
	ApplicationBase();
	virtual ~ApplicationBase();

	virtual bool Initialize(HINSTANCE hInstance);
	virtual bool Terminate();
	virtual bool Input();
	virtual bool Process();
	virtual bool Render();

	virtual bool AppWindowed() { return true; }
	virtual int DispSizeW() { return 640; }
	virtual int DispSizeH() { return 480; }

	static	ApplicationBase	*GetInstance() { return _lpInstance; }
	virtual int GetKey() { return _gKey; }
	virtual int GetTrg() { return _gTrg; }
	virtual int GetRel() { return _gRel; }

protected:
	static	ApplicationBase	*_lpInstance;

	int		_gKey, _gTrg, _gRel;

	ModeServer* _serverMode;

};
