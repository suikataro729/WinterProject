#include "appframe.h"

#include <string>
#include <vector>


// モード
class ClassEffekseer
{
public:
	ClassEffekseer();
	~ClassEffekseer();
	void AddEffect(const TCHAR* EffectHandle,float x, float y, float z,int EffectCntMax, float Rotate = 0.0f);
	void Process();
	void Render();


	int EffectCnt;
	int EffectCntMax;
	int		breakFlag = 0;

	// エフェクト位置
	float	_position_x = 0.0f;
	float	_position_y = 0.0f;
	float	_position_z = 0.0f;
protected:
	VECTOR _vPos;	// 位置
	int		_effectResourceHandle;		// エフェクトファイルをロードするハンドル
	int		_playingEffectHandle;		// ロードしたエフェクトファイルから、エフェクトを生成したもの
	
	float _Rotate;

};
