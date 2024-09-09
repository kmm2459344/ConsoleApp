//======================================
//	三国志 メイン
//======================================
using Utility = GP2.Utility;
using System;              // ConsoleKey

namespace Sangokushi_CS
{
    internal class SengokuSimulationMain
    {
        static int Main()
        {
            Console.OutputEncoding = System.Text.Encoding.UTF8;
            Utility.InitRand();

            ConsoleKey c;
            do
            {
                game();
                Utility.Printf("もう一度(y/n)?");
                Utility.PrintOut();
                while (true)
                {
                    c = Utility.GetKey();
                    if (c == ConsoleKey.Y || c == ConsoleKey.N)
                    {
                        break;
                    }
                }
            } while (c == ConsoleKey.Y);

            return 0;
        }

        static void game()
        {
            var chro = new Chronology();
            var stage = new Stage(Data.castles, chro, Data.START_YEAR);
            stage.Start();
            CastleId playerCastle = UI.InputPlayerCastle(stage);
            stage.SetPlayerLord(playerCastle);
            DrawIntro(stage, playerCastle);

            while (true)
            {
                // ターンの順番をシャフル
                stage.MakeTurnOrder();
                for (int i = 0; i < stage.castlesSize; i++)
                {
                    // 各城のターン実行
                    stage.ExecTurn(i);
                    // プレーヤの負け?
                    if (stage.IsPlayerLose())
                    {
                        DrawGameOver(stage);
                        goto exit;
                    }
                    // プレーヤの勝ち
                    if (stage.IsPlayerWin())
                    {
                        DrawEnding(stage);
                        goto exit;
                    }
                }
                // 年越し
                stage.NextYear();
            }
        exit:
            /*nothing*/
            ;
        }
        // GameOver を描画
        static void DrawGameOver(Stage stage)
        {
            stage.DrawScreen(DrawMode.GameOver, 0);
            // 年表を表示
            stage.chro.Print();
            Utility.Putchar('\n');
            Utility.Printf("ＧＡＭＥ　ＯＶＥＲ\n");
            Utility.PrintOut();
            Utility.WaitKey();
        }
        // エンディングを描画
        static void DrawEnding(Stage stage)
        {
            stage.DrawScreen(DrawMode.Ending, 0);
            // 年表を表示
            stage.chro.Print();
            int year = stage.year + 3;
            string name1 = stage.GetLordFamilyName(stage.playerLord);
            string name2 = stage.GetLordFirstName(stage.playerLord);
            Utility.Printf("{0}ねん　 {1}（{2}）が　てんかを　とういつした\n", year, name1, name2);
            Utility.Putchar('\n');
            Utility.Printf("ＴＨＥ　ＥＮＤ");
            Utility.PrintOut();
            Utility.WaitKey();
        }
        // イントロ表示
        static void DrawIntro(Stage stage, CastleId playerCastle)
        {
            LordId player = stage.GetCastleOwner(playerCastle);
            Utility.Printf("{0}さま、 {1}から　てんかとういつを\nめざしましょうぞ！\n"
                , stage.GetLordFirstName(player)
                , stage.GetCastleName(playerCastle)
            );
            Utility.PrintOut();
            Utility.WaitKey();
        }
    } // class
} // namespace 