//======================================
//	マップ
//======================================
#ifndef __MAP_H
#define __MAP_H

const int MAP_WIDTH = 16;
const int MAP_HEIGHT = 16;
const int SCREEN_WIDTH = 16;
const int SCREEN_HEIGHT = 12;

typedef char MapArray[MAP_HEIGHT][MAP_WIDTH + 1];

const char outOfMap = '*';

// マップID
typedef enum {
	MAP_FIELD,        // フィールド
	MAP_KING_CASTLE,  // 王様の城
	MAP_BOSS_CASTLE,  // ボスの城
	MAP_NONE = -1,
} MapId;

// 次のマップとエントリー位置
typedef struct {
	MapId nextId;
	int nextX, nextY;
} NextMap;

// マップスペック
typedef struct {
	MapArray* array;        // マップ
	char    outData;        // マップ外のデータ
	NextMap nextMap_Out;    // マップ出たときの行先
	NextMap nextMap_K;      // K 踏んだ時の行先
	NextMap nextMap_B;      // B 踏んだ時の行先
	bool isBattleEncount;   // バトルエンカウントするか?
} MapSpec;

// マップデータを取得
char GetMapData(MapSpec* spec, int x, int y);
// idからマップスペックを取得
MapSpec* GetMapSpec(MapId id);
// マップデータのAAを取得
const char* GetMapAA(char c);
// マップ内にいるか?
bool IsInMap(int x, int y);
// バトルエンカウントありか?
bool IsBattleEncount(MapSpec* spec);

#endif //  __MAP_H
#pragma once
