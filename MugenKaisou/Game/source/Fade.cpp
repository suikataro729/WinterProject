#include "AppFrame.h"
#include "Fade.h"

// フェード
// コンストラクタ
Fade::Fade() {
	// カラーマスク用
	gColorMaskR = 0;
	gColorMaskG = 0;
	gColorMaskB = 0;
	gColorMaskA = 0;
	// フェードインアウト用
	gFadeFrames = 0;
	gFadeCnt = 0;
}

// デストラクタ
Fade::~Fade() {

}

// 指定の色をカラーマスク
void Fade::ColorMask(int colorR, int colorG, int colorB, int colorA) {
	gColorMaskR = colorR;
	gColorMaskG = colorG;
	gColorMaskB = colorB;
	gColorMaskA = colorA;
}

// 指定の色にフェードアウト（カラーマスク使用, alpha=255にする）
void Fade::ColorFadeOut(int colorR, int colorG, int colorB, int frames) {
	// フェード開始値
	gColorFadeStR = gColorMaskR;
	gColorFadeStG = gColorMaskG;
	gColorFadeStB = gColorMaskB;
	gColorFadeStA = gColorMaskA;
	// フェード到達値
	gColorFadeEdR = colorR;
	gColorFadeEdG = colorG;
	gColorFadeEdB = colorB;
	gColorFadeEdA = 255;
	// フェードカウンタ
	gFadeFrames = frames;
	gFadeCnt = 0;
}

// 現在のカラーマスクからフェードイン（カラーマスク使用, alpha=0にする）
void Fade::ColorFadeIn(int frames) {
	// フェード開始値
	gColorFadeStR = gColorMaskR;
	gColorFadeStG = gColorMaskG;
	gColorFadeStB = gColorMaskB;
	gColorFadeStA = gColorMaskA;
	// フェード到達値
	gColorFadeEdR = gColorMaskR;
	gColorFadeEdG = gColorMaskG;
	gColorFadeEdB = gColorMaskB;
	gColorFadeEdA = 0;
	// フェードカウンタ
	gFadeFrames = frames;
	gFadeCnt = 0;
}

// フェードインアウトは終了したか？
// 戻り値: 1 = フェード中, 0 = フェード終了(もしくは開始前)
int Fade::IsColorFade() {
	if (gFadeCnt < gFadeFrames) {
		return 1;
	}
	return 0;
}

// フェードインアウト処理
void Fade::ProcessColorFade() {
	// カラーマスクのフェードインアウト
	if (IsColorFade() != 0) {
		gFadeCnt++;
		gColorMaskR = myMath.EasingLinear(gFadeCnt, gColorFadeStR, gColorFadeEdR, gFadeFrames);
		gColorMaskG = myMath.EasingLinear(gFadeCnt, gColorFadeStG, gColorFadeEdG, gFadeFrames);
		gColorMaskB = myMath.EasingLinear(gFadeCnt, gColorFadeStB, gColorFadeEdB, gFadeFrames);
		gColorMaskA = myMath.EasingLinear(gFadeCnt, gColorFadeStA, gColorFadeEdA, gFadeFrames);
	}
}

// フェードインアウト描画
void Fade::DrawColorFade() {
	// カラーマスク
	if (gColorMaskA > 0) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, gColorMaskA);	// 半透明モード
		DrawBox(0, 0, 1920, 1080, GetColor(gColorMaskR, gColorMaskG, gColorMaskB), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, gColorMaskA);
	}
}
