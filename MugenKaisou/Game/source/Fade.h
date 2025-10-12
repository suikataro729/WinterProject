#pragma once

#include "appframe.h"

// フェード
class Fade
{
public:
	Fade();		// コンストラクタ
	~Fade();	// デストラクタ
	
	// カラーマスクの指定
	void ColorMask(int colorR, int colorG, int colorB, int colorA);
	// 指定の色にフェードアウト（カラーマスク使用, alpha=255にする）
	void ColorFadeOut(int colorR, int colorG, int colorB, int frames);
	// 現在のカラーマスクからフェードイン（カラーマスク使用, alpha=0にする）
	void ColorFadeIn(int frames);
	// フェードインアウトは終了したか？
	// 戻り値: 1 = フェード中, 0 = フェード終了(もしくは開始前)
	int IsColorFade();

	// フェードインアウト処理
	void ProcessColorFade();
	// フェードインアウト描画
	void DrawColorFade();
private:
	// カラーマスク用
	int gColorMaskR, gColorMaskG, gColorMaskB, gColorMaskA;
	// フェードインアウト用
	int gColorFadeStR, gColorFadeStG, gColorFadeStB, gColorFadeStA;
	int gColorFadeEdR, gColorFadeEdG, gColorFadeEdB, gColorFadeEdA;
	int gFadeFrames, gFadeCnt;

	MyMath myMath;
};
