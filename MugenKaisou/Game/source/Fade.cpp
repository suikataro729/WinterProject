#include "AppFrame.h"
#include "Fade.h"

// �t�F�[�h
// �R���X�g���N�^
Fade::Fade() {
	// �J���[�}�X�N�p
	gColorMaskR = 0;
	gColorMaskG = 0;
	gColorMaskB = 0;
	gColorMaskA = 0;
	// �t�F�[�h�C���A�E�g�p
	gFadeFrames = 0;
	gFadeCnt = 0;
}

// �f�X�g���N�^
Fade::~Fade() {

}

// �w��̐F���J���[�}�X�N
void Fade::ColorMask(int colorR, int colorG, int colorB, int colorA) {
	gColorMaskR = colorR;
	gColorMaskG = colorG;
	gColorMaskB = colorB;
	gColorMaskA = colorA;
}

// �w��̐F�Ƀt�F�[�h�A�E�g�i�J���[�}�X�N�g�p, alpha=255�ɂ���j
void Fade::ColorFadeOut(int colorR, int colorG, int colorB, int frames) {
	// �t�F�[�h�J�n�l
	gColorFadeStR = gColorMaskR;
	gColorFadeStG = gColorMaskG;
	gColorFadeStB = gColorMaskB;
	gColorFadeStA = gColorMaskA;
	// �t�F�[�h���B�l
	gColorFadeEdR = colorR;
	gColorFadeEdG = colorG;
	gColorFadeEdB = colorB;
	gColorFadeEdA = 255;
	// �t�F�[�h�J�E���^
	gFadeFrames = frames;
	gFadeCnt = 0;
}

// ���݂̃J���[�}�X�N����t�F�[�h�C���i�J���[�}�X�N�g�p, alpha=0�ɂ���j
void Fade::ColorFadeIn(int frames) {
	// �t�F�[�h�J�n�l
	gColorFadeStR = gColorMaskR;
	gColorFadeStG = gColorMaskG;
	gColorFadeStB = gColorMaskB;
	gColorFadeStA = gColorMaskA;
	// �t�F�[�h���B�l
	gColorFadeEdR = gColorMaskR;
	gColorFadeEdG = gColorMaskG;
	gColorFadeEdB = gColorMaskB;
	gColorFadeEdA = 0;
	// �t�F�[�h�J�E���^
	gFadeFrames = frames;
	gFadeCnt = 0;
}

// �t�F�[�h�C���A�E�g�͏I���������H
// �߂�l: 1 = �t�F�[�h��, 0 = �t�F�[�h�I��(�������͊J�n�O)
int Fade::IsColorFade() {
	if (gFadeCnt < gFadeFrames) {
		return 1;
	}
	return 0;
}

// �t�F�[�h�C���A�E�g����
void Fade::ProcessColorFade() {
	// �J���[�}�X�N�̃t�F�[�h�C���A�E�g
	if (IsColorFade() != 0) {
		gFadeCnt++;
		gColorMaskR = myMath.EasingLinear(gFadeCnt, gColorFadeStR, gColorFadeEdR, gFadeFrames);
		gColorMaskG = myMath.EasingLinear(gFadeCnt, gColorFadeStG, gColorFadeEdG, gFadeFrames);
		gColorMaskB = myMath.EasingLinear(gFadeCnt, gColorFadeStB, gColorFadeEdB, gFadeFrames);
		gColorMaskA = myMath.EasingLinear(gFadeCnt, gColorFadeStA, gColorFadeEdA, gFadeFrames);
	}
}

// �t�F�[�h�C���A�E�g�`��
void Fade::DrawColorFade() {
	// �J���[�}�X�N
	if (gColorMaskA > 0) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, gColorMaskA);	// ���������[�h
		DrawBox(0, 0, 1920, 1080, GetColor(gColorMaskR, gColorMaskG, gColorMaskB), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, gColorMaskA);
	}
}
