//======================================
//      疑似3Dダンジョン　ステージ
//======================================
using Vector2 = GP2.Vector2;
using Utility = GP2.Utility;
using System.Collections.Generic;   // List<T>
using System.Diagnostics;   // Debug
using System; // Console

namespace _3DDungeonGame_CS
{
    internal class Stage
    {
        const int MAZE_WIDTH = 8;
        const int MAZE_HEIGHT = 8;
        const int GOAL_X = MAZE_WIDTH - 1;
        const int GOAL_Y = MAZE_HEIGHT - 1;

        static char[] FloorPlayer = new char[]
        {
            '↑',  // North
            '←',  // West
            '↓',  // South
            '→',  // East
        };

        struct TILE
        {
            private bool[] m_walls;
            // コンストラクター
            public TILE()
            {
                m_walls = new bool[(int)Direction.Max];
            }
            // プロパティ
            public bool[] walls
            {
                get { return m_walls; }
            }
            // リセット
            public void Reset()
            {
                for (int i = 0; i < m_walls.Length; i++)
                {
                    m_walls[i] = true;
                }
            }
        }

        TILE[,] m_maze;   // マップ
        Character m_player; // プレーヤの位置と向き
        Vector2 m_goal;   // ゴールの位置
        bool m_isForMap;  // UI forMap or for3D

        // プロパティ
        public bool isForMap
        {
            get { return m_isForMap; }
            set { m_isForMap = value; }
        }
        // プロパティ
        public Character player
        {
            get { return m_player; }
        }

        // コンストラクター
        public Stage()
        {
            m_maze = new TILE[MAZE_HEIGHT, MAZE_WIDTH];
            for (int y = 0; y < MAZE_HEIGHT; y++)
            {
                for (int x = 0; x < MAZE_WIDTH; x++)
                {
                    m_maze[y, x] = new TILE();
                }
            }
            m_player = new Character(new Vector2(0, 0), Direction.North);
            m_goal = new Vector2(GOAL_X, GOAL_Y);
            m_isForMap = false;
            GenerateMap();
        }

        // 迷路マップ描画
        public void DrawMap()
        {
            Vector2 pos = new Vector2(0, 0);
            for (int y = 0; y < MAZE_HEIGHT; y++)
            {
                DrawMap_HorizontalWall(y, Direction.North);
                pos.y = y;
                for (int x = 0; x < MAZE_WIDTH; x++)
                {
                    pos.x = x;
                    char floor = '　';
                    if (pos == m_player.pos)
                    {
                        floor = FloorPlayer[(int)m_player.dir];
                    }
                    else if (pos == m_goal)
                    {
                        floor = 'Ｇ';
                    }
                    char west = GetMazeWall(pos, Direction.West) ? '|' : ' ';
                    char east = GetMazeWall(pos, Direction.East) ? '|' : ' ';
                    Utility.Printf("{0}{1}{2}", west, floor, east);
                }
                Utility.Putchar('\n');
                DrawMap_HorizontalWall(y, Direction.South);
            }
        }
        // 北、南の壁を表示
        protected void DrawMap_HorizontalWall(int y, Direction dir)
        {
            Vector2 pos = new Vector2(0, y);
            for (int x = 0; x < MAZE_WIDTH; x++)
            {
                pos.x = x;
                char wall = GetMazeWall(pos, dir) ? '―' : '　';
                Utility.Printf("+{0}+", wall);
            }
            Utility.Putchar('\n');
        }
        // 3D描画
        public void Draw3D()
        {
            string _screen =
                "         \n" +
                "         \n" +
                "         \n" +
                "         \n" +
                "         \n" +
                "         \n" +
                "         \n" +
                "         \n";
            char[] screen = _screen.ToCharArray();

            // 
            //  プレーヤの周囲(A～E)について
            //	+--+--+--+
            //  |Ａ|Ｃ|Ｂ|
            //  +--+--+--+
            //  |Ｄ|↑|Ｅ|
            //  +--+--+--+
            for (int i = 0; i < (int)Location.Max; i++)
            {
                Vector2 loc = Misc.GetLocationVector2(m_player.dir, (Location)i);
                Vector2 pos = m_player.pos + loc;
                if (IsInsideMaze(pos) == false)
                {
                    continue;
                }

                for (int j = 0; j < (int)Direction.Max; j++)
                {
                    // プレーヤから見た方向
                    // ↑←↓→(0,1,2,3) をプレーヤ↑(0)　から見ると ↑←↓→(0,1,2,3)
                    // ↑←↓→(0,1,2,3) をプレーヤ←(1)　から見ると →↑←↓(3,0,1,2)
                    // ↑←↓→(0,1,2,3) をプレーヤ↓(2)　から見ると ↓→↑←(2,3,0,1) 
                    // ↑←↓→(0,1,2,3) をプレーヤ→(3)　から見ると ←↓→↑(1,2,3,0)
                    const int dirMax = (int)Direction.Max;
                    Direction dir = (Direction)((dirMax + j - (int)player.dir) % dirMax);

                    if (GetMazeWall(pos, (Direction)j) == false)
                    {
                        continue;
                    }
                    string aa = Misc.GetLocationAA((Location)i, dir);
                    if (aa == null)
                    {
                        continue;
                    }
                    // screenにコピー
                    for (int k = 0; k < screen.Length; k++)
                    {
                        char c = aa[k];
                        if (c != ' ')
                        {
                            screen[k] = c;
                        }
                    }
                }
            }
            //
            // screen[]を描画
            //
            for (int i = 0; i < screen.Length; i++)
            {
                char c = screen[i];
                switch (c)
                {
                    case ' ': Utility.Putchar('　'); break;
                    case '#': Utility.Putchar('　'); break;
                    case '_': Utility.Putchar('＿'); break;
                    case '|': Utility.Putchar('｜'); break;
                    case '/': Utility.Putchar('／'); break;
                    case 'L': Utility.Putchar('＼'); break;
                    case '\n':
                        Utility.Putchar(c);
                        break;
                    default:
                        Console.Write(string.Format("{0:X}\n", (int)c));
                        Debug.Assert(false);
                        break;
                }
            }
        }
        // プレーヤがゴールしたか?
        public bool IsGoalPlayer()
        {
            return m_player.pos == m_goal;
        }
        protected void SetMazeWall(Vector2 pos, Direction dir, bool value)
        {
            if (IsInsideMaze(pos) && Misc.IsInDirection(dir))
            {
                m_maze[pos.y, pos.x].walls[(int)dir] = value;
            }
        }
        public bool GetMazeWall(Vector2 pos, Direction dir)
        {
            if (IsInsideMaze(pos) && Misc.IsInDirection(dir))
            {
                return m_maze[pos.y, pos.x].walls[(int)dir];
            }
            return true;
        }
        // 座標がMaze内か?
        public bool IsInsideMaze(Vector2 pos)
        {
            return 0 <= pos.x && pos.x < MAZE_WIDTH
                && 0 <= pos.y && pos.y < MAZE_HEIGHT;
        }
        // マップ生成
        protected void GenerateMap()
        {
            ResetMap();

            Vector2 curPos = new Vector2(0, 0);
            List<Vector2> toDigWallPos = new List<Vector2>();
            List<int> canDigDirection = new List<int>();
            toDigWallPos.Add(curPos);

            while (true)
            {
                // curPosの掘れる向きをリスト
                canDigDirection.Clear();
                for (int d = 0; d < (int)Direction.Max; d++)
                {
                    if (CanDigWall(curPos, (Direction)d))
                    {
                        canDigDirection.Add(d);
                    }
                }
                int count = canDigDirection.Count;
                if (count > 0)
                {
                    // リストからランダムに選んで掘る
                    int idx = Utility.GetRand(count);
                    Direction digDirection = (Direction)canDigDirection[idx];
                    DigWall(curPos, digDirection);
                    // 掘った向きに進む
                    Vector2 digVec = Misc.GetDirVector2(digDirection);
                    curPos += digVec;
                    toDigWallPos.Add(curPos);
                }
                else
                {
                    toDigWallPos.RemoveAt(0);
                    // 掘れる向きが無いとき
                    if (toDigWallPos.Count == 0)
                    {
                        break;
                    }
                    curPos = toDigWallPos[0];
                }
            }
        }
        // マップをリセット(全部の壁をonにする)
        protected void ResetMap()
        {
            for (int y = 0; y < MAZE_HEIGHT; y++)
            {
                for (int x = 0; x < MAZE_WIDTH; x++)
                {
                    m_maze[y, x].Reset();
                }
            }
        }
        // 指定座標の指定向きは掘れるか?
        protected bool CanDigWall(Vector2 pos, Direction dir)
        {
            Vector2 dirVector2 = Misc.GetDirVector2(dir);
            Vector2 nextPos = pos + dirVector2;
            if (IsInsideMaze(nextPos) == false)
            {
                return false;
            }
            // 既に掘られていたらNG
            for (int d = 0; d < (int)Direction.Max; d++)
            {
                if (GetMazeWall(nextPos, (Direction)d) == false)
                {
                    return false;
                }
            }
            return true;
        }
        // 壁を掘る
        protected void DigWall(Vector2 pos, Direction dir)
        {
            // mazeの外ならなにもしない
            if (IsInsideMaze(pos) == false)
            {
                return;
            }
            // posのdirの壁を取り払う
            SetMazeWall(pos, dir, false);

            Vector2 dirVector2 = Misc.GetDirVector2(dir);
            Vector2 newPos = pos + dirVector2;
            if (IsInsideMaze(newPos))
            {
                // 北←→南、西←→東
                Direction dir2 = Misc.DirectionAdd(dir, 2);
                // newPosのdir2の壁を取り払う
                SetMazeWall(newPos, dir2, false);
            }
        }
    } // class
} // namespace 