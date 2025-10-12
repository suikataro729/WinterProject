#include "appframe.h"

#include <string>
#include <vector>


// モード
class ModeEffekseer : public ModeBase
{
	typedef ModeBase base;
public:
	virtual bool Initialize(float x, float y, float z);
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

protected:
	VECTOR _vPos;	// 位置
	int		_effectResourceHandle;		// エフェクトファイルをロードするハンドル
	int		_playingEffectHandle;		// ロードしたエフェクトファイルから、エフェクトを生成したもの

	// エフェクト位置
	float	_position_x = 0.0f;
	float	_position_y = 0.0f;
	float	_position_z = 0.0f;
};
