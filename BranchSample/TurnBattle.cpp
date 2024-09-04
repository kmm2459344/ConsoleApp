//======================================
//	ターン制バトル
//======================================
#include "TurnBattle.h"
#include "Utility.h"
#include <stdio.h>  // printf()

// 関数プロトタイプ
static void execCommand(TurnBattle* btl, Command cmd, Character* offense, Character* defense);

// ターンバトル設定
void SetTurnBattle(TurnBattle* btl, Character* player, Character* enemy)
{
	btl->player = player;
	btl->enemy = enemy;
}
// イントロ「～が現れた!!」表示
void IntroTurnBattle(TurnBattle* btl)
{
	DrawBattleScreen(btl);
	printf("%sが　あらわれた!!\n", GetName(btl->enemy));
	WaitKey();
}
// バトル開始
void StartTurnBattle(TurnBattle* btl)
{
	btl->turn = 1;
	StartCharacter(btl->player);
	StartCharacter(btl->enemy);
}
// バトル画面を描画
void DrawBattleScreen(TurnBattle* btl)
{
	ClearScreen();
	IndicatePlayer(btl->player);
	putchar('\n');
	IndicateEnemy(btl->enemy);
	putchar('\n');
}
// プレーヤのターン実行
bool ExecPlayerTurn(TurnBattle* btl, Command cmd)
{
	execCommand(btl, cmd, btl->player, btl->enemy);
	if (IsDeadCharacter(btl->enemy)) {
		SetEraseAa(btl->enemy);
		DrawBattleScreen(btl);
		printf("%sを　たおした!\n", GetName(btl->enemy));
		WaitKey();
		return true;
	}
	return IsEscapeCharacter(btl->player);
}
// 敵のターン実行
bool ExecEnemyTurn(TurnBattle* btl, Command cmd)
{
	execCommand(btl, cmd, btl->enemy, btl->player);
	if (IsDeadCharacter(btl->player)) {
		DrawBattleScreen(btl);
		printf("あなたは　しにました\n");
		WaitKey();
		return true;
	}
	return false;
}
// コマンド実行(offense:攻撃キャラ defense:防御キャラ)
static void execCommand(TurnBattle* btl, Command cmd, Character* offense, Character* defense)
{
	int dmg;
	switch (cmd) {
	case COMMAND_FIGHT:
		DrawBattleScreen(btl);
		printf("%sの　こうげき!\n", GetName(offense));
		WaitKey();

		dmg = CalcDamage(offense);
		DamageCharacter(defense, dmg);
		DrawBattleScreen(btl);
		printf("%sに %dの　ダメージ!\n", GetName(defense), dmg);
		WaitKey();

		break;
	case COMMAND_SPELL:
		if (CanSpellCharacter(offense) == false) {
			DrawBattleScreen(btl);
			printf("ＭＰが　たりない!\n");
			WaitKey();
			break;
		}
		UseSpellCharacter(offense);
		DrawBattleScreen(btl);
		printf("%sは　ヒールを　となえた!\n", GetName(offense));
		WaitKey();

		RecoverCharacter(offense);
		DrawBattleScreen(btl);
		printf("%sのきずが　かいふくした!\n", GetName(offense));
		WaitKey();
		break;

	case COMMAND_ESCAPE:
		DrawBattleScreen(btl);
		printf("%sは　にげだした!\n", GetName(offense));
		WaitKey();
		SetEscapeCharacter(offense);
		break;
	}
}
// 次のターンへ
void NextTurnBattle(TurnBattle* btl)
{
	btl->turn++;
}