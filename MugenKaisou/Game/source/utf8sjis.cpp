#include "utf8sjis.h"

bool SJIS_IsKanji(unsigned char cData) {
	if (cData<0x81) { return false; }
	if (cData<0xa0) { return true; }
	if (cData<0xe0) { return false; }
	if (cData<0xff) { return true; }
	return false;
}


// UTF8�̐擪���������āA���o�C�g�������Ԃ�
int UTF8_OctBytes(unsigned char c) {
	/*
	�ꎟ���Ƃ��Ă�Unicode�t�H�[�����̎d�l�����ARFC3629���Q��
	0*******: 1�I�N�e�b�g����
	10******: �����I�N�e�b�g�����̌㑱����
	110*****: 2�I�N�e�b�g�����̐擪
	1110****: 3�I�N�e�b�g�����̐擪
	11110***: 4�I�N�e�b�g�����̐擪
	111110**: 5�I�N�e�b�g�����̐擪
	1111110*: 6�I�N�e�b�g�����̐擪
	*/
	if ((c & 0x80) == 0x00) { return 1; }	// 0*** ****
	if ((c & 0xe0) == 0xc0) { return 2; }	// 110* ****
	if ((c & 0xf0) == 0xe0) { return 3; }	// 1110 ****
	if ((c & 0xf8) == 0xf0) { return 4; }	// 1111 0***
	if ((c & 0xfc) == 0xf8) { return 5; }	// 1111 10**
	if ((c & 0xfe) == 0xfc) { return 6; }	// 1111 110*

											// 1�����ڂ���Ȃ�
	return 0;
}


static unsigned long ConvSJIStoUTF8Single(unsigned long lSjis) {
	size_t in_size = 1;
	unsigned long x = lSjis;
	unsigned char szSjis[8] = { 0 };
	if (x < 0x100) {
		// 1byte
		szSjis[0] = (unsigned char)(x & 0xff);
		in_size = 2;
	}
	else if (x < 0x10000) {
		// 2byte
		szSjis[0] = (unsigned char)((x >> 8) & 0xff);
		szSjis[1] = (unsigned char)((x) & 0xff);
		in_size = 3;
	}
	else if (x < 0x1000000) {
		// 3byte
		szSjis[0] = (unsigned char)((x >> 16) & 0xff);
		szSjis[1] = (unsigned char)((x >> 8) & 0xff);
		szSjis[2] = (unsigned char)((x) & 0xff);
		in_size = 4;
	}
	else {
		// 4byte
		szSjis[0] = (unsigned char)((x >> 24) & 0xff);
		szSjis[1] = (unsigned char)((x >> 16) & 0xff);
		szSjis[2] = (unsigned char)((x >> 8) & 0xff);
		szSjis[3] = (unsigned char)((x) & 0xff);
		in_size = 5;
	}

	// Shift-JIS����UTF-8�֕ϊ�
	unsigned char buffUtf8[16] = "";
	if (in_size == 2) { buffUtf8[0] = szSjis[0]; buffUtf8[1] = '\0'; }

	// ShiftJIS����UTF-16�֕ϊ�
	BYTE buffUtf16[16];
	MultiByteToWideChar(932 /*SJIS,  CP_ACP*/, 0, (LPCSTR)szSjis, -1, (LPWSTR)buffUtf16, 16);
	// UTF-16����UTF-8�֕ϊ�
	WideCharToMultiByte(CP_UTF8, 0, (LPCWSTR)buffUtf16, -1, (LPSTR)buffUtf8, 16, NULL, NULL);

	x = 0;
	int c = 0;
	while (buffUtf8[c] != '\0') {
		x = (x << 8) | ((unsigned long)buffUtf8[c++]);
	}

	return x;
}

int ConvSJIStoUTF8(const unsigned char *pszSjis, unsigned char *pszOutUtf8) {
	int n = 0, c = 0;
	unsigned long l, x;

	while (pszSjis[n] != '\0') {

		if (SJIS_IsKanji(pszSjis[n])) {
			// 2byte
			l = (((unsigned long)pszSjis[n]) << 8) | (unsigned long)pszSjis[n + 1];
			n += 2;
		}
		else {
			// 1byte
			l = (unsigned long)pszSjis[n];
			n++;
		}
		x = ConvSJIStoUTF8Single(l);	// SJIS to UTF8

										// �f�[�^��������
		if (pszOutUtf8) {
			if (x < 0x100) {
				// 1byte
				pszOutUtf8[c++] = (unsigned char)(x & 0xff);
			}
			else if (x < 0x10000) {
				// 2byte
				pszOutUtf8[c++] = (unsigned char)((x >> 8) & 0xff);
				pszOutUtf8[c++] = (unsigned char)((x) & 0xff);
			}
			else if (x < 0x1000000) {
				// 3byte
				pszOutUtf8[c++] = (unsigned char)((x >> 16) & 0xff);
				pszOutUtf8[c++] = (unsigned char)((x >> 8) & 0xff);
				pszOutUtf8[c++] = (unsigned char)((x) & 0xff);
			}
			else {
				// 4byte
				pszOutUtf8[c++] = (unsigned char)((x >> 24) & 0xff);
				pszOutUtf8[c++] = (unsigned char)((x >> 16) & 0xff);
				pszOutUtf8[c++] = (unsigned char)((x >> 8) & 0xff);
				pszOutUtf8[c++] = (unsigned char)((x) & 0xff);
			}
		}
		else {
			if (x < 0x100) { c++; }
			else if (x < 0x10000) { c += 2; }
			else if (x < 0x1000000) { c += 3; }
			else { c += 4; }
		}
	}
	if (pszOutUtf8) { pszOutUtf8[c] = '\0'; }
	c++;	// asciiz�p

	return c;	// �K�vbyte��
}

static unsigned long ConvUTF8toSJISSingle(unsigned long lUtf8) {
	size_t in_size = 1;
	unsigned long x = lUtf8;
	unsigned char szUtf8[8] = { 0 };
	if (x < 0x100) {
		// 1byte
		szUtf8[0] = (unsigned char)(x & 0xff);
		in_size = 2;
	}
	else if (x < 0x10000) {
		// 2byte
		szUtf8[0] = (unsigned char)((x >> 8) & 0xff);
		szUtf8[1] = (unsigned char)((x) & 0xff);
		in_size = 3;
	}
	else if (x < 0x1000000) {
		// 3byte
		szUtf8[0] = (unsigned char)((x >> 16) & 0xff);
		szUtf8[1] = (unsigned char)((x >> 8) & 0xff);
		szUtf8[2] = (unsigned char)((x) & 0xff);
		in_size = 4;
	}
	else {
		// 4byte
		szUtf8[0] = (unsigned char)((x >> 24) & 0xff);
		szUtf8[1] = (unsigned char)((x >> 16) & 0xff);
		szUtf8[2] = (unsigned char)((x >> 8) & 0xff);
		szUtf8[3] = (unsigned char)((x) & 0xff);
		in_size = 5;
	}

	// UTF-8����Shift-JIS�֕ϊ�
	unsigned char buffSjis[16] = "";
	if (in_size == 2) { buffSjis[0] = szUtf8[0]; buffSjis[1] = '\0'; }
	// UTF-8����UTF-16�֕ϊ�
	BYTE buffUtf16[16];
	MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)szUtf8, -1, (LPWSTR)buffUtf16, 16);
	// UTF-16����Shift-JIS�֕ϊ�
	WideCharToMultiByte(932 /*SJIS,  CP_ACP*/, 0, (LPCWSTR)buffUtf16, -1, (LPSTR)buffSjis, 16, NULL, NULL);

	x = 0;
	int c = 0;
	while (buffSjis[c] != '\0') {
		x = (x << 8) | ((unsigned long)buffSjis[c++]);
	}

	return x;
}

int ConvUTF8toSJIS(const unsigned char *pszUtf8, unsigned char *pszOutSjis) {
	int n = 0, c = 0, len, i;
	unsigned long l, x;

	while (pszUtf8[n] != '\0') {
		len = UTF8_OctBytes(pszUtf8[n]);
		l = 0;
		for (i = 0; i < len; i++) {
			l = (l << 8) | pszUtf8[n++];
		}
		x = ConvUTF8toSJISSingle(l);	// UTF8 to SJIS

										// �f�[�^��������
		if (pszOutSjis) {
			if (x < 0x100) {
				// 1byte
				pszOutSjis[c++] = (unsigned char)(x & 0xff);
			}
			else {
				// 2byte
				pszOutSjis[c++] = (unsigned char)((x >> 8) & 0xff);
				pszOutSjis[c++] = (unsigned char)((x) & 0xff);
			}
		}
		else {
			if (x < 0x100) { c++; }
			else { c += 2; }
		}
	}
	if (pszOutSjis) { pszOutSjis[c] = '\0'; }
	c++;	// asciiz�p

	return c;	// �K�vbyte��
}


std::string ConvUTF8toSJIS(std::string strUtf8) {
	int n = ConvUTF8toSJIS((const unsigned char *)strUtf8.c_str(), NULL);
	unsigned char *p = new unsigned char[n];
	ConvUTF8toSJIS((const unsigned char *)strUtf8.c_str(), p);
	std::string s =(char*)p;
	delete p;
	return s;
}

std::string ConvSJIStoUTF8(std::string strSjis) {
	int n = ConvSJIStoUTF8((const unsigned char *)strSjis.c_str(), NULL);
	unsigned char *p = new unsigned char[n];
	ConvSJIStoUTF8((const unsigned char *)strSjis.c_str(), p);
	std::string s = (char*)p;
	delete p;
	return s;
}

