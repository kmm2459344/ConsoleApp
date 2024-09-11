//======================================
//	マップ
//======================================
#include "Map.h"
#include <assert.h>
// 画数プロトタイプ
static bool isInMap(int x, int y);

MapArray mapField = {
        "~~~~~~~~~~~~~~~~",
        "~~MMMMM~~MMMM.~~",
        "~M...M.##..M...~",
        "~M.M.M.~~M.M.M.~",
        "~M.M...~~M...M.~",
        "~M.MMMM~~MMMM..~",
        "~M..MM.~~~~~~#~~",
        "~~M.M.~~~~~~~#~~",
        "~~M.MM~~~~BMM..~",
        "~~...MM~~M.MMM.~",
        "~...~~M~~M...M.~",
        "~..~~~K~~MMM.M.~",
        "~..~~~.~~M...M.~",
        "~......~~M.MM..~",
        "~~....~~~~....~~",
        "~~~~~~~~~~~~~~~~"
};
MapArray mapKingCastle = {
        "HHH.......HHH",
        "H.H.......H.H",
        "HHHHHHHHHHHHH",
        ".H.........H.",
        ".H.HHH.HHH.H.",
        ".H.H0H.H1H.H.",
        ".H.........H.",
        ".HW.......WH.",
        ".HY.......YH.",
        "HHHHHH.HHHHHH",
        "H.H~~~#~~~H.H",
        "HHH~~~#~~~HHH",
        ".............."
};
MapArray mapBossCastle = {
       "HHH.......HHH",
        "H.H.......H.H",
        "HHHHHHHHHHHHH",
        ".H....H....H.",
        ".H..WHHHW..H.",
        ".H..YH2HY..H.",
        ".H.........H.",
        ".H..W...W..H.",
        ".H..Y...Y..H.",
        ".H.........H.",
        "HHHHHH.HHHHHH",
        "H.H~~~#~~~H.H",
        "HHH~~~#~~~HHH",
        "~~~~~~#~~~~~~",
        "~~~~~~#~~~~~~",
        "............."
};

MapSpec specField = {
    &mapField,                // mapArray
    '~',                      // outData
    { MAP_NONE,0,0 },         // nextMap_Out
    { MAP_KING_CASTLE,6,12},  // nextMap_K
    { MAP_BOSS_CASTLE,6,15},  // nextMap_B
    true,                     // isBattleEncount
};

MapSpec specKingCastle = {
    &mapKingCastle,     // mapArray
    '.',                // outData
    { MAP_FIELD,6,12},  // nextMap_Out
    { MAP_NONE,0,0},    // nextMap_K
    { MAP_NONE,0,0},    // nexrMap_B
    false,              // isBattleEncount
};

MapSpec specBossCastle = {
    &mapBossCastle,     // mapArray
    '.',                // outData
    { MAP_FIELD,10,9},  // nextMap_Out
    { MAP_NONE,0,0},    // nextMap_K
    { MAP_NONE,0,0},    // nexrMap_B
    false,              // isBattleEncount
};
// idからマップスペックを取得
MapSpec* GetMapSpec(MapId id)
{
    static MapSpec* specs[] = {
        &specField,
        &specKingCastle,
        &specBossCastle,
    };
    const int specsSize = sizeof(specs) / sizeof(specs[0]);
    // ★ここをコーディングしてください。
    // idが 0～specsSize-1 であることをassertで確認し
    // specs[id]を返します
    assert(0 <= id && id < specsSize);
    return specs[id];
    
}
// マップデータを取得
char GetMapData(MapSpec* spec, int x, int y)
{
    // ★ここをコーディングしてください。
    // 座標がマップ内か確認します
    // spaceのarray[y][x]をアクセスして、'\0'でなければそれを返します
    // マップ外または '\0' なら outOfMapコードを返します
    if (isInMap(x, y)) {
        char c = (*spec->array)[y][x];
        if (c != '\0') {
            return c;
        }
    }
}
// マップのAA(アスキーアート)を取得
const char* GetMapAA(char c)
{
    switch (c) {
    case '~':   return "～";  // 海
    case '.':   return "．";  // 平地
    case 'M':   return "Ｍ";  // 山
    case '#':   return "＃";  // 橋
    case 'K':   return "王";  // 王様の城
    case 'B':   return "魔";  // 魔王の城
    case 'H':   return "□";  // 壁
    case 'W':   return "炎";  // 炎
    case 'Y':   return "Ｙ";  // 燭台
    case '0':   return "王";  // 王
    case '1':   return "姫";  // 姫
    case '2':   return "魔";  // 魔王
    }
    assert(false);
    return "";
}
bool IsBattleEncount(MapSpec* spec)
{
    // ★ここをコーディングしてください
    // specのisBattleEncount を返します
    return spec->isBattleEncount;
}

static bool isInMap(int x, int y)
{
    // ★ここをコーディングしてください
    //  xが 0 ～MAP_WIDTH かつ yが 0～MAP_HEIGHTを調べます
    return 0 <= x && x < MAP_WIDTH && 0 <= y && y < MAP_HEIGHT;
}