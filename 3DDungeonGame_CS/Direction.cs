//======================================
//      疑似3Dダンジョン　方位
//======================================
using Vector2 = GP2.Vector2;
using System.Diagnostics;  // Debug

namespace _3DDungeonGame_CS
{
    enum Direction
    {
        North,  // 北(前方)
        West,　 // 西(左方)
        South,  // 南(後方)
        East,   // 東(右方)
        Max,
    }

    static partial class Misc
    {
        static Vector2[] dirVector2 = new Vector2[]
        {
            new Vector2( 0,-1), // Dir.North
            new Vector2(-1, 0), // Dir.West
            new Vector2( 0, 1), // Dir.South
            new Vector2( 1, 0), // Dir.East
        };
        // 4方位のベクターを取得
        public static Vector2 GetDirVector2(Direction d)
        {
            int idx = (int)d;
            Debug.Assert(0 <= idx && idx < dirVector2.Length);
            return dirVector2[idx];
        }
        // 方位加算
        public static Direction DirectionAdd(Direction d, int add)
        {
            const int MAX = (int)Direction.Max;
            int tmp = (int)d + add;
            tmp = (tmp + MAX) % MAX;
            return (Direction)tmp;
        }
        // Direction範囲内?
        public static bool IsInDirection(Direction dir)
        {
            return 0 <= dir && dir < Direction.Max;
        }
    } // class
} // namespace