//======================================
//	戦国シミュレーション メイン
//======================================
#include "Stage.h"
#include "Lord.h"
#include "UI.h"
#include "Utility.h"
#include "Chronology.h"
#include <stdio.h>   // printf(),putchar()
#include <stdlib.h>
// 関数プロトタイプ
static void game();
static void DrawGameOver(Stage* stage);
static void DrawEnding(Stage* stage);

int main()
{
    system("chcp 65001");// [6-5-0]コンソールの文字セットをUTF-8に設定する
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

const int CHRONOLOGY_BUFF_SIZE = 1024;
const int START_YEAR = 196;
extern Castle castles[];

static void game()
{
    Stage stage[1];
    Chronology chro[1];
    InitializeChronology(chro, CHRONOLOGY_BUFF_SIZE);
    InitializeStage(stage, castles, CASTLE_MAX, START_YEAR, chro);

    StartStage(stage);
    CastleId playerCastle = InputPlayerCastle(stage);
    SetPlayerLord(stage, playerCastle);
    IntroStage(stage, playerCastle);

    while (true) {
        // ターンの順番をシャフル
        MakeTurnOrder(stage);
        for (int i = 0; i < stage->castlesSize; i++) {
            // 各城のターン実行
            ExecTurn(stage, i);
            // プレーヤの負け?
            if (IsPlayerLose(stage)) {
                DrawGameOver(stage);
                goto exit;
            }
            // プレーヤの勝ち
            if (IsPlayerWin(stage)) {
                DrawEnding(stage);
                goto exit;
            }
        }
        // 年越し
        NextYear(stage);
    }
exit:
    FinalizeStage(stage);
    FinalizeChronology(chro);
}


static void DrawGameOver(Stage* stage)
{
    DrawScreen(stage, DM_GameOver, 0);
    // 年表を表示
    PrintChronology(stage->chro);
    putchar('\n');
    printf("ＧＡＭＥ　ＯＶＥＲ\n");
    WaitKey();
}

static void DrawEnding(Stage* stage)
{
    DrawScreen(stage, DM_Ending, 0);
    // 年表を表示
    PrintChronology(stage->chro);
    int year = stage->year + 3;
    const char* name1 = GetLordFamilyName(stage, stage->playerLord);
    const char* name2 = GetLordFirstName(stage, stage->playerLord);
    printf("%dねん　 %s（%s）が　てんかを　とういつする\n", year, name1, name2);
    putchar('\n');
    printf("ＴＨＥ　ＥＮＤ");
    WaitKey();
}