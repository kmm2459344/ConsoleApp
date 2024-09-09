//======================================
//	戦国シミュレーション  ステージ
//======================================
#include "Stage.h"
#include "Lord.h"
#include "Castle.h"
#include "Utility.h"
#include "Troop.h"
#include "UI.h"
#include "AI.h"
#include <stdio.h>  // printf(),putchar()
#include <stdlib.h> // calloc(),free(),exit()
#include <assert.h> // assert()
// 関数プロトタイプ
static void printTurnOrder(Stage* stage, int turn);
static void ExecPlayerTurn(Stage* stage, CastleId currentCastle, Command cmd, CastleId targetCastle, int sendTroopCount);
static void ExecNpcTurn(Stage* stage, CastleId currentCastle, Command cmd, CastleId targetCastle, int sendTroopCount);
static void TransitTroop(Stage* stage, Castle* castle, CastleId targetCastle, int sendTroopCount);
static void AttackTroop(Stage* stage, Castle* castle, CastleId targetCastle, int sendTroopCount);
static void SiegeBattle(Stage* stage, LordId offenseLord, int offenseTroopCount, CastleId defenseCastle);
static int getCastleCount(Stage* stage, LordId lord);
static Castle* GetCastle(Stage* stage, CastleId id);
static LordId changeLordId(Stage* stage, LordId id);

// 初期化
void InitializeStage(Stage* stage, Castle castles[], int castlesSize, int startYear, Chronology* chro)
{
	stage->year = startYear;
	stage->chro = chro;
	stage->castles = (Castle*)calloc(castlesSize, sizeof(Castle));
	if (stage->castles == nullptr) {
		printf("calloc失敗");
		exit(1);
	}
	for (int i = 0; i < castlesSize; i++) {
		stage->castles[i] = castles[i];  // コピー
	}
	stage->castlesSize = castlesSize;
	stage->playerLord = LORD_NONE;
	stage->isHonnojiEvent = false;
}
// 後始末
void FinalizeStage(Stage* stage)
{
	free(stage->castles);
	stage->castles = nullptr;
}
// スタート
void StartStage(Stage* stage)
{
	for (int i = 0; i < stage->castlesSize; i++) {
		SetCastleOwner(stage, (CastleId)i, (LordId)i);
		SetCastleTroopCount(stage, (CastleId)i, TROOP_BASE);
	}
}
// プレーヤ大名のセット
void SetPlayerLord(Stage* stage, CastleId castleId)
{
	stage->playerLord = GetCastleOwner(stage, castleId);
}
// イントロメッセージ
void IntroStage(Stage* stage, CastleId playerCastle)
{
	printf("%sさま、 %sから　てんかとういつを\nめざしましょうぞ！\n"
		, GetLordFirstName(stage, stage->playerLord)
		, GetCastleName(stage, playerCastle)
	);
	WaitKey();
}
// スクリーン描画
void DrawScreen(Stage* stage, DrawMode mode, int turn)
{
	ClearScreen();
	printf("%s",
		//0       1         2         3         4   
		//2345678901234567890123456789012345678901234567890123
		" 196ねん　　　　　　　　　　9幽州5　　　\n"    // 01
		"　　　　　　　　　　　　　　公孫　～　～\n"    // 02
		"8涼州5　　　　　　2冀州5　　　～～～～～\n"    // 03
		"馬騰　　　　　　　袁紹　　～～～～～～～\n"    // 04
		"　　　　　　　　　　　　　　～～　　～～\n"    // 05
		"　　　　　　　　　3兗州5　　　　　～～～\n"    // 06
		"　　　0司隸5　　　曹操　　4徐州5　～～～\n"    // 07
		"　　　李傕　　　　　　　　呂布　～～～～\n"    // 08
		"　　　　　　　　　1豫州5　　　　　～～～\n"    // 09
		"　　　　　　　　　劉備　　　　　　　～～\n"    // 10
		"7益州5　　5荊州5　　　　6揚州5　　　～～\n"    // 11
		"劉璋　　　劉表　　　　　孫策　　　　～～\n"    // 12
		"　　　　　　　　　　　　　　　　　～～～\n"    // 13
		"　　　　　　　　　　　　　　　　　～～～\n"    // 14
		"　　　　　　　　　　　　　　　～～～～～\n"    // 15
		"　　　　　　　　　～～～～～～～～～～～\n"    // 16
	);

	PrintCursor(1, 1); printf("%4dねん", stage->year);
	for (int i = 0; i < stage->castlesSize; i++) {
		Castle* castle = GetCastle(stage, (CastleId)i);
		int curx = GetCastleCurx(castle);
		int cury = GetCastleCury(castle);
		LordId owner = GetCastleOwner(castle);
		int troopCount = GetCastleTroopCount(castle);
		const char* mapName = GetCastleMapName(castle);
		PrintCursor(curx, cury);
		printf("%d%s%d", i, mapName, troopCount);
		PrintCursor(curx, cury + 1);
		printf("%s", GetLordMapName(stage, owner));
	}
	PrintCursor(1, 18);
}
// ターンの順番をシャッフル
void MakeTurnOrder(Stage* stage)
{
	CastleId* turnOrder = stage->turnOrder;
	for (int i = 0; i < stage->castlesSize; i++) {
		turnOrder[i] = (CastleId)i;
	}
	for (int i = 0; i < stage->castlesSize; i++) {
		int j = GetRand(stage->castlesSize);
		// turnOrder[i]とturnOrder[j]をスワップ
		CastleId tmp = turnOrder[i];
		turnOrder[i] = turnOrder[j];
		turnOrder[j] = tmp;
	}
}
// 年越し
void NextYear(Stage* stage)
{
	stage->year++;
	for (int i = 0; i < stage->castlesSize; i++) {
		Castle* castle = GetCastle(stage, (CastleId)i);
		int troopCount = GetCastleTroopCount(castle);
		if (troopCount < TROOP_BASE) {
			// 兵数が BASEより小なら 増員
			AddCastleTroopCount(castle, +1);
		}
		else if (troopCount > TROOP_BASE) {
			// 兵数が BASEより大なら 減員
			AddCastleTroopCount(castle, -1);
		}
	}
}
// ターン実行
void ExecTurn(Stage* stage, int turn)
{
	CastleId currentCastle = stage->turnOrder[turn];
	Castle* castle = GetCastle(stage, currentCastle);
	LordId owner = GetCastleOwner(castle);

	DrawScreen(stage, DM_Turn, turn);
	printTurnOrder(stage, turn);
	printf("%sの　%sの　ひょうじょうちゅう…\n"
		, GetLordFamilyName(owner)
		, GetCastleName(stage, currentCastle)
	);
	putchar('\n');

	CastleId targetCastle;
	int sendTroopCount;
	Command cmd;
	if (owner == stage->playerLord) {
		cmd = InputPlayerTurn(stage, castle, &targetCastle, &sendTroopCount);
		ExecPlayerTurn(stage, currentCastle, cmd, targetCastle, sendTroopCount);
	}
	else {
		cmd = InputNpcTurn(stage, castle, &targetCastle, &sendTroopCount);
		ExecNpcTurn(stage, currentCastle, cmd, targetCastle, sendTroopCount);
	}
}
// プレーヤターンを実行
static void ExecPlayerTurn(Stage* stage, CastleId currentCastle, Command cmd, CastleId targetCastle, int sendTroopCount)
{
	Castle* castle = GetCastle(stage, currentCastle);
	switch (cmd) {
	case CMD_Cancel:
		printf("しんぐんを　とりやめました\n");
		WaitKey();
		break;
	case CMD_Transit:
		TransitTroop(stage, castle, targetCastle, sendTroopCount);
		printf("%sに　%dにん　いどう　しました"
			, GetCastleName(stage, targetCastle)
			, sendTroopCount * TROOP_UNIT
		);
		WaitKey();
		break;

	case CMD_Attack:
		printf("%sに　%dにんで　しゅつじんじゃ～！！\n"
			, GetCastleName(stage, targetCastle)
			, sendTroopCount * TROOP_UNIT
		);
		WaitKey();
		AttackTroop(stage, castle, targetCastle, sendTroopCount);
		break;
	}
}
// NPCターンを実行
static void ExecNpcTurn(Stage* stage, CastleId currentCastle, Command cmd, CastleId targetCastle, int sendTroopCount)
{
	Castle* castle = GetCastle(stage, currentCastle);
	LordId owner = GetCastleOwner(stage, currentCastle);
	switch (cmd) {
	case CMD_Cancel:
		//printf("しんぐんを　とりやめました\n");
		//WaitKey();
		break;
	case CMD_Transit:
		TransitTroop(stage, castle, targetCastle, sendTroopCount);
		printf("%sから　%sに　%dにん　いどう　しました\n"
			, GetCastleName(stage, currentCastle)
			, GetCastleName(stage, targetCastle)
			, sendTroopCount * TROOP_UNIT
		);
		WaitKey();
		break;

	case CMD_Attack:
		printf("%sの　%s（%s）が　%sに　せめこみました！\n"
			, GetCastleName(stage, currentCastle)
			, GetLordFamilyName(stage, owner)
			, GetLordFirstName(stage, owner)
			, GetCastleName(stage, targetCastle)
		);
		WaitKey();
		AttackTroop(stage, castle, targetCastle, sendTroopCount);
		break;
	}
}
// 移送処理
static void TransitTroop(Stage* stage, Castle* castle, CastleId targetCastle, int sendTroopCount)
{
	AddCastleTroopCount(castle, -sendTroopCount);
	Castle* target = GetCastle(stage, targetCastle);
	AddCastleTroopCount(target, sendTroopCount);
}
// 派兵(攻撃)処理
static void AttackTroop(Stage* stage, Castle* castle, CastleId targetCastle, int sendTroopCount)
{
	AddCastleTroopCount(castle, -sendTroopCount);
	LordId offenseLord = GetCastleOwner(castle);
	SiegeBattle(stage, offenseLord, sendTroopCount, targetCastle);
}
// プレーヤの負け?
bool IsPlayerLose(Stage* stage)
{
	// プレーヤの城が無くなったら負け!!
	return getCastleCount(stage, stage->playerLord) == 0;
}
// プレーヤの勝ち?
bool IsPlayerWin(Stage* stage)
{
	// プレーヤの城で埋まったら勝ち
	return getCastleCount(stage, stage->playerLord) == stage->castlesSize;
}
// ターン順番をプリント
static void printTurnOrder(Stage* stage, int turn)
{
	for (int i = 0; i < stage->castlesSize; i++) {
		const char* cur = (i == turn) ? "＞" : "　";
		CastleId id = (CastleId)stage->turnOrder[i];
		printf("%s%s", cur, GetCastleMapName(stage, id));
	}
	putchar('\n');
	putchar('\n');
}
// 包囲戦闘を行う
static void SiegeBattle(Stage* stage, LordId offenseLord, int offenseTroopCount, CastleId defenseCastle)
{
	ClearScreen();
	printf("～ %sの　たたかい～\n", GetCastleName(stage, defenseCastle));
	putchar('\n');
	LordId defenseLord = GetCastleOwner(stage, defenseCastle);
	int defenseTroopCount = GetCastleTroopCount(stage, defenseCastle);

	while (true) {
		printf("%sぐん（%5dにん）　Ｘ　%sぐん（%5dにん）\n"
			, GetLordFamilyName(offenseLord)
			, offenseTroopCount * TROOP_UNIT
			, GetLordFamilyName(defenseLord)
			, defenseTroopCount * TROOP_UNIT
		);
		WaitKey();
		if (offenseTroopCount <= 0 || defenseTroopCount <= 0) {
			break;
		}

		int rnd = GetRand(3);
		if (rnd == 0) {
			defenseTroopCount--;
			SetCastleTroopCount(stage, defenseCastle, defenseTroopCount);
		}
		else {
			offenseTroopCount--;
		}
	}
	putchar('\n');

	if (defenseTroopCount <= 0) {
		// 防御側の負け
		SetCastleOwner(stage, defenseCastle, offenseLord);
		SetCastleTroopCount(stage, defenseCastle, offenseTroopCount);

		printf("%s　らくじょう！！\n"
			, GetCastleName(stage, defenseCastle)
		);
		putchar('\n');

		printf("%sは　 %sの　ものとなります\n"
			, GetCastleName(stage, defenseCastle)
			, GetLordFamilyName(offenseLord)
		);
		WaitKey();

		if (getCastleCount(stage, defenseLord) <= 0) {
			RecordChronology(stage->chro
				, "%dねん　%s（%s）が　%sで　%s（%s）を　ほろぼす\n"
				, stage->year
				, GetLordFamilyName(stage, offenseLord)
				, GetLordFirstName(stage, offenseLord)
				, GetCastleName(stage, defenseCastle)
				, GetLordFamilyName(stage, defenseLord)
				, GetLordFirstName(stage, defenseLord)
			);
		}
	}
	else {
		// 攻撃側の負け
		printf("%sぐん　かいめつ！！\n"
			, GetLordFamilyName(stage, offenseLord)
		);
		putchar('\n');
		printf("%sぐんが　%sを　まもりきりました！\n"
			, GetLordFamilyName(stage, defenseLord)
			, GetCastleName(stage, defenseCastle)
		);
		WaitKey();
	}
}
// 任意のownerの城を数える
static int getCastleCount(Stage* stage, LordId lord)
{
	int castleCount = 0;
	for (int i = 0; i < stage->castlesSize; i++) {
		Castle* castle = GetCastle(stage, (CastleId)i);
		if (castle->owner == lord) {
			castleCount++;
		}
	}
	return castleCount;
}
//---------------------------------------------------------
// 城の名前を得る
const char* GetCastleName(Stage* stage, CastleId id)
{
	Castle* castle = GetCastle(stage, id);
	return GetCastleName(castle);
}
// 城の城主を取得
LordId GetCastleOwner(Stage* stage, CastleId id)
{
	Castle* castle = GetCastle(stage, id);
	return GetCastleOwner(castle);
}
// 城の城主をセット
void SetCastleOwner(Stage* stage, CastleId id, LordId owner)
{
	Castle* castle = GetCastle(stage, id);
	SetCastleOwner(castle, owner);
}
// 兵数を得る
int GetCastleTroopCount(Stage* stage, CastleId id)
{
	Castle* castle = GetCastle(stage, id);
	return GetCastleTroopCount(castle);
}
// 兵数をセット
void SetCastleTroopCount(Stage* stage, CastleId id, int troopCount)
{
	Castle* castle = GetCastle(stage, id);
	SetCastleTroopCount(castle, troopCount);
}
// 城の近隣リストを取得
CastleId* GetCastleConnectedList(Stage* stage, CastleId id)
{
	Castle* castle = GetCastle(stage, id);
	return GetCastleConnectedList(castle);
}
// 城のマップ名を取得
const char* GetCastleMapName(Stage* stage, CastleId id)
{
	Castle* castle = GetCastle(stage, id);
	return GetCastleMapName(castle);
}
// idから Castle* を取得
static Castle* GetCastle(Stage* stage, CastleId id)
{
	assert(0 <= id && id < stage->castlesSize);
	return &stage->castles[id];
}
//--------------------------------------
// 城主の名を取得
const char* GetLordFirstName(Stage* stage, LordId id)
{
	id = changeLordId(stage, id);
	return GetLordFirstName(id);
}
// 城主の姓を取得
const char* GetLordFamilyName(Stage* stage, LordId id)
{
	id = changeLordId(stage, id);
	return GetLordFamilyName(id);
}
// 城主のマップ上の名前を取得
const char* GetLordMapName(Stage* stage, LordId id)
{
	id = changeLordId(stage, id);
	return GetLordMapName(id);
}
// 城主IDの変更
static LordId changeLordId(Stage* stage, LordId id)
{
	return id;
}