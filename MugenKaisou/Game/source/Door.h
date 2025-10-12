#include "appframe.h"


// ドア
class Door
{
public:
	Door();		// コンストラクタ
	~Door();	// デストラクタ
	void SetVisible(bool flg);					// ドア表示・非表示状態の設定
	bool GetVisible() { return _flgVisible; }	// ドア表示・非表示状態の取得
	void ChangeDoor(int ChangeDoor);			// ドア切り替え
	int GetDoorType() { return _objTypeDoor; }	// 表示するドアのタイプの取得
	void Clear();

protected:
	bool _flgVisible;	// ドアの表示フラグ
	int _objTypeDoor;	// 表示するドアのオブジェクトタイプ
};
