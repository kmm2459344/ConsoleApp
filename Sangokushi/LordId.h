//======================================
//	戦国シミュレーション  城主ID
//======================================
#ifndef __LORD_ID_H
#define __LORD_ID_H

typedef enum {
    LORD_RIKAKU,    // 李傕
    LORD_RYUBI,     // 劉備
    LORD_ENSHO,     // 袁紹
    LORD_SOSO,      // 曹操
    LORD_RYOFU,     // 呂布
    LORD_RYUHYO,    // 劉表
    LORD_SONSAKU,   // 孫策
    LORD_RYUSHO,    // 劉璋
    LORD_BATO,      // 馬騰
    LORD_KOSONSAN,  // 公孫瓚
    LORD_MAX,       // (種類の数)
    LORD_NONE = -1,
} LordId;

#endif //  __LORD_ID_H