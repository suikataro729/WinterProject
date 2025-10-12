#pragma once

#include "appframe.h"
#include "nlohmann/json.hpp"
#include <iostream>
#include <fstream>
#include <string>

class RoomData
{
public:
	// �t�@�C������f�[�^�Ǎ�
	void LoadJson(int num);

	// �}�b�v�f�[�^----------------------------------------------------------------------
	// �f�[�^�擾
	int GetkeyRoom() { return _jsonMapData.keyRoom; }		// �����ԍ�
	int GetMapSize_H() { return _jsonMapData.H; }			// �}�b�v�T�C�Y�i�c�j
	int GetMapSize_W() { return _jsonMapData.W; }			// �}�b�v�T�C�Y�i���j
	int GetMapSteps() { return _jsonMapData.Steps; }			// �}�b�v�i��
	int GetBoxSize() { return _jsonMapData.boxSize; }		// �}�b�v�`�b�v�T�C�Y
	int GetMapTip(int step, int i) { return _jsonMapData.map[step][i]; }		// �}�b�v�`�b�v

	// ��}�b�v���f��
	int GetHandleSky() {
		return MV1LoadModel(_jsonMapData.pathSky.c_str());
	}

	// �f�[�^����
	void DeleteJsonData();

	// �I�u�W�F�N�g�f�[�^----------------------------------------------------------------------
	// �f�[�^�擾
	int GetObjSize() { return _jsonObjData.size(); }				// �I�u�W�F�N�g��
	int GetObjType(int i) { return _jsonObjData[i].type; }		// �I�u�W�F�N�g�^�C�v
	int GetObjSize_H(int i) { return _jsonObjData[i].H; }		// �I�u�W�F�N�g�T�C�Y�i�c�j
	int GetObjSize_W(int i) { return _jsonObjData[i].W; }		// �I�u�W�F�N�g�T�C�Y�i�c�j
	int GetObjIsMove(int i) { return _jsonObjData[i].isMove; }	// �I�u�W�F�N�g�̈ړ��\�t���O�i0�F�s��, 1�F�\�j
	VECTOR GetObjVPos(int i) { return VGet(_jsonObjData[i].x, _jsonObjData[i].y, _jsonObjData[i].z); }		// �I�u�W�F�N�g�ʒu���
	VECTOR GetObjVRota(int i) { return VGet(_jsonObjData[i].rx, _jsonObjData[i].ry, _jsonObjData[i].rz); }	// �I�u�W�F�N�g��]���

	// �I�u�W�F�N�g���f��
	int GetHandleObj(int i) {
		return _jsonObjData[i].handleBase;
	}
	// �I�u�W�F�N�g�R���W�����t���[��
	int GetFrameObjColl(int i, int handleObj) {
		return MV1SearchFrame(handleObj, _jsonObjData[i].frameColl.c_str());
	}

	// �I�u�W�F�N�g�^�C�v�ɑΉ�����JSON�f�[�^�̃C���f�b�N�X�i�v�f�ԍ��j�擾
	int GetIndexObj(int objType) { return _indexObjType[objType]; }

	void LoadModelHandle();		// �I�u�W�F�N�g��3D���f���擾
	void RoomLoad(int num);		// �}�b�v���ǂݍ��݁E�擾
	void RoomInit();			// �}�b�v������
	void RoomRelease();			// �}�b�v�f�[�^���
	bool IsLoad();				// �񓯊����[�h�����ǂ���
private:
	// json����ǂݍ��񂾃f�[�^
	struct JsonData {
		int keyRoom;						// �����ԍ�
		int H, W;							// �}�b�v�T�C�Y�i�c, ���j
		int Steps;							// �}�b�v�i��
		int boxSize;						// �}�b�v�`�b�v�T�C�Y
		std::string pathSky;				// �󃂃f���p�X
		std::vector<std::vector<int>> map;	// �}�b�v�`�b�v
	};
	JsonData _jsonMapData;
	
	// json����ǂݍ��񂾃I�u�W�F�N�g�f�[�^
	struct JsonObjectData {
		int type;
		int x, y, z;
		int H, W;
		std::string pathObj;
		int handleBase;
		std::string frameColl;
		int rx, ry, rz;
		int isMove;
	};
	std::vector<JsonObjectData> _jsonObjData;

	// �I�u�W�F�N�g�^�C�v�ɑΉ������C���f�b�N�X�i�[�z��
	int _indexObjType[100];

	int jsonMax;
public:
	// �I�u�W�F�N�g�f�[�^
	struct ObjectData {
		int _objType;			// �I�u�W�F�N�g�^�C�v
		int _mapType;			// �}�b�v�`�b�v�^�C�v
		int _handle;			// ���f��
		int _frameCollision;	// �R���W�����t���[��
		int _isMove;			// �ړ��\�t���O
		VECTOR _vPos;			// �ʒu

		// �ړ������p
		VECTOR _vDir;			// ����
		VECTOR _vMove;			// �ړ���
		VECTOR _vToPos;			// �ړ���ʒu
	};
	std::vector<ObjectData> _objData;

	// �}�b�v�f�[�^
	int _roomNum;		// �����ԍ�
	int _mapH, _mapW;	// �}�b�v�T�C�Y�iH�F�c, W�F���j
	int _mapSteps;		// �}�b�v�i��
	int _mapSize;		// �}�b�v�T�C�Y�i�c�~���j
	int _boxSize;		// �}�b�v�`�b�v�T�C�Y

	bool _isViewMap;
	int _handleSkySphere;	// �󃂃f��
};
