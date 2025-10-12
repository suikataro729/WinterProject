#pragma once

#include "DxLib.h"
#include <math.h>

// 円周率
#define	PI		(3.141592653589793)
#define TwoPI   (PI * 2.0f)
#define PIOver2 (PI / 2.0f)

class MyMath
{
public:
	MyMath();
	~MyMath();

	bool IsHitCircle(VECTOR c1, float cr1, VECTOR c2, float cr2);
	bool IsHitSphere(VECTOR s1, float sr1, VECTOR s2, float sr2);

	bool IsHitPointBox(VECTOR c1, float b1x, float b1z, float bw1, float bh1);

	// 様々なイージング
	// https://game-ui.net/?p=835 を参考に
	float EasingLinear(float cnt, float start, float end, float frames);
	float EasingInQuad(float cnt, float start, float end, float frames);
	float EasingOutQuad(float cnt, float start, float end, float frames);
	float EasingInOutQuad(float cnt, float start, float end, float frames);
	float EasingInCubic(float cnt, float start, float end, float frames);
	float EasingOutCubic(float cnt, float start, float end, float frames);
	float EasingInOutCubic(float cnt, float start, float end, float frames);
	float EasingInQuart(float cnt, float start, float end, float frames);
	float EasingOutQuart(float cnt, float start, float end, float frames);
	float EasingInOutQuart(float cnt, float start, float end, float frames);
	float EasingInQuint(float cnt, float start, float end, float frames);
	float EasingOutQuint(float cnt, float start, float end, float frames);
	float EasingInOutQuint(float cnt, float start, float end, float frames);
	float EasingInSine(float cnt, float start, float end, float frames);
	float EasingOutSine(float cnt, float start, float end, float frames);
	float EasingInOutSine(float cnt, float start, float end, float frames);
	float EasingInExpo(float cnt, float start, float end, float frames);
	float EasingOutExpo(float cnt, float start, float end, float frames);
	float EasingInOutExpo(float cnt, float start, float end, float frames);
	float EasingInCirc(float cnt, float start, float end, float frames);
	float EasingOutCirc(float cnt, float start, float end, float frames);
	float EasingInOutCirc(float cnt, float start, float end, float frames);
};
