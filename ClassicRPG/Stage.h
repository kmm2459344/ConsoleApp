//======================================
//	ステージ
//======================================
#ifndef __STAGE_H
#define __STAGE_H
#include "Map.h"
#include "Character.h"

const int ZAKO_SIZE = 10;

typedef struct {
	MapSpec* mapSpec;
	int playerX;
	int playerY;
	Character* player;
	Character* boss;
	Character* zako[ZAKO_SIZE];
	int zakoPtr;
} Stage;

// 初期化
void InitializeStage(Stage* stage, Character* player, Character* boss);
// ザコ敵を登録
void RegistZako(Stage* stage, Character* zako);
// マップ変更
void ChangeMap(Stage* stage, NextMap* next);
// スタートマップにエントリー
void ChangeStartMap(Stage* stage);
// マップ描画
void DrawMap(Stage* stage);
// ザコバトル実行
void BattleZako(Stage* stage);
// ボスバトル実行
void BattleBoss(Stage* stage);
// マップスペック取得
MapSpec* GetMapSpec(Stage* stage);
// プレーヤX座標を取得
int GetPlayerX(Stage* stage);
// プレーヤY座標を取得
int GetPlayerY(Stage* stage);
// プレーヤ座標をセット
void SetPlayerPosition(Stage* stage, int playerX, int playerY);
// プレーヤ死亡?
bool IsPlayerDead(Stage* stage);
// ボス死亡?
bool IsBossDead(Stage* stage);

#endif //  __STAGE_H