//======================================
//      ユーティリティ
//======================================
using System.Text; // StringBuilder

namespace GP2
{
    static class Utility
    {
        public const string EscBLACK = "\x1b[30m";
        public const string EscRED = "\x1b[31m";
        public const string EscGREEN = "\x1b[32m";
        public const string EscYELLOW = "\x1b[33m";
        public const string EscBLUE = "\x1b[34m";
        public const string EscMAZENTA = "\x1b[35m";
        public const string EscCYAN = "\x1b[36m";
        public const string EscWHITE = "\x1b[37m";
        public const string EscDEFAULT = "\x1b[39m";

        public const string EscBgBLACK = "\x1b[40m";
        public const string EscBgRED = "\x1b[41m";
        public const string EscBgGREEN = "\x1b[42m";
        public const string EscBgYELLOW = "\x1b[43m";
        public const string EscBgBLUE = "\x1b[44m";
        public const string EscBgMAZENTA = "\x1b[45m";
        public const string EscBgCYAN = "\x1b[46m";
        public const string EscBgWHITE = "\x1b[47m";
        public const string EscBgDEFAULT = "\x1b[49m";

        private static Random s_rand = new Random();
        // 乱数初期化
        public static void InitRand()
        {
            //s_rand = new Random();
        }
        // 乱数取得
        public static int GetRand(int max)
        {
            return s_rand.Next(max);
        }
        // キー入力待ち
        public static void WaitKey()
        {
            Console.ReadKey(true);
        }
        // キー取得
        //  ConsoleKey.UpArrow    カーソル上
        //  ConsoleKey.DownArrow  カーソル下
        //  ConsoleKey.LeftArrow  カーソル左
        //  ConsoleKey.RightArrow カーソル右
        //  ConsoleKey.Return     リターンキー
        //  ConsoleKey.Escape     ESCキー
        //  ConsoleKey.Spacebar   スペースキー
        public static ConsoleKey GetKey()
        {
            ConsoleKeyInfo info = Console.ReadKey(true);
            return info.Key;
        }
        // キーが押されたか?
        public static bool KeyAvailable()
        {
            return Console.KeyAvailable;
        }

        static StringBuilder s_console = new StringBuilder();
        //--------------------------------------
        //      コンソール出力
        //--------------------------------------
        // 使い方 : StringBuilderにため込んで PrintOut()で実際の描画を行う
        //    Utility.ClearScreen();
        //    Utilitu.Printf(....);
        //    Utility.Putchar(.);
        //    ....
        //    Utility.PrintOut();
        //--------------------------------------
        // 画面クリア
        public static void ClearScreen()
        {
            s_console.Clear();
        }
        // printf()関数
        public static void Printf(string fmt, params Object[] list)
        {
            s_console.AppendFormat(fmt, list);
        }
        // putchar()関数
        public static void Putchar(Char c)
        {
            s_console.Append(c);
        }
        // プリント出力
        public static void PrintOut()
        {
            Console.Clear();
            Console.Write(s_console.ToString());
        }
        // m秒スリープ
        public static void Sleep_mSec(int mSec)
        {
            System.Threading.Thread.Sleep(mSec);
        }
    } // class Utility
} // namespace