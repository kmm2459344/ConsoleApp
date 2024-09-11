//======================================
//	ターン制バトル メイン
//======================================
#include "Stage.h"
#include "Map.h"
#include "Character.h"
#include "Utility.h"  // InitRand(),GetKey()
#include <stdio.h>  // printf()
// 関数プロトタイプ
static void game();
static void TalkToKing(Stage* stage);
static void TalkToPrincess(Stage* stage);
static void TalkToBoss(Stage* stage);
static void RevivePlayer(Stage* stage);
static void DrawEnding();

int main()
{
	InitRand();

	int c;
	do {
		game();
		printf("もう一度(y/n)?");
		while (true) {
			c = GetKey();
			if (c == 'y' || c == 'n') {
				break;
			}
		}
	} while (c == 'y');

	return 0;
}

static void game()
{
	Stage stage[1];
	Character player[1];
	Character boss[1];
	Character zako[1];

	SetCharacter(player,
		100,        // HP
		15,         // MP
		30,         // 攻撃力
		"ゆうしゃ", // 名前
		"");        // アスキーアート
	SetCharacter(boss,
		255,      // HP
		0,        // MP
		50,       // 攻撃力
		"まおう", // 名前
		"　　Ａ＠Ａ\n" // アスキーアート
		"ψ（▼皿▼）ψ"
	);
	SetCharacter(zako,
		3,          // HP
		0,          // MP
		2,          // 攻撃力
		"スライム", // 名前 
		"／・Д・＼\n" // アスキーアート
		"～～～～～"
	);

	InitializeStage(stage, player, boss);
	RegistZako(stage, zako);
	ChangeStartMap(stage);

	while (true) {
		MapSpec* spec = GetMapSpec(stage);
		DrawMap(stage);

		int playerX = GetPlayerX(stage);
		int playerY = GetPlayerY(stage);
		switch (GetKey()) {
		case ARROW_UP:    playerY--; break;
		case ARROW_DOWN:  playerY++; break;
		case ARROW_LEFT:  playerX--; break;
		case ARROW_RIGHT: playerX++; break;
		}

		char c = GetMapData(spec, playerX, playerY);
		switch (c) {
		case outOfMap:
			ChangeMap(stage, &spec->nextMap_Out);
			break;
		case 'K':  // 王様の城
			ChangeMap(stage, &spec->nextMap_K);
			break;
		case 'B':  // 魔王の城
			ChangeMap(stage, &spec->nextMap_B);
			break;
		case '0':  // 王
			TalkToKing(stage);
			break;
		case '1':  // 姫
			TalkToPrincess(stage);
			break;
		case '2':  // 魔王
			TalkToBoss(stage);
			break;
		case '.':  // 床/平地
		case '#':  // 階段/橋
			SetPlayerPosition(stage, playerX, playerY);
			if (IsBattleEncount(spec)) {
				// ★ここをコーディングしてください。
				// １６分の1の確率でザコ戦闘を行います
			}
			break;
		}
		if (IsPlayerDead(stage)) {
			RevivePlayer(stage);
			continue; // continue while()
		}
		if (IsBossDead(stage)) {
			break;  // exit while()
		}
	}
	DrawEnding();
}
// 王様と話す
static void TalkToKing(Stage* stage)
{
	// ★ここをコーディングしてください。
	// 以下を表示して キーウェイトします
	// "＊「おお　ゆうしゃよ！\n"
	// "ひがしの　まじょうの　まおうを\n"
	// "たおし　せかいを　すくってくれ！\n"
	printf("＊「おお　ゆうしゃよ！\n"
		"ひがしの　まじょうの　まおうを\n"
		"たおし　せかいを　すくってくれ！\n");

	WaitKey();
}
// 姫と話す
static void TalkToPrincess(Stage* stage)
{
	// ★ここをコーディングしてください。
	// 以下を表示して キーウェイトしたのち、プレーヤの全回復を行います
	// "＊「かみに　いのりを　ささげます。\n"
	// "おお　かみよ！\n"
	// "ゆうしゃさまに　しゅくふくを！\n"
	printf("＊「かみに　いのりを　ささげます。\n"
		"おお　かみよ！\n"
		"ゆうしゃさまに　しゅくふくを！\n");

	WaitKey();

	RecoverAllStatus(stage->player);
}
// ボスと話す
static void TalkToBoss(Stage* stage)
{
	// ★ここをコーディングしてください。
	// 以下を表示して キーウェイトしたのち、ボス戦闘を行います
	// "＊「おろかな　にんげんよ！\n"
	// "わが　やぼうを　はばむものは\n"
	// "このよから　けしさってくれる！\n"
	printf("＊「おろかな　にんげんよ！\n"
		 "わが　やぼうを　はばむものは\n"
		 "このよから　けしさってくれる！\n");

	WaitKey();
}
// プレーヤ復活
static void RevivePlayer(Stage* stage)
{
	// ★ここをコーディングしてください。
	// プレーヤの全回復、初期マップへの再エントリーしたのち
	// 以下を表示して、キーウェイトします
	// "＊「おお　ゆうしゃよ！\n"
	// "かみが　そなたを　すくわれた！\n"
	// "ゆうしゃに　えいこう　あれ！\n");
	RecoverAllStatus(stage->player);
	ChangeStartMap(stage);
	DrawMap(stage);
	printf("＊「おお　ゆうしゃよ！\n"
		"かみが　そなたを　すくわれた！\n"
		"ゆうしゃに　えいこう　あれ！\n");

	WaitKey();

}

// エンディング描画
static void DrawEnding()
{
	// ★ここをコーディングしてください。
	// 画面消去して、以下を表示します。キーウェイトします
	// "　まおうは　ほろび　せかいは\n"
	// "めつぼうのききから　すくわれた！\n"
	// "\n"
	// "　おうは　ふれをだし　ゆうしゃを\n"
	// "さがしもとめたが、だれも\n"
	// "みたものは　いなかったという…\n"
	// "\n"
	// "\n"
	// "　　　　ＴＨＥ　ＥＮＤ\n"
	// "\n"
		printf("　まおうは　ほろび　せかいは\n"
			 "めつぼうのききから　すくわれた！\n"
			 "\n"
			 "　おうは　ふれをだし　ゆうしゃを\n"
			 "さがしもとめたが、だれも\n"
			 "みたものは　いなかったという…\n"
			 "\n"
			 "\n"
			 "　　　　ＴＨＥ　ＥＮＤ\n"
			 "\n");

	WaitKey();

}
