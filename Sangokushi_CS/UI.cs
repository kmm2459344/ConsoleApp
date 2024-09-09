//======================================
//	三国志 UI
//======================================
using System;   // Array,ConsoleKey
using System.Collections.Generic;  // List<T>
using Utility = GP2.Utility;

namespace Sangokushi_CS
{
    enum Command
    {
        Cancel,  // なにもしない
        Attack,  // 攻撃
        Transit, // 移送
    }

    internal static class UI
    {
        // プレーヤの城を入力する
        public static CastleId InputPlayerCastle(Stage stage)
        {
            stage.DrawScreen(DrawMode.Intro, 0);
            Utility.Printf("わがきみ、われらがしろは　このちずの\n" +
                "どこに　ありまするか？！（0～{0}）\n", stage.castlesSize - 1);
            Utility.Putchar('\n');
            Utility.PrintOut();

            int num = GetKeyInRange(0, stage.castlesSize - 1);
            return (CastleId)num;
        }
        // プレーヤターンの挙動を入力する
        public static Command InputPlayerTurn(Stage stage, Castle castle, out CastleId targetCastle, out int sendTroopCount)
        {
            CastleId _targetCastle = CastleId.NONE;
            int _sendTroopCount = 0;
            Command cmd = Command.Cancel;
            const ConsoleKey CANCEL_KEY = ConsoleKey.X;
            const string CANCEL_STR = "x";

            List<ConsoleKey> list = new List<ConsoleKey>();
            //
            // 進軍先を入力
            //
            Utility.Printf("{0}さま、どこに　しんぐん　しますか？\n", stage.GetLordFirstName(stage.playerLord));
            Utility.Putchar('\n');

            CastleId[] connectedList = castle.connectedList;
            for (int i = 0; i < connectedList.Length; i++)
            {
                CastleId id = connectedList[i];
                int digit = (int)id;
                string opt = (stage.GetCastleOwner(id) == stage.playerLord) ? "移送" : "攻撃";
                Utility.Printf("{0} {1} ({2})\n", digit, stage.GetCastleName(id), opt);
                list.AddRange(getDigitKey(digit));
            }
            Utility.Printf("{0} しんぐんしない\n", CANCEL_STR);
            list.Add(CANCEL_KEY);
            Utility.Putchar('\n');
            Utility.PrintOut();

            ConsoleKey c = GetKeyInList(list);
            if (c != CANCEL_KEY)
            {
                _targetCastle = (CastleId)getDigit(c);
                cmd = Command.Attack;
                int troopMax = castle.troopCount;
                if (stage.GetCastleOwner(_targetCastle) == stage.playerLord)
                {
                    int targetCapacity = Data.TROOP_MAX - stage.GetCastleTroopCount(_targetCastle);
                    if (troopMax > targetCapacity)
                    {
                        troopMax = targetCapacity;
                    }
                    cmd = Command.Transit;
                }
                Utility.Printf("{0}に　なんまんにん　しんぐん　しますか？（0～{1}）\n"
                    , stage.GetCastleName(_targetCastle)    // 進軍先の城の名前
                    , troopMax);                        // 進軍兵数
                Utility.Putchar('\n');
                Utility.PrintOut();
                _sendTroopCount = GetKeyInRange(0, troopMax);
            }
            targetCastle = _targetCastle;
            sendTroopCount = _sendTroopCount;
            return cmd;
        }

        static int GetKeyInRange(int min, int max)
        {
            ConsoleKey c;
            int num;
            do
            {
                c = Utility.GetKey();
                num = getDigit(c);
                //Console.WriteLine("Key:" + c + " num;" + num + "\n");
            } while (num < min || max < num);
            return num;
        }
        static ConsoleKey GetKeyInList(List<ConsoleKey> list)
        {
            ConsoleKey c;
            do
            {
                c = Utility.GetKey();
            } while (list.Contains(c) == false);
            return c;
        }

        static ConsoleKey[] s_digitKeys1 = new ConsoleKey[10]
        {
            ConsoleKey.D0,
            ConsoleKey.D1,
            ConsoleKey.D2,
            ConsoleKey.D3,
            ConsoleKey.D4,
            ConsoleKey.D5,
            ConsoleKey.D6,
            ConsoleKey.D7,
            ConsoleKey.D8,
            ConsoleKey.D9,
        };
        static ConsoleKey[] s_digitKeys2 = new ConsoleKey[10]
        {
            ConsoleKey.NumPad0,
            ConsoleKey.NumPad1,
            ConsoleKey.NumPad2,
            ConsoleKey.NumPad3,
            ConsoleKey.NumPad4,
            ConsoleKey.NumPad5,
            ConsoleKey.NumPad6,
            ConsoleKey.NumPad7,
            ConsoleKey.NumPad8,
            ConsoleKey.NumPad9,
        };

        static ConsoleKey[] getDigitKey(int digit)
        {
            var ret = new ConsoleKey[2] {
                s_digitKeys1[digit],
                s_digitKeys2[digit],
            };
            return ret;
        }
        static int getDigit(ConsoleKey c)
        {
            int idx = Array.IndexOf(s_digitKeys1, c);
            if (idx < 0)
            {
                idx = Array.IndexOf(s_digitKeys2, c);
            }
            return idx;
        }
    } // class
} // namespace