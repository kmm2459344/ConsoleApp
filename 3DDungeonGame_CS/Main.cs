//======================================
//      疑似3Dダンジョン　メイン
//======================================
using System;  // ConsoleKey
using Utility = GP2.Utility;

namespace _3DDungeonGame_CS
{
    internal class _3DDungeonGameMain
    {
        static int Main()
        {
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
            Stage stage = new Stage();

            while (true)
            {
                Utility.ClearScreen();
                stage.Draw3D();
                stage.DrawMap();
                UI.DrawOperation(stage);
                Utility.PrintOut();
                // プレーユ移動
                bool isEsc = UI.MovePlayer(stage);
                if (isEsc)
                {
                    break;
                }
                if (stage.IsGoalPlayer())
                {
                    DrawEnding();
                    Utility.WaitKey();
                    break;
                }
            }
        }
        static void DrawEnding()
        {
            Utility.ClearScreen();
            Utility.Printf(
            "　＊　＊　ＣＯＮＧＲＡＴＵＬＡＴＩＯＮＳ　＊　＊\n" +
            "\n" +
            "　あなたはついに　でんせつのまよけを　てにいれた！\n" +
            "\n" +
            "　しかし、くらくをともにした　「なかま」という\n" +
            "かけがえのない　たからをてにした　あなたにとって、\n" +
            "まよけのかがやきも　いろあせて　みえるのであった…\n" +
            "\n" +
            "　　　　　　　～　ＴＨＥ　ＥＮＤ　～\n" +
            "\n");
            Utility.PrintOut();
        }
    } // class
} // namespace 