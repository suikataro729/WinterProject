#pragma once

#include "appframe.h"

// �t�F�[�h
class Fade
{
public:
	Fade();		// �R���X�g���N�^
	~Fade();	// �f�X�g���N�^
	
	// �J���[�}�X�N�̎w��
	void ColorMask(int colorR, int colorG, int colorB, int colorA);
	// �w��̐F�Ƀt�F�[�h�A�E�g�i�J���[�}�X�N�g�p, alpha=255�ɂ���j
	void ColorFadeOut(int colorR, int colorG, int colorB, int frames);
	// ���݂̃J���[�}�X�N����t�F�[�h�C���i�J���[�}�X�N�g�p, alpha=0�ɂ���j
	void ColorFadeIn(int frames);
	// �t�F�[�h�C���A�E�g�͏I���������H
	// �߂�l: 1 = �t�F�[�h��, 0 = �t�F�[�h�I��(�������͊J�n�O)
	int IsColorFade();

	// �t�F�[�h�C���A�E�g����
	void ProcessColorFade();
	// �t�F�[�h�C���A�E�g�`��
	void DrawColorFade();
private:
	// �J���[�}�X�N�p
	int gColorMaskR, gColorMaskG, gColorMaskB, gColorMaskA;
	// �t�F�[�h�C���A�E�g�p
	int gColorFadeStR, gColorFadeStG, gColorFadeStB, gColorFadeStA;
	int gColorFadeEdR, gColorFadeEdG, gColorFadeEdB, gColorFadeEdA;
	int gFadeFrames, gFadeCnt;

	MyMath myMath;
};
