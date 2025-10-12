#include "AppFrame.h"
#include "RoomData.h"

void RoomData::LoadJson(int num) {
	// json�t�@�C���̓Ǎ�
	std::ifstream file("res/jsonfile/RoomData/" + std::to_string(num) + ".json");
	nlohmann::json json;
	file >> json;
	int i = 0;
	jsonMax = 0;
	for (int n = 0; n < 100; n++) {
		_indexObjType[n] = 0;
	}

	// �}�b�v�f�[�^�Ǎ�
	json[0].at("keyRoom").get_to(_jsonMapData.keyRoom);
	json[0].at("H").get_to(_jsonMapData.H);
	json[0].at("W").get_to(_jsonMapData.W);
	json[0].at("Steps").get_to(_jsonMapData.Steps);
	json[0].at("boxSize").get_to(_jsonMapData.boxSize);
	json[0].at("pathSky").get_to(_jsonMapData.pathSky);
	json[0].at("map").get_to(_jsonMapData.map);

	// �I�u�W�F�N�g�f�[�^�Ǎ�
	for (auto jsonfile : json[0]["objects"]) {
		JsonObjectData _jobjData;
		jsonfile.at("type").get_to(_jobjData.type);
		jsonfile.at("x").get_to(_jobjData.x);
		jsonfile.at("y").get_to(_jobjData.y);
		jsonfile.at("z").get_to(_jobjData.z);
		jsonfile.at("H").get_to(_jobjData.H);
		jsonfile.at("W").get_to(_jobjData.W);
		jsonfile.at("pathObj").get_to(_jobjData.pathObj);
		jsonfile.at("frameColl").get_to(_jobjData.frameColl);
		jsonfile.at("rx").get_to(_jobjData.rx);
		jsonfile.at("ry").get_to(_jobjData.ry);
		jsonfile.at("rz").get_to(_jobjData.rz);
		jsonfile.at("isMove").get_to(_jobjData.isMove);

		_jsonObjData.push_back(_jobjData);
		_indexObjType[_jobjData.type] = i;
		jsonMax++;
		i++;
	}
}

void RoomData::DeleteJsonData() {
	// ���f������
	_jsonObjData.clear();
}

void RoomData::LoadModelHandle() {
	for (int i = 0; i < _jsonObjData.size(); i++) {
		_jsonObjData[i].handleBase = MV1LoadModel(_jsonObjData[i].pathObj.c_str());
	}
}

void RoomData::RoomLoad(int num) {
	LoadJson(num);
	_roomNum = GetkeyRoom();
	_mapH = GetMapSize_H();
	_mapW = GetMapSize_W();
	_mapSize = _mapH * _mapW;
	_mapSteps = GetMapSteps();
	_boxSize = GetBoxSize();
	_isViewMap = false;
}

void RoomData::RoomInit() {
	// �󃂃f��
	_handleSkySphere = GetHandleSky();

	// �I�u�W�F�N�g�f�[�^�̏�����
	// �}�b�v�`�b�v�i���E�ǁj
	if (_mapSize != 1) {
		for (int s = 0; s < _mapSteps; s++) {
			for (int i = 0; i < _mapSize; i++) {
				ObjectData data;
				int indexObj;
				VECTOR vRota;
				data._mapType = GetMapTip(s, i);
				int n = i / _mapW;

				if (data._mapType != 0) {
					// �}�b�v�`�b�v�ԍ��ɑΉ��������f�����擾
					switch (data._mapType) {
					case 1:		// ��
					case 2:		// �x���g�R���x�A��(+X)
					case 3:		// �x���g�R���x�A��(-X)
					case 4:		// �x���g�R���x�A��(+Y)
					case 5:		// �x���g�R���x�A��(-Y)
					case 10:	// ��
						indexObj = GetIndexObj(data._mapType);
						break;
					default:
						indexObj = GetIndexObj(1);
					}
					// �I�u�W�F�N�g�^�C�v
					data._objType = GetObjType(indexObj);
					// ���f��
					data._handle = MV1DuplicateModel(GetHandleObj(indexObj));
					// �ʒu���
					data._vPos = VGet((i % _mapW) * _boxSize, s * _boxSize, -n * _boxSize);
					// ���f����]
					vRota = VScale(GetObjVRota(indexObj), DX_PI_F / 180.f);
					MV1SetRotationXYZ(data._handle, vRota);
					// ���f���ʒu�Z�b�g
					MV1SetPosition(data._handle, data._vPos);
					// �R���W�����t���[��
					data._frameCollision = GetFrameObjColl(indexObj, data._handle);
					// �R���W������񐶐�
					MV1SetupCollInfo(data._handle, data._frameCollision, 16, 16, 16);
					MV1SetFrameVisible(data._handle, data._frameCollision, _isViewMap);

					// 6212�i�����Ȃ������j�̓e�N�X�`����\�����Ȃ�
					if (_roomNum == 6212) {
						int frametex = MV1SearchFrame(data._handle, "keisanheya_yuka_low4");
						MV1SetFrameVisible(data._handle, frametex, FALSE);
					}

					// �ړ��\�t���O�ݒ�
					data._isMove = GetObjIsMove(indexObj);

					// �I�u�W�F�N�g�f�[�^�ǉ�
					_objData.push_back(data);
				}
			}
		}
	}
	// �I�u�W�F�N�g�E�}�b�v
	for (int i = 0; i < GetObjSize(); i++) {
		ObjectData data;
		VECTOR vRota;
		data._objType = GetObjType(i);
		if (!(data._objType >= 2 && data._objType <= 6) && data._objType != 10) {
			if (!(data._objType == 1 && _mapSize != 1)) {
				// �}�b�v��̃I�u�W�F�N�g�̐ݒ�
				data._mapType = GetObjType(i);
				// �ʒu���
				data._vPos = GetObjVPos(i);
				data._vPos.y += 250.f;
				// ���f��
				data._handle = MV1DuplicateModel(GetHandleObj(i));
				// ���f����]
				vRota = VScale(GetObjVRota(i), DX_PI_F / 180.f);
				MV1SetRotationXYZ(data._handle, vRota);
				//���f���ʒu�Z�b�g
				MV1SetPosition(data._handle, data._vPos);
				// �t���[���R���W����
				data._frameCollision = GetFrameObjColl(i, data._handle);
				// �R���W������񐶐�
				MV1SetupCollInfo(data._handle, data._frameCollision, 16, 16, 16);
				MV1SetFrameVisible(data._handle, data._frameCollision, FALSE);
				// �ړ������p
				data._vDir = VGet(0.f, 0.f, -1.f);
				data._vMove = VGet(0.f, 0.f, 0.f);
				data._vToPos = data._vPos;

				// �ړ��\�t���O�ݒ�
				data._isMove = GetObjIsMove(i);

				// �I�u�W�F�N�g�f�[�^�ǉ�
				_objData.push_back(data);
			}
		}
	}
}

void RoomData::RoomRelease() {
	// json����ǂݍ��񂾃f�[�^�̉��
	_jsonMapData.keyRoom = 0;
	_jsonMapData.H = 0;
	_jsonMapData.W = 0;
	_jsonMapData.Steps = 0;
	_jsonMapData.boxSize = 0;
	_jsonMapData.pathSky.clear();
	_jsonMapData.map.clear();

	// json����ǂݍ��񂾃I�u�W�F�N�g�f�[�^
	_jsonObjData.clear();

	// �}�b�v�f�[�^
	_roomNum = 0;
	_mapH = 0;
	_mapW = 0;
	_mapSteps = 0;
	_mapSize = 0;
	_boxSize = 0;
	_isViewMap = false;
	_handleSkySphere = -1;

	// �I�u�W�F�N�g�f�[�^
	_objData.clear();
}

bool RoomData::IsLoad() {
	if (GetASyncLoadNum() > 0) {
		return true;
	}
	else {
		return false;
	}
}
