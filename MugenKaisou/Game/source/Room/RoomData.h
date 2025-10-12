#pragma once

#include "appframe.h"
#include "nlohmann/json.hpp"
#include <iostream>
#include <fstream>
#include <string>

class RoomData
{
public:
	// ファイルからデータ読込
	void LoadJson(int num);

	// マップデータ----------------------------------------------------------------------
	// データ取得
	int GetkeyRoom() { return _jsonMapData.keyRoom; }		// 部屋番号
	int GetMapSize_H() { return _jsonMapData.H; }			// マップサイズ（縦）
	int GetMapSize_W() { return _jsonMapData.W; }			// マップサイズ（横）
	int GetMapSteps() { return _jsonMapData.Steps; }			// マップ段数
	int GetBoxSize() { return _jsonMapData.boxSize; }		// マップチップサイズ
	int GetMapTip(int step, int i) { return _jsonMapData.map[step][i]; }		// マップチップ

	// 空マップモデル
	int GetHandleSky() {
		return MV1LoadModel(_jsonMapData.pathSky.c_str());
	}

	// データ消去
	void DeleteJsonData();

	// オブジェクトデータ----------------------------------------------------------------------
	// データ取得
	int GetObjSize() { return _jsonObjData.size(); }				// オブジェクト数
	int GetObjType(int i) { return _jsonObjData[i].type; }		// オブジェクトタイプ
	int GetObjSize_H(int i) { return _jsonObjData[i].H; }		// オブジェクトサイズ（縦）
	int GetObjSize_W(int i) { return _jsonObjData[i].W; }		// オブジェクトサイズ（縦）
	int GetObjIsMove(int i) { return _jsonObjData[i].isMove; }	// オブジェクトの移動可能フラグ（0：不可, 1：可能）
	VECTOR GetObjVPos(int i) { return VGet(_jsonObjData[i].x, _jsonObjData[i].y, _jsonObjData[i].z); }		// オブジェクト位置情報
	VECTOR GetObjVRota(int i) { return VGet(_jsonObjData[i].rx, _jsonObjData[i].ry, _jsonObjData[i].rz); }	// オブジェクト回転情報

	// オブジェクトモデル
	int GetHandleObj(int i) {
		return _jsonObjData[i].handleBase;
	}
	// オブジェクトコリジョンフレーム
	int GetFrameObjColl(int i, int handleObj) {
		return MV1SearchFrame(handleObj, _jsonObjData[i].frameColl.c_str());
	}

	// オブジェクトタイプに対応したJSONデータのインデックス（要素番号）取得
	int GetIndexObj(int objType) { return _indexObjType[objType]; }

	void LoadModelHandle();		// オブジェクトの3Dモデル取得
	void RoomLoad(int num);		// マップ情報読み込み・取得
	void RoomInit();			// マップ初期化
	void RoomRelease();			// マップデータ解放
	bool IsLoad();				// 非同期ロード中かどうか
private:
	// jsonから読み込んだデータ
	struct JsonData {
		int keyRoom;						// 部屋番号
		int H, W;							// マップサイズ（縦, 横）
		int Steps;							// マップ段数
		int boxSize;						// マップチップサイズ
		std::string pathSky;				// 空モデルパス
		std::vector<std::vector<int>> map;	// マップチップ
	};
	JsonData _jsonMapData;
	
	// jsonから読み込んだオブジェクトデータ
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

	// オブジェクトタイプに対応したインデックス格納配列
	int _indexObjType[100];

	int jsonMax;
public:
	// オブジェクトデータ
	struct ObjectData {
		int _objType;			// オブジェクトタイプ
		int _mapType;			// マップチップタイプ
		int _handle;			// モデル
		int _frameCollision;	// コリジョンフレーム
		int _isMove;			// 移動可能フラグ
		VECTOR _vPos;			// 位置

		// 移動処理用
		VECTOR _vDir;			// 向き
		VECTOR _vMove;			// 移動量
		VECTOR _vToPos;			// 移動先位置
	};
	std::vector<ObjectData> _objData;

	// マップデータ
	int _roomNum;		// 部屋番号
	int _mapH, _mapW;	// マップサイズ（H：縦, W：横）
	int _mapSteps;		// マップ段数
	int _mapSize;		// マップサイズ（縦×横）
	int _boxSize;		// マップチップサイズ

	bool _isViewMap;
	int _handleSkySphere;	// 空モデル
};
