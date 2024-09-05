//======================================
//      疑似3Dダンジョン　ロケーション
//======================================
using Vector2 = GP2.Vector2;
using System.Diagnostics;   // Debug

namespace _3DDungeonGame_CS
{
    enum Location
    {
        FrontLeft,  // 左前
        FrontRight, // 右前
        Front,      // 前
        Left,       // 左
        Right,      // 右
        Center,     // 中心
        Max,        // (最大)
    }

    static partial class Misc
    {
        static Vector2[,] locations = new Vector2[,]
        {
            // Direction.North
            {                       //                            x:-1 + 0 + 1
		            new Vector2(-1,-1), // LOC_FRONT_LEFT  左前(A)     +--+--+--+
		            new Vector2( 1,-1), // LOC_FRONT_RIGHT 右前(B)     |Ａ|Ｃ|Ｂ|-1 
		            new Vector2( 0,-1), // LOC_FRONT       前(C)       +--+--+--+
		            new Vector2(-1, 0), // LOC_LEFT        左(D)       |Ｄ|↑|Ｅ|+0
		            new Vector2( 1, 0), // LOC_RIGHT       右(E)       +--+--+--+
		            new Vector2( 0, 0), // LOC_CENTER      中心        |　|　|　|+1
                                        //                             +--+--+--+
            },
            // Direction.West
            	{                       //                            x:-1 + 0 + 1
                    new Vector2(-1, 1), // LOC_FRONT_LEFT  左前(A)     +--+--+--+
                    new Vector2(-1,-1), // LOC_FRONT_RIGHT 右前(B)     |Ｂ|Ｅ|　|-1 
                    new Vector2(-1, 0), // LOC_FRONT       前(C)       +--+--+--+
                    new Vector2( 0,+1), // LOC_LEFT        左(D)       |Ｃ|←|　|+0
                    new Vector2( 0,-1), // LOC_RIGHT       右(E)       +--+--+--+
                    new Vector2( 0, 0), // LOC_CENTER      中心        |Ａ|Ｄ|　|+1
                                        //                             +--+--+--+
	        },
	        // DIR_SOUTH
	        {                           //                            x:-1 + 0 + 1
                    new Vector2( 1, 1), // LOC_FRONT_LEFT  左前(A)     +--+--+--+
                    new Vector2(-1, 1), // LOC_FRONT_RIGHT 右前(B)     |　|　|　|-1 
                    new Vector2( 0, 1), // LOC_FRONT       前(C)       +--+--+--+
                    new Vector2( 1, 0), // LOC_LEFT        左(D)       |Ｅ|↓|Ｄ|+0
                    new Vector2(-1, 0), // LOC_RIGHT       右(E)       +--+--+--+
                    new Vector2( 0, 0), // LOC_CENTER      中心        |Ｂ|Ｃ|Ａ|+1
	                                    //                             +--+--+--+
	        },
	        // DIR_EAST
	        {                          //                            x:-1 + 0 + 1
                    new Vector2(1,-1), // LOC_FRONT_LEFT  左前(A)     +--+--+--+
                    new Vector2(1, 1), // LOC_FRONT_RIGHT 右前(B)     |　|Ｄ|Ａ|-1 
                    new Vector2(1, 0), // LOC_FRONT       前(C)       +--+--+--+
                    new Vector2(0,-1), // LOC_LEFT        左(D)       |　|→|Ｃ|+0
                    new Vector2(0, 1), // LOC_RIGHT       右(E)       +--+--+--+
                    new Vector2(0, 0), // LOC_CENTER      中心        |　|Ｅ|Ｂ|+1
	                                   //                             +--+--+--+
        	},
        };

        // 方向とロケーションからオフセットベクター取得
        public static Vector2 GetLocationVector2(Direction dir, Location loc)
        {
            int idx1 = (int)dir;
            int idx2 = (int)loc;
            Debug.Assert(0 <= idx1 && idx1 < locations.GetLength(0));
            Debug.Assert(0 <= idx2 && idx2 < locations.GetLength(1));
            return locations[idx1, idx2];
        }

        // [5-2]基準となるアスキーアートを宣言する
        // +..+==+..+
        // .  |  |  .
        // +..+..+..+
        // .  |↑|  .
        // +..+..+..+
        const string all =
            "L       /\n" +
            "#L     /#\n" +
            "#|L _ /|#\n" +
            "#|#|#|#|#\n" +
            "#|#|_|#|#\n" +
            "#|/   L|#\n" +
            "#/     L#\n" +
            "/       L\n";

        // [5-3]左前方前の壁のアスキーアートを宣言する
        // +==+..+..+ (この壁を描画)
        // .  .  .  .
        // +..+..+..+
        // .  .↑.  .
        // +..+..+..+
        const string frontLeftNorth =
            "         \n" +
            "         \n" +
            "  _      \n" +
            " |#|     \n" +
            " |_|     \n" +
            "         \n" +
            "         \n" +
            "         \n";

        // [5-4]右前方前の壁のアスキーアートを宣言する
        // +..+..+==+ (この壁を描画)
        // .  .  .  .
        // +..+..+..+
        // .  .↑.  .
        // +..+..+..+
        static string frontRightNorth =
            "         \n" +
            "         \n" +
            "      _  \n" +
            "     |#| \n" +
            "     |_| \n" +
            "         \n" +
            "         \n" +
            "         \n";

        // [5-5]前方前の壁のアスキーアートを宣言する
        // +..+==+..+ (この壁を描画)
        // .  .  .  .
        // +..+..+..+
        // .  .↑.  .
        // +..+..+..+
        static string frontNorth =
            "         \n" +
            "         \n" +
            "    _    \n" +
            "   |#|   \n" +
            "   |_|   \n" +
            "         \n" +
            "         \n" +
            "         \n";

        // [5-6]前方左の壁のアスキーアートを宣言する
        // +..+..+..+ 
        // .  |  .  . (この壁を描画)
        // +..+..+..+
        // .  .↑.  .
        // +..+..+..+
        static string frontWest =
            "         \n" +
            "         \n" +
            " |L      \n" +
            " |#|     \n" +
            " |#|     \n" +
            " |/      \n" +
            "         \n" +
            "         \n";

        // [5-7]前方右の壁のアスキーアートを宣言する
        // +..+..+..+ 
        // .  .  |  . (この壁を描画)
        // +..+..+..+
        // .  .↑.  .
        // +..+..+..+
        static string frontEast =
            "         \n" +
            "         \n" +
            "      /| \n" +
            "     |#| \n" +
            "     |#| \n" +
            "      L| \n" +
            "         \n" +
            "         \n";

        // [5-8]左方前の壁のアスキーアートを宣言する
        // +..+..+..+ 
        // .  .  .  .
        // +==+..+..+ (この壁を描画)
        // .  .↑.  .
        // +..+..+..+
        static string leftNorth =
            "         \n" +
            "_        \n" +
            "#|       \n" +
            "#|       \n" +
            "#|       \n" +
            "_|       \n" +
            "         \n" +
            "         \n";

        // [5-9]右方前の壁のアスキーアートを宣言する
        // +..+..+..+ 
        // .  .  .  .
        // +..+..+==+ (この壁を描画)
        // .  .↑.  .
        // +..+..+..+
        static string rightNorth =
            "         \n" +
            "        _\n" +
            "       |#\n" +
            "       |#\n" +
            "       |#\n" +
            "       |_\n" +
            "         \n" +
            "         \n";

        // [5-10]前の壁のアスキーアートを宣言する
        // +..+..+..+ 
        // .  .  .  .
        // +..+==+..+ (この壁を描画)
        // .  .↑.  .
        // +..+..+..+
        static string north =
            "         \n" +
            "  _____  \n" +
            " |#####| \n" +
            " |#####| \n" +
            " |#####| \n" +
            " |_____| \n" +
            "         \n" +
            "         \n";

        // [5-11]左の壁のアスキーアートを宣言する
        // +..+..+..+ 
        // .  .  .  .
        // +..+..+..+
        // .  |↑.  . (この壁を描画)
        // +..+..+..+
        static string west =
            "L        \n" +
            "#L       \n" +
            "#|       \n" +
            "#|       \n" +
            "#|       \n" +
            "#|       \n" +
            "#/       \n" +
            "/        \n";

        // [5-12]右の壁のアスキーアートを宣言する
        // +..+..+..+ 
        // .  .  .  .
        // +..+..+..+
        // .  .↑|  . (この壁を描画)
        // +..+..+..+
        static string east =
            "        /\n" +
            "       /#\n" +
            "       |#\n" +
            "       |#\n" +
            "       |#\n" +
            "       |#\n" +
            "       L#\n" +
            "        L\n";

        static string[,] aaTable = new string[,]
        {
	        // LOC_FRONT_LEFT 左前
	        {
                frontLeftNorth,  // DIR_NORTH(前方)
		        null,         // DIR_WEST (左方)
		        null,         // DIR_SOUTH(後方)
		        null,         // DIR_EAST (右方)
	        },
	        // LOC_FRONT_RIGHT 右前
	        {
                frontRightNorth, // DIR_NORTH(前方)
		        null,         // DIR_WEST (左方)
		        null,         // DIR_SOUTH(後方)
		        null,         // DIR_EAST (右方)
	        },
	        // LOC_FRONT
	        {
                frontNorth,      // DIR_NORTH(前方)
		        frontWest,       // DIR_WEST (左方)
		        null,         // DIR_SOUTH(後方)
		        frontEast,       // DIR_EAST (右方)
	        },
	        // LOC_LEFT
	        {
                leftNorth,       // DIR_NORTH(前方)
		        null,         // DIR_WEST (左方)
		        null,         // DIR_SOUTH(後方)
		        null,         // DIR_EAST (右方)
	        },
	        // LOC_RIGHT
	        {
                rightNorth,      // DIR_NORTH(前方)
		        null,         // DIR_WEST (左方)
		        null,         // DIR_SOUTH(後方)
		        null,         // DIR_EAST (右方)
	        },
	        // LOC_CENTER
	        {
                north,          // DIR_NORTH(前方)
		        west,           // DIR_WEST (左方)
		        null,        // DIR_SOUTH(後方)
		        east,           // DIR_EAST (右方)
	        },
        };

        public static string GetLocationAA(Location loc, Direction dir)
        {
            int idx1 = (int)loc;
            int idx2 = (int)dir;
            Debug.Assert(0 <= idx1 && idx1 < aaTable.GetLength(0));
            Debug.Assert(0 <= idx2 && idx2 < aaTable.GetLength(1));
            return aaTable[idx1, idx2];
        }
    } // class
} // namespace