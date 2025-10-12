#include "appframe.h"

// サウンド（BGM・SE）
class Sound
{
public:
	Sound();	// コンストラクタ
	~Sound();	// デストラクタ
	void Load(int num);
	void Play(int type);
	void Stop();
	void Delete();
protected:
	int _handle;	// サウンドデータ
};
