//======================================
//	ステージ
//======================================
#include "Stage.h"
#include "TurnBattle.h"
#include "UI.h"
#include "Utility.h"
#include <stdio.h>  // printf()
// 関数プロットタイプ
static void ExecBattle(Stage* stage, Character* enemy);

void InitializeStage(Stage* stage, Character* player, Character* boss)
{
	stage->player = player;
	stage->boss = boss;
	StartCharacter(player);  // プレーヤ生存状態に
	StartCharacter(boss);   // ボス生存状態に
	stage->zakoPtr = 0;
}
// ザコ敵を登録する
void RegistZako(Stage* stage, Character* zako)
{
	if (stage->zakoPtr < ZAKO_SIZE) {
		stage->zako[stage->zakoPtr++] = zako;
	}
}

void DrawMap(Stage* stage)
{
	ClearScreen();
	for (int y = stage->playerY - SCREEN_HEIGHT / 2; y < stage->playerY + SCREEN_HEIGHT / 2; y++) {
		for (int x = stage->playerX - SCREEN_WIDTH / 2; x < stage->playerX + SCREEN_WIDTH / 2; x++) {
			if (x == stage->playerX && y == stage->playerY) {
				printf("勇");
			}
			else {
				char c = GetMapData(stage->mapSpec, x, y);
				if (c == outOfMap) {
					c = stage->mapSpec->outData;
				}
				printf(GetMapAA(c));
			}
		}
		putchar('\n');
	}

	putchar('\n');
	IndicatePlayer(stage->player);
	putchar('\n');
}

// マップチェンジ
void ChangeMap(Stage* stage, NextMap* p)
{
	// ★ここをコーディングしてください
	// NextMapの id からマップスペックを取得して ステージのマップスペックに代入します
	// NextMapの nextX,nextY をプレーヤの位置に代入します
	MapSpec* spec = GetMapSpec(p->nextId);
	stage->mapSpec = spec;
	stage->playerX = p->nextX;
	stage->playerY = p->nextY;

}
// スタートマップにエントリー
void ChangeStartMap(Stage* stage)
{
	// ★ここをコーディングしてください
	// 初期マップ{ MAP_KING_CASTLE,4,6 }のデータで
	// ChangeMap()します
	NextMap next = { MAP_KING_CASTLE,4,6 };
	ChangeMap(stage, &next);
}
// マップスペック取得
MapSpec* GetMapSpec(Stage* stage)
{
	// ★ここをコーディングしてください
	// stageのmapSpecを返します
	return stage->mapSpec;
}
int GetPlayerX(Stage* stage)
{
	// ★ここをコーディングしてください
	// stageのplayerXを返します
	return stage->playerX;
}
int GetPlayerY(Stage* stage)
{
	// ★ここをコーディングしてください
	// stageのplayerYを返します
	return stage->playerY;
}
void SetPlayerPosition(Stage* stage, int playerX, int playerY)
{
	// ★ここをコーディングしてください
	// stageのplayerX,playerYをセットします
	stage->playerX = playerX;
	stage->playerY = playerY;
}
// サゴバトル実行
void BattleZako(Stage* stage)
{
	// ★ここをコーディングしてください
	// 登録されているザコからランダムに選択して、ExecBattle()を実行します
	int idx = GetRand(stage->zakoPtr);
	Character* zako = stage->zako[idx];
	ExecBattle(stage, zako);
}
// ボスバトル実行
void BattleBoss(Stage* stage)
{
	// ★ここをコーディングしてください
	// ボスと ExecBattle()を実行します
	ExecBattle(stage, stage->boss);
}
// バトル実行
static void ExecBattle(Stage* stage, Character* enemy)
{
	TurnBattle btl[1];

	SetTurnBattle(btl, stage->player, enemy);
	StartTurnBattle(btl);
	IntroTurnBattle(btl);
	bool isEnd = false;
	Command cmd;
	while (true) {
		cmd = GetPlayerCommand(btl);
		isEnd = ExecPlayerTurn(btl, cmd);
		if (isEnd) {
			break;
		}
		cmd = GetEnemyCommand();
		isEnd = ExecEnemyTurn(btl, cmd);
		if (isEnd) {
			break;
		}
		NextTurnBattle(btl);
	}
}
// プレーヤ死亡?
bool IsPlayerDead(Stage* stage)
{
	// ★ここをコーディングしてください
	// プレーヤで IsDeadCharacter()を呼びます;
	return IsDeadCharacter(stage->player);
}
// ボス死亡?
bool IsBossDead(Stage* stage)
{
	// ★ここをコーディングしてください
	// ボスで IsDeadCharacter()を呼びます;
	return IsDeadCharacter(stage->boss);
}