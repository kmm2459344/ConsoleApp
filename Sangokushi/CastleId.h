//======================================
//	戦国シミュレーション  城ID
//======================================
#ifndef __CASTLE_ID_H
#define __CASTLE_ID_H

typedef enum
{
    CASTLE_SHIREI,  // 司隸
    CASTLE_YOSHU,   // 豫州
    CASTLE_KISHU,   // 冀州
    CASTLE_ENSHU,   // 兗州
    CASTLE_JOSHU,   // 徐州
    CASTLE_KEISHU,  // 荊州
    CASTLE_YOUSHU,  // 揚州
    CASTLE_EKISHU,  // 益州
    CASTLE_RYOSHU,  // 涼州
    CASTLE_YUSHU,   // 幽州
    CASTLE_MAX,      // 種類の数
    CASTLE_NONE = -1,         // リスト終端
} CastleId;

#endif //  __CASTLE_ID_H