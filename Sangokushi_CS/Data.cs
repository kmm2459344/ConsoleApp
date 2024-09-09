//======================================
//	三国志 データ
//======================================
using Sangokushi_CS;

namespace Sangokushi_CS
{
    static class Data
    {
        public const int START_YEAR = 196;
        public const int TROOP_BASE = 5;
        public const int TROOP_MAX = 9;
        public const int TROOP_UNIT = 10000;

        static string s_map =
        //0       1         2         3         4   
        //2345678901234567890123456789012345678901234567890123
        " 196ねん　　　　　　　　　　9幽州5　　　\n" +   // 01
        "　　　　　　　　　　　　　　公孫　～　～\n" +   // 02
        "8涼州5　　　　　　2冀州5　　　～～～～～\n" +   // 03
        "馬騰　　　　　　　袁紹　　～～～～～～～\n" +   // 04
        "　　　　　　　　　　　　　　～～　　～～\n" +   // 05
        "　　　　　　　　　3兗州5　　　　　～～～\n" +   // 06
        "　　　0司隸5　　　曹操　　4徐州5　～～～\n" +   // 07
        "　　　李傕　　　　　　　　呂布　～～～～\n" +   // 08
        "　　　　　　　　　1豫州5　　　　　～～～\n" +   // 09
        "　　　　　　　　　劉備　　　　　　　～～\n" +   // 10
        "7益州5　　5荊州5　　　　6揚州5　　　～～\n" +   // 11
        "劉璋　　　劉表　　　　　孫策　　　　～～\n" +   // 12
        "　　　　　　　　　　　　　　　　　～～～\n" +   // 13
        "　　　　　　　　　　　　　　　　　～～～\n" +   // 14
        "　　　　　　　　　　　　　　　～～～～～\n" +   // 15
        "　　　　　　　　　～～～～～～～～～～～\n" +   // 16
        "\n";
        // プロパティ
        public static string map
        {
            get { return s_map; }
        }

        static LordName[] s_lordNames = new LordName[]
        {
           new LordName("李傕",      "稚然", "李傕"),   // LORD_RIKAKU    李傕
           new LordName("劉備",      "玄徳", "劉備"),   // LORD_RYUBI     劉備
           new LordName("袁紹",      "本初", "袁紹"),   // LORD_ENSHO     袁紹
           new LordName("曹操",      "孟徳", "曹操"),   // LORD_SOSO      曹操
           new LordName("呂布",      "奉先", "呂布"),   // LORD_RYOFU     呂布
           new LordName("劉表",      "景升", "劉表"),   // LORD_RYUHYO    劉表
           new LordName("孫策",      "伯符", "孫策"),   // LORD_SONSAKU   孫策
           new LordName("劉璋",      "季玉", "劉璋"),   // LORD_RYUSHO    劉璋
           new LordName("馬騰",      "寿成", "馬騰"),   // LORD_BATO      馬騰
           new LordName("公孫",      "伯珪", "公孫"),   // LORD_KOSONSAN  公孫
        };
        // プロパティ
        public static LordName[] lordNames
        {
            get { return s_lordNames; }
        }

        static Castle[] s_castles = new Castle[]
        {
            new Castle(
                "司隸",   // 名前
		        LordId.RIKAKU,  // 城主
		        // 接続された城のリスト
		        new CastleId[]{
                    CastleId.YOSHU,   // 豫州
			        CastleId.KISHU,   // 冀州
			        CastleId.ENSHU,   // 兗州
			        CastleId.KEISHU,  // 荊州
			        CastleId.EKISHU,  // 益州
			        CastleId.RYOSHU,  // 涼州
                },
                 7, 7,      // 描画位置
		        "司隸"     // マップ上の名前
                ),
            new Castle(
                "豫州",     // 名前
		        LordId.RYUBI,    // 城主
		        // 接続された城のリスト
		        new CastleId[]{
                    CastleId.SHIREI,  // 司隸 
			        CastleId.ENSHU,   // 兗州
			        CastleId.JOSHU,   // 徐州
			        CastleId.KEISHU,  // 荊州
			        CastleId.YOUSHU,  // 揚州
                },
                19, 9,          // 描画位置
		        "豫州"         // マップ上の名前
                ),
            new Castle(
                "冀州",         // 名前
                LordId.ENSHO,     // 城主
                // 接続された城のリスト
                new CastleId[]{
                    CastleId.SHIREI,  // 司隸
			        CastleId.ENSHU,   // 兗州
			        CastleId.JOSHU,   // 徐州
			        CastleId.YUSHU,   // 幽州
		        },
                19, 3,          // 描画位置
		        "冀州"         // マップ上の名前
                ),
            new Castle(
                "兗州",     // 名前
                LordId.SOSO,  // 城主
                // 接続された城のリスト
                new CastleId[]{
                    CastleId.SHIREI,  // 司隸
			        CastleId.YOSHU,   // 豫州
			        CastleId.KISHU,   // 冀州
			        CastleId.JOSHU,   // 徐州
		        },
                19, 6,      // 描画位置
		        "兗州"     // マップ上の名前
                ),
            new Castle(
                "徐州",         // 名前
                LordId.RYOFU,     // 城主
                // 接続された城のリスト
                new CastleId[]{
                    CastleId.YOSHU,   // 豫州
			        CastleId.KISHU,   // 冀州
			        CastleId.ENSHU,   // 兗州
			        CastleId.YOUSHU,  // 揚州
		        },
                27, 7,          // 描画位置
		        "徐州"         // マップ上の名前
                ),
            new Castle(
                "荊州",       // 名前
                LordId.RYUHYO,  // 城主
                // 接続された城のリスト
                new CastleId[]{
                    CastleId.SHIREI,  // 司隸
			        CastleId.YOSHU,   // 豫州
			        CastleId.YOUSHU,  // 揚州
			        CastleId.EKISHU,  // 益州
		        },
                11,11,      // 描画位置
		        "荊州"     // マップ上の名前
                ),
            new Castle(
                "揚州",         // 名前
                LordId.SONSAKU,   // 城主
                // 接続された城のリスト
                new CastleId[]{
                    CastleId.YOSHU,   // 豫州
			        CastleId.JOSHU,   // 徐州
			        CastleId.KEISHU,  // 荊州
		        },
                25,11,          // 描画位置
		        "揚州"         // マップ上の名前
                ),
            new Castle(
                "益州",   // 名前
                LordId.RYUSHO,      // 城主
                // 接続された城のリスト
                new CastleId[]{
                    CastleId.SHIREI,  // 司隸
			        CastleId.KEISHU,  // 荊州
		        },
                 1,11,          // 描画位置
		        "益州"         // マップ上の名前
                ),
            new Castle(
                "涼州",         // 名前
                LordId.BATO,     // 城主
                // 接続された城のリスト
                new CastleId[]{
                    CastleId.SHIREI,  // 司隸
		        },
                 1, 3,          // 描画位置
		        "涼州"         // マップ上の名前
                ),
            new Castle(
                "幽州",         // 名前
                LordId.KOSONSAN,    // 城主
                //  接続された城のリスト
                new CastleId[]{
                    CastleId.KISHU,   // 冀州
		        },
                29, 1,          // 描画位置
		        "幽州"         // マップ上の名前
                ),
        };
        // プロバティ
        public static Castle[] castles
        {
            get { return s_castles; }
        }
    } // class
} // namespace 