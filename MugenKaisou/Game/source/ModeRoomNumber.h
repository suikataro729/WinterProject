
#include "appframe.h"

#include <string>
#include <vector>


// モード
class ModeRoomNumber : public ModeBase
{
	typedef ModeBase base;

public:
	ModeRoomNumber(int _keyRoom, int _next_keyRoom, bool clear);
	~ModeRoomNumber();
	virtual bool Initialize();
	virtual bool Process();
	virtual bool Render();

	int save_keyRoom;
	int save_next_keyRoom;
	bool save_clear;
	int alpha_cnt;
	int gamecnt;
	int cgbg;
	int cgCover[2];
	int _cgDialy;
	int cgDialyParts[2];
	int _cgNum;
	int cgDialy[11];
	int cgNumber[11];

	int cgAreaMapUI;
	int cgAreaMapEmpty[4];
	int cgAreaMapNum[2][11];		//0:白、1:黄色
	Useful USEFUL;
};
