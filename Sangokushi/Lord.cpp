//======================================
//	戦国シミュレーション  城主
//======================================
#include "Lord.h"

typedef struct {
    const char* familyName;   // 姓
    const char* firstName;    // 名
    const char* mapName;      // マップ上の名前
} LordName;

static LordName lordNames[LORD_MAX] = {
    {"李傕",      "稚然", "李傕"},   // LORD_RIKAKU    李傕
    {"劉備",      "玄徳", "劉備"},   // LORD_RYUBI     劉備
    {"袁紹",      "本初", "袁紹"},   // LORD_ENSHO     袁紹
    {"曹操",      "孟徳", "曹操"},   // LORD_SOSO      曹操
    {"呂布",      "奉先", "呂布"},   // LORD_RYOFU     呂布
    {"劉表",      "景升", "劉表"},   // LORD_RYUHYO    劉表
    {"孫策",      "伯符", "孫策"},   // LORD_SONSAKU   孫策
    {"劉璋",      "季玉", "劉璋"},   // LORD_RYUSHO    劉璋
    {"馬騰",      "寿成", "馬騰"},   // LORD_BATO      馬騰
    {"公孫瓚",    "伯珪", "公孫"},   // LORD_KOSONSAN  公孫瓚
};

// 城主の名を取得
const char* GetLordFirstName(LordId id)
{
    if (0 <= id && id < LORD_MAX) {
        return lordNames[id].firstName;
    }
    return "??";
}
// 城主の姓を取得
const char* GetLordFamilyName(LordId id)
{
    if (0 <= id && id < LORD_MAX) {
        return lordNames[id].familyName;
    }
    return "??";
}
// 城主のマップ上の名前を取得
const char* GetLordMapName(LordId id)
{
    if (0 <= id && id < LORD_MAX) {
        return lordNames[id].mapName;
    }
    return "??";
}