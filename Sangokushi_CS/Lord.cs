//======================================
//	三国志 城主
//======================================

namespace Sangokushi_CS
{
    enum LordId
    {
        RIKAKU,    // 李傕
        RYUBI,     // 劉備
        ENSHO,     // 袁紹
        SOSO,      // 曹操
        RYOFU,     // 呂布
        RYUHYO,    // 劉表
        SONSAKU,   // 孫策
        RYUSHO,    // 劉璋
        BATO,      // 馬騰
        KOSONSAN,  // 公孫瓚
        MAX,       // (種類の数)
        NONE = -1,
    }

    struct LordName
    {
        string m_familyName;  // 姓
        string m_firstName;   // 名
        string m_mapName;     // マップ上の名前

        // コンストラクタ
        public LordName(string familyName, string firstName, string mapName)
        {
            m_familyName = familyName;
            m_firstName = firstName;
            m_mapName = mapName;
        }
        // プロパティ
        public string familyName
        {
            get { return m_familyName; }
        }
        public string firstName
        {
            get { return m_firstName; }
        }
        public string mapName
        {
            get { return m_mapName; }
        }
    }

    static class Lord
    {
        // 城主の名を取得
        public static string GetFirstName(LordId id)
        {
            int idx = (int)id;
            if (0 <= idx && idx < Data.lordNames.Length)
            {
                return Data.lordNames[idx].firstName;
            }
            return "??";
        }
        // 城主の姓を取得
        public static string GetFamilyName(LordId id)
        {
            int idx = (int)id;
            if (0 <= idx && idx < Data.lordNames.Length)
            {
                return Data.lordNames[idx].familyName;
            }
            return "??";
        }
        // 城主のマップ上の名前を取得
        public static string GetMapName(LordId id)
        {
            int idx = (int)id;
            if (0 <= idx && idx < Data.lordNames.Length)
            {
                return Data.lordNames[idx].mapName;
            }
            return "??";
        }
    } // class
} // namespace 