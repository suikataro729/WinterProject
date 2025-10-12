#include "MyMath.h"

MyMath::MyMath()
{

}

MyMath::~MyMath()
{

}

bool MyMath::IsHitCircle(VECTOR c1, float cr1, VECTOR c2, float cr2)
{
	return true;
}

bool MyMath::IsHitSphere(VECTOR s1, float sr1, VECTOR s2, float sr2)
{
	return true;
}

bool MyMath::IsHitPointBox(VECTOR c1, float b1x, float b1z, float bw1, float bh1)
{
	if (b1x < c1.x && c1.x < b1x + bw1
		&& b1z < c1.z && c1.z < b1z + bh1)
	{
		return true;
	}
	else { return false; }
}

// イージング
float MyMath::EasingLinear(float cnt, float start, float end, float frames) {
    return (end - start) * cnt / frames + start;
}
float MyMath::EasingInQuad(float cnt, float start, float end, float frames) {
    cnt /= frames;
    return (end - start) * cnt * cnt + start;
}
float MyMath::EasingOutQuad(float cnt, float start, float end, float frames) {
    cnt /= frames;
    return -(end - start) * cnt * (cnt - 2) + start;
}
float MyMath::EasingInOutQuad(float cnt, float start, float end, float frames) {
    cnt /= frames / 2.0;
    if (cnt < 1) {
        return (end - start) / 2.0 * cnt * cnt + start;
    }
    cnt--;
    return -(end - start) / 2.0 * (cnt * (cnt - 2) - 1) + start;
}
float MyMath::EasingInCubic(float cnt, float start, float end, float frames) {
    cnt /= frames;
    return (end - start) * cnt * cnt * cnt + start;
}
float MyMath::EasingOutCubic(float cnt, float start, float end, float frames) {
    cnt /= frames;
    cnt--;
    return (end - start) * (cnt * cnt * cnt + 1) + start;
}
float MyMath::EasingInOutCubic(float cnt, float start, float end, float frames) {
    cnt /= frames / 2.0;
    if (cnt < 1) {
        return (end - start) / 2.0 * cnt * cnt * cnt + start;
    }
    cnt -= 2;
    return (end - start) / 2.0 * (cnt * cnt * cnt + 2) + start;
}
float MyMath::EasingInQuart(float cnt, float start, float end, float frames) {
    cnt /= frames;
    return (end - start) * cnt * cnt * cnt * cnt + start;
}
float MyMath::EasingOutQuart(float cnt, float start, float end, float frames) {
    cnt /= frames;
    cnt--;
    return -(end - start) * (cnt * cnt * cnt * cnt - 1) + start;
}
float MyMath::EasingInOutQuart(float cnt, float start, float end, float frames) {
    cnt /= frames / 2.0;
    if (cnt < 1) {
        return (end - start) / 2.0 * cnt * cnt * cnt * cnt + start;
    }
    cnt -= 2;
    return -(end - start) / 2.0 * (cnt * cnt * cnt * cnt - 2) + start;
}
float MyMath::EasingInQuint(float cnt, float start, float end, float frames) {
    cnt /= frames;
    return (end - start) * cnt * cnt * cnt * cnt * cnt + start;
}
float MyMath::EasingOutQuint(float cnt, float start, float end, float frames) {
    cnt /= frames;
    cnt--;
    return (end - start) * (cnt * cnt * cnt * cnt * cnt + 1) + start;
}
float MyMath::EasingInOutQuint(float cnt, float start, float end, float frames) {
    cnt /= frames / 2.0;
    if (cnt < 1) {
        return (end - start) / 2.0 * cnt * cnt * cnt * cnt * cnt + start;
    }
    cnt -= 2;
    return (end - start) / 2.0 * (cnt * cnt * cnt * cnt * cnt + 2) + start;
}
float MyMath::EasingInSine(float cnt, float start, float end, float frames) {
    return -(end - start) * cos(cnt / frames * (PIOver2)) + end + start;
}
float MyMath::EasingOutSine(float cnt, float start, float end, float frames) {
    return (end - start) * sin(cnt / frames * PIOver2) + start;
}
float MyMath::EasingInOutSine(float cnt, float start, float end, float frames) {
    return -(end - start) / 2.0 * (cos(PI * cnt / frames) - 1) + start;
}
float MyMath::EasingInExpo(float cnt, float start, float end, float frames) {
    return (end - start) * pow(2.0, 10 * (cnt / frames - 1)) + start;
}
float MyMath::EasingOutExpo(float cnt, float start, float end, float frames) {
    return (end - start) * (-pow(2.0, -10 * cnt / frames) + 1) + start;
}
float MyMath::EasingInOutExpo(float cnt, float start, float end, float frames) {
    cnt /= frames / 2.0;
    if (cnt < 1) {
        return (end - start) / 2.0 * pow(2.0, 10 * (cnt - 1)) + start;
    }
    cnt--;
    return (end - start) / 2.0 * (-pow(2.0, -10 * cnt) + 2) + start;
}
float MyMath::EasingInCirc(float cnt, float start, float end, float frames) {
    cnt /= frames;
    return -(end - start) * (sqrt(1 - cnt * cnt) - 1) + start;
}
float MyMath::EasingOutCirc(float cnt, float start, float end, float frames) {
    cnt /= frames;
    cnt--;
    return (end - start) * sqrt(1 - cnt * cnt) + start;
}
float MyMath::EasingInOutCirc(float cnt, float start, float end, float frames) {
    cnt /= frames / 2.0;
    if (cnt < 1) {
        return -(end - start) / 2.0 * (sqrt(1 - cnt * cnt) - 1) + start;
    }
    cnt -= 2;
    return (end - start) / 2.0 * (sqrt(1 - cnt * cnt) + 1) + start;
}
