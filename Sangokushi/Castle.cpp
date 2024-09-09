//======================================
//	戦国シミュレーション  城
//======================================
#include "Castle.h"
#include "Lord.h"
#include "Troop.h"

Castle castles[] =
{
	// CASTLE_SHIREI 司隸
	{
		"司隸",   // 名前
		LORD_RIKAKU,  // 城主
		TROOP_BASE, // 兵数
		// 接続された城のリスト
		{
			CASTLE_YOSHU,   // 豫州
			CASTLE_KISHU,   // 冀州
			CASTLE_ENSHU,   // 兗州
			CASTLE_KEISHU,  // 荊州
			CASTLE_EKISHU,  // 益州
			CASTLE_RYOSHU,  // 涼州
			CASTLE_NONE,
		},
		 7, 7,      // 描画位置
		"司隸",     // マップ上の名前
	},
	// CASTLE_YOSHU  豫州
	{
		"豫州"   ,     // 名前
		LORD_RYUBI,    // 城主
		TROOP_BASE,     // 兵数
		// 接続された城のリスト
		{
			CASTLE_SHIREI,  // 司隸 
			CASTLE_ENSHU,   // 兗州
			CASTLE_JOSHU,   // 徐州
			CASTLE_KEISHU,  // 荊州
			CASTLE_YOUSHU,  // 揚州
			CASTLE_NONE,
		},
		19, 9,          // 描画位置
		"豫州",         // マップ上の名前
	},
	// CASTLE_KISHU  冀州
	{
		"冀州",         // 名前
		LORD_ENSHO,     // 城主
		TROOP_BASE,     // 兵数
		// 接続された城のリスト
		{
			CASTLE_SHIREI,  // 司隸
			CASTLE_ENSHU,   // 兗州
			CASTLE_JOSHU,   // 徐州
			CASTLE_YUSHU,   // 幽州
			CASTLE_NONE,
		},
		19, 3,          // 描画位置
		"冀州",         // マップ上の名前
	},
	// CASTLE_ENSHU  兗州
	{
		"兗州",     // 名前
		LORD_SOSO,  // 城主
		TROOP_BASE, // 兵数
		// 接続された城のリスト
		{
			CASTLE_SHIREI,  // 司隸
			CASTLE_YOSHU,   // 豫州
			CASTLE_KISHU,   // 冀州
			CASTLE_JOSHU,   // 徐州
			CASTLE_NONE,
		},
		19, 6,      // 描画位置
		"兗州",     // マップ上の名前
	},
	// CASTLE_JOSHU  徐州
	{
		"徐州",         // 名前
		LORD_RYOFU,     // 城主
		TROOP_BASE,     // 兵数
		// 接続された城のリスト
		{
			CASTLE_YOSHU,   // 豫州
			CASTLE_KISHU,   // 冀州
			CASTLE_ENSHU,   // 兗州
			CASTLE_YOUSHU,  // 揚州
			CASTLE_NONE,
		},
		27, 7,          // 描画位置
		"徐州",         // マップ上の名前
	},
	// CASTLE_KEISHU 荊州
	{
		"荊州",       // 名前
		LORD_RYUHYO,  // 城主
		TROOP_BASE,   // 兵数
		// 接続された城のリスト
		{
			CASTLE_SHIREI,  // 司隸
			CASTLE_YOSHU,   // 豫州
			CASTLE_YOUSHU,  // 揚州
			CASTLE_EKISHU,  // 益州
			CASTLE_NONE,
		},
		11,11,      // 描画位置
		"荊州",     // マップ上の名前
	},
	// CASTLE_YOUSHU 揚州
	{
		"揚州",         // 名前
		LORD_SONSAKU,   // 城主
		TROOP_BASE,     // 兵数
		// 接続された城のリスト
		{
			CASTLE_YOSHU,   // 豫州
			CASTLE_JOSHU,   // 徐州
			CASTLE_KEISHU,  // 荊州
			CASTLE_NONE,
		},
		25,11,          // 描画位置
		"揚州",         // マップ上の名前
	},
	// CASTLE_EKISHU 益州
	{
		"益州",   // 名前
		LORD_RYUSHO,      // 城主
		TROOP_BASE,     // 兵数
		// 接続された城のリスト
		{
			CASTLE_SHIREI,  // 司隸
			CASTLE_KEISHU,  // 荊州
			CASTLE_NONE,
		},
		 1,11,          // 描画位置
		"益州",         // マップ上の名前
	},
	// CASTLE_RYOSHU 涼州
	{
		"涼州",         // 名前
		LORD_BATO,     // 城主
		TROOP_BASE,     // 兵数
		// 接続された城のリスト
		{
			CASTLE_SHIREI,  // 司隸
			CASTLE_NONE,
		},
		 1, 3,          // 描画位置
		"涼州",         // マップ上の名前
	},
	// CASTLE_YUSHU 幽州
	{
		"幽州",         // 名前
		LORD_KOSONSAN,    // 城主
		TROOP_BASE,     // 兵数
		//  接続された城のリスト
		{
			CASTLE_KISHU,   // 冀州
			CASTLE_NONE,
		},
		29, 1,          // 描画位置
		"幽州",         // マップ上の名前
	},
};
// 城の名前を取得
const char* GetCastleName(Castle* castle)
{
	return castle->name;
}
// 城主IDを取得
LordId GetCastleOwner(Castle* castle)
{
	return castle->owner;
}
// 兵数を取得
int GetCastleTroopCount(Castle* castle)
{
	return castle->troopCount;
}
// 近隣の城リストを取得
CastleId* GetCastleConnectedList(Castle* castle)
{
	return castle->connectedList;
}
// 描画X座標を取得
int GetCastleCurx(Castle* castle)
{
	return castle->curx;
}
// 描画Y座標を取得
int GetCastleCury(Castle* castle)
{
	return castle->cury;
}
// マップ上の名前を取得
const char* GetCastleMapName(Castle* castle)
{
	return castle->mapName;
}
// 兵数を代入する
void SetCastleTroopCount(Castle* castle, int troopCount)
{
	castle->troopCount = troopCount;
}
// 城主をセット
void SetCastleOwner(Castle* castle, LordId owner)
{
	castle->owner = owner;
}
// 兵数に加算
void AddCastleTroopCount(Castle* castle, int add)
{
	int value = castle->troopCount + add;
	if (value < 0) {
		value = 0;
	}
	else if (value > TROOP_MAX) {
		value = TROOP_MAX;
	}
	castle->troopCount = value;
}