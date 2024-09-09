//======================================
//	戦国シミュレーション  UI
//======================================
#include "UI.h"
#include "Stage.h"
#include "Castle.h"
#include "Lord.h"
#include "Utility.h"
#include "Troop.h"
#include <stdio.h>
#include <string.h> // strchr()
// 関数プロトタイプ
static int getKeyInRange(int min, int max);
static char getKeyInList(const char* list);

// プレーヤIDを入力する
CastleId InputPlayerCastle(Stage* stage)
{
	DrawScreen(stage, DM_Intro, 0);
	printf("わがきみ、われらがしろは　このちずの\n"
		"どこに　ありまするか？！（0～%d）\n", stage->castlesSize - 1);
	putchar('\n');

	int num = getKeyInRange(0, stage->castlesSize - 1);
	return (CastleId)num;
}
// プレーヤターンの挙動を入力
Command InputPlayerTurn(Stage* stage, Castle* castle, CastleId* outTarget, int* outTroopCount)
{
	const char CANCEL = 'x';
	char list[CASTLE_MAX + 2];
	char* listp;
	//
	// 進軍先を入力
	//
	printf("%sさま、どこに　しんぐん　しますか？\n", GetLordFirstName(stage, stage->playerLord));
	putchar('\n');

	listp = list;
	CastleId* connectedList = castle->connectedList;
	for (int i = 0; ; i++) {
		CastleId id = connectedList[i];
		if (id == CASTLE_NONE) break;
		const char* opt = (GetCastleOwner(stage, id) == stage->playerLord) ? "移送" : "攻撃";
		printf("%d %s (%s)\n", id, GetCastleName(stage, id), opt);
		*listp++ = id + '0';
	}
	printf("%c しんぐんしない\n", CANCEL);
	*listp++ = CANCEL;
	*listp = '\0';
	putchar('\n');

	char c = getKeyInList(list);
	if (c == CANCEL) {
		return CMD_Cancel;
	}
	//
	// 進軍する兵数を入力
	//
	CastleId targetId = (CastleId)(c - '0');
	Command cmd = CMD_Attack;

	int troopMax = castle->troopCount;
	if (GetCastleOwner(stage, targetId) == stage->playerLord) {
		int targetCapacity = TROOP_MAX - GetCastleTroopCount(stage, targetId);
		if (troopMax > targetCapacity) {
			troopMax = targetCapacity;
		}
		cmd = CMD_Transit;
	}
	printf("%sに　なんまんにん　しんぐん　しますか？（0～%d）\n"
		, GetCastleName(stage, targetId)	// 進軍先の城の名前
		, troopMax);						    // 進軍兵数
	putchar('\n');
	int troopCount = getKeyInRange(0, troopMax);

	*outTarget = targetId;
	*outTroopCount = troopCount;
	return cmd;
}

// min～maxの数字を入力させる
static int getKeyInRange(int min, int max)
{
	unsigned char c;
	int num;
	do {
		c = (unsigned char)GetKey();
		num = c - '0';
	} while (num < min || max < num);
	return num;
}
// listにあるキーを入力させる
static char getKeyInList(const char* list)
{
	char c;
	do {
		c = GetKey();
	} while (strchr(list, c) == nullptr);
	return c;
}