#include "AppFrame.h"
#include "RoomData.h"

void RoomData::LoadJson(int num) {
	// jsonファイルの読込
	std::ifstream file("res/jsonfile/RoomData/" + std::to_string(num) + ".json");
	nlohmann::json json;
	file >> json;
	int i = 0;
	jsonMax = 0;
	for (int n = 0; n < 100; n++) {
		_indexObjType[n] = 0;
	}

	// マップデータ読込
	json[0].at("keyRoom").get_to(_jsonMapData.keyRoom);
	json[0].at("H").get_to(_jsonMapData.H);
	json[0].at("W").get_to(_jsonMapData.W);
	json[0].at("Steps").get_to(_jsonMapData.Steps);
	json[0].at("boxSize").get_to(_jsonMapData.boxSize);
	json[0].at("pathSky").get_to(_jsonMapData.pathSky);
	json[0].at("map").get_to(_jsonMapData.map);

	// オブジェクトデータ読込
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
	// モデル消去
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
	// 空モデル
	_handleSkySphere = GetHandleSky();

	// オブジェクトデータの初期化
	// マップチップ（床・壁）
	if (_mapSize != 1) {
		for (int s = 0; s < _mapSteps; s++) {
			for (int i = 0; i < _mapSize; i++) {
				ObjectData data;
				int indexObj;
				VECTOR vRota;
				data._mapType = GetMapTip(s, i);
				int n = i / _mapW;

				if (data._mapType != 0) {
					// マップチップ番号に対応したモデルを取得
					switch (data._mapType) {
					case 1:		// 床
					case 2:		// ベルトコンベア床(+X)
					case 3:		// ベルトコンベア床(-X)
					case 4:		// ベルトコンベア床(+Y)
					case 5:		// ベルトコンベア床(-Y)
					case 10:	// 壁
						indexObj = GetIndexObj(data._mapType);
						break;
					default:
						indexObj = GetIndexObj(1);
					}
					// オブジェクトタイプ
					data._objType = GetObjType(indexObj);
					// モデル
					data._handle = MV1DuplicateModel(GetHandleObj(indexObj));
					// 位置情報
					data._vPos = VGet((i % _mapW) * _boxSize, s * _boxSize, -n * _boxSize);
					// モデル回転
					vRota = VScale(GetObjVRota(indexObj), DX_PI_F / 180.f);
					MV1SetRotationXYZ(data._handle, vRota);
					// モデル位置セット
					MV1SetPosition(data._handle, data._vPos);
					// コリジョンフレーム
					data._frameCollision = GetFrameObjColl(indexObj, data._handle);
					// コリジョン情報生成
					MV1SetupCollInfo(data._handle, data._frameCollision, 16, 16, 16);
					MV1SetFrameVisible(data._handle, data._frameCollision, _isViewMap);

					// 6212（何もない部屋）はテクスチャを表示しない
					if (_roomNum == 6212) {
						int frametex = MV1SearchFrame(data._handle, "keisanheya_yuka_low4");
						MV1SetFrameVisible(data._handle, frametex, FALSE);
					}

					// 移動可能フラグ設定
					data._isMove = GetObjIsMove(indexObj);

					// オブジェクトデータ追加
					_objData.push_back(data);
				}
			}
		}
	}
	// オブジェクト・マップ
	for (int i = 0; i < GetObjSize(); i++) {
		ObjectData data;
		VECTOR vRota;
		data._objType = GetObjType(i);
		if (!(data._objType >= 2 && data._objType <= 6) && data._objType != 10) {
			if (!(data._objType == 1 && _mapSize != 1)) {
				// マップ上のオブジェクトの設定
				data._mapType = GetObjType(i);
				// 位置情報
				data._vPos = GetObjVPos(i);
				data._vPos.y += 250.f;
				// モデル
				data._handle = MV1DuplicateModel(GetHandleObj(i));
				// モデル回転
				vRota = VScale(GetObjVRota(i), DX_PI_F / 180.f);
				MV1SetRotationXYZ(data._handle, vRota);
				//モデル位置セット
				MV1SetPosition(data._handle, data._vPos);
				// フレームコリジョン
				data._frameCollision = GetFrameObjColl(i, data._handle);
				// コリジョン情報生成
				MV1SetupCollInfo(data._handle, data._frameCollision, 16, 16, 16);
				MV1SetFrameVisible(data._handle, data._frameCollision, FALSE);
				// 移動処理用
				data._vDir = VGet(0.f, 0.f, -1.f);
				data._vMove = VGet(0.f, 0.f, 0.f);
				data._vToPos = data._vPos;

				// 移動可能フラグ設定
				data._isMove = GetObjIsMove(i);

				// オブジェクトデータ追加
				_objData.push_back(data);
			}
		}
	}
}

void RoomData::RoomRelease() {
	// jsonから読み込んだデータの解放
	_jsonMapData.keyRoom = 0;
	_jsonMapData.H = 0;
	_jsonMapData.W = 0;
	_jsonMapData.Steps = 0;
	_jsonMapData.boxSize = 0;
	_jsonMapData.pathSky.clear();
	_jsonMapData.map.clear();

	// jsonから読み込んだオブジェクトデータ
	_jsonObjData.clear();

	// マップデータ
	_roomNum = 0;
	_mapH = 0;
	_mapW = 0;
	_mapSteps = 0;
	_mapSize = 0;
	_boxSize = 0;
	_isViewMap = false;
	_handleSkySphere = -1;

	// オブジェクトデータ
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
