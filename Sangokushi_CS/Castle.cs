//======================================
//	三国志 城
//======================================
using System.Security.Principal;

namespace Sangokushi_CS
{
    enum CastleId
    {
        SHIREI,       // 司隸
        YOSHU,        // 豫州
        KISHU,        // 冀州
        ENSHU,        // 兗州
        JOSHU,        // 徐州
        KEISHU,       // 荊州
        YOUSHU,       // 揚州
        EKISHU,       // 益州
        RYOSHU,       // 涼州
        YUSHU,        // 幽州
        MAX,          // (種類の数)
        NONE = -1,    // リスト終端
    }
    internal class Castle
    {
        string m_name;      // 名前
        LordId m_owner;     // 城主
        int m_troopCount;   // 兵数
        CastleId[] m_connectedList;  // 接続された城のリスト
        int m_curx, m_cury; // 描画位置
        string m_mapName;   // マップ上の名前

        public string name
        {
            get { return m_name; }
        }
        public LordId owner
        {
            get { return m_owner; }
            set { m_owner = value; }
        }
        public CastleId[] connectedList
        {
            get { return m_connectedList; }
        }
        public int troopCount
        {
            get { return m_troopCount; }
            set { m_troopCount = value; }
        }
        public int curx
        {
            get { return m_curx; }
        }
        public int cury
        {
            get { return m_cury; }
        }
        public string mapName
        {
            get { return m_mapName; }
        }

        // コンストラクタ
        public Castle(string name, LordId owenre, CastleId[] connectedList, int curx, int cury, string mapName)
        {
            m_name = name;
            m_owner = owner;
            m_connectedList = connectedList;
            m_curx = curx;
            m_cury = cury;
            m_mapName = mapName;
        }
        // 兵数に加算する
        public void AddTroopCount(int add)
        {
            int value = m_troopCount + add;
            if (value < 0)
            {
                value = 0;
            }
            else if (value > Data.TROOP_MAX)
            {
                value = Data.TROOP_MAX;
            }
            m_troopCount = value;
        }
    } // class
} // namespace