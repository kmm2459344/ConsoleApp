//======================================
//	三国志 ステージ
//=======================
using System.Diagnostics;
using Utility = GP2.Utility;

namespace Sangokushi_CS
{
    enum DrawMode
    {
        Intro,    // ゲーム開始時
        Turn,     // ターン中
        Event,    // イベント発生中
        GameOver, // ゲームオーバー中
        Ending,   // エンディング中
    }

    internal class Stage
    {
        Castle[] m_castles;      // 城データ
        int m_year;              // 年
        LordId m_playerLord;     // プレーヤ大名
        Chronology m_chro;       // 年表
        CastleId[] m_turnOrder;
        bool m_isDoneHonnojiEvent;  // 本能寺の変あったか?

        // プロパティ
        public bool isDoneHonnojiEvent
        {
            get { return m_isDoneHonnojiEvent; }
            set { m_isDoneHonnojiEvent = value; }
        }
        // プロパティ
        public LordId playerLord
        {
            get { return m_playerLord; }
            set { m_playerLord = value; }
        }
        public int castlesSize
        {
            get { return m_castles.Length; }
        }
        public Chronology chro
        {
            get { return m_chro; }
        }
        public int year
        {
            get { return m_year; }
        }

        // コンストラクタ
        public Stage(Castle[] castles, Chronology chro, int year)
        {
            m_castles = castles;
            m_chro = chro;
            m_playerLord = LordId.NONE;
            m_turnOrder = new CastleId[m_castles.Length];
            m_year = year;
        }
        // スタート
        public void Start()
        {
            // 城の城主と兵員をリセット
            for (int i = 0; i < m_castles.Length; i++)
            {
                Castle castle = GetCastle((CastleId)i);
                castle.owner = (LordId)i;
                castle.troopCount = Data.TROOP_BASE;
            }
        }
        // プレーヤ大名のセット
        public void SetPlayerLord(CastleId castleId)
        {
            m_playerLord = GetCastleOwner(castleId);
        }
        // 画面描画
        public void DrawScreen(DrawMode drawMode, int turn)
        {
            Utility.ClearScreen();
            Utility.Printf(Data.map);
            Utility.PrintCursor(1, 1);
            Utility.Printf("{0,4}ねん", m_year);
            for (int i = 0; i < m_castles.Length; i++)
            {
                Castle castle = GetCastle((CastleId)i);
                int curx = castle.curx;
                int cury = castle.cury;
                LordId owner = castle.owner;
                int troopCount = castle.troopCount;
                string mapName = castle.mapName;
                Utility.PrintCursor(curx, cury);
                Utility.Printf("{0}{1}{2}", i, mapName, troopCount);
                Utility.PrintCursor(curx, cury + 1);
                Utility.Printf("{0}", GetLordMapName(owner));
            }
            Utility.PrintCursor(1, 18);
        }
        // ターン順番を作成
        public void MakeTurnOrder()
        {
            int turnSize = m_castles.Length;
            for (int i = 0; i < turnSize; i++)
            {
                m_turnOrder[i] = (CastleId)i;
            }
            // m_turnOrder[]をシャッフル
            for (int i = 0; i < turnSize; i++)
            {
                int j = Utility.GetRand(turnSize);
                CastleId tmp = m_turnOrder[i];
                m_turnOrder[i] = m_turnOrder[j];
                m_turnOrder[j] = tmp;
            }
        }
        // ターン順番をプリント
        protected void PrintTurnOrder(int turn)
        {
            for (int i = 0; i < m_turnOrder.Length; i++)
            {
                string cur = i == turn ? "＞" : "　";
                CastleId id = m_turnOrder[i];
                Utility.Printf("{0}{1}", cur, GetCastleMapName(id));
            }
            Utility.Putchar('\n');
            Utility.Putchar('\n');
        }
        // 次の年へ
        public void NextYear()
        {
            m_year++;
            // 各城の兵員をTROOP_BASEに近づける
            for (int i = 0; i < m_castles.Length; i++)
            {
                Castle castle = m_castles[i];
                int troopCount = castle.troopCount;
                int diff = troopCount - Data.TROOP_BASE;
                if (diff != 0)
                {
                    int add = diff < 0 ? +1 : -1;
                    castle.AddTroopCount(add);
                }
            }
        }
        // ターン実行
        public void ExecTurn(int turn)
        {
            CastleId currentCastle = m_turnOrder[turn];
            Castle castle = GetCastle(currentCastle);
            LordId owner = castle.owner;

            DrawScreen(DrawMode.Turn, turn);
            PrintTurnOrder(turn);
            Utility.Printf("{0}の　{1}の　ひょうじょうちゅう…\n"
                , GetLordFamilyName(owner)
                , GetCastleName(currentCastle)
            );
            Utility.Putchar('\n');

            CastleId targetCastle;
            int sendTroopCount;
            Command cmd;
            if (owner == m_playerLord)
            {
                cmd = UI.InputPlayerTurn(this, castle, out targetCastle, out sendTroopCount);
                ExecPlayerTurn(currentCastle, cmd, targetCastle, sendTroopCount);
            }
            else
            {
                Utility.PrintOut();
                Utility.WaitKey();
                cmd = AI.InputNpcTurn(this, castle, out targetCastle, out sendTroopCount);
                ExecNpcTurn(currentCastle, cmd, targetCastle, sendTroopCount);
            }
        }
        // プレーヤターンを実行
        protected void ExecPlayerTurn(CastleId currentCastle, Command cmd, CastleId targetCastle, int sendTroopCount)
        {
            Castle castle = GetCastle(currentCastle);
            switch (cmd)
            {
                case Command.Cancel:
                    Utility.Printf("しんぐんを　とりやめました\n");
                    Utility.PrintOut();
                    Utility.WaitKey();
                    break;
                case Command.Transit:
                    TransitTroop(castle, targetCastle, sendTroopCount);
                    Utility.Printf("{0}に　{1}にん　いどう　しました"
                           , GetCastleName(targetCastle)
                           , sendTroopCount * Data.TROOP_UNIT
                        );
                    Utility.PrintOut();
                    Utility.WaitKey();
                    break;
                case Command.Attack:
                    Utility.Printf("{0}に　{1}にんで　しゅつじんじゃ～！！\n"
                            , GetCastleName(targetCastle)
                            , sendTroopCount * Data.TROOP_UNIT
                        );
                    Utility.PrintOut();
                    Utility.WaitKey();
                    AttackTroop(castle, targetCastle, sendTroopCount);
                    break;
            }
        }
        // NPCターンを実行
        protected void ExecNpcTurn(CastleId currentCastle, Command cmd, CastleId targetCastle, int sendTroopCount)
        {
            Castle castle = GetCastle(currentCastle);
            LordId owner = GetCastleOwner(currentCastle);

            switch (cmd)
            {
                case Command.Cancel:
                    break;
                case Command.Transit:
                    TransitTroop(castle, targetCastle, sendTroopCount);
                    Utility.Printf("{0}から　{1}に　{2}にん　いどう　しました\n"
                        , GetCastleName(currentCastle)
                        , GetCastleName(targetCastle)
                        , sendTroopCount * Data.TROOP_UNIT
                    );
                    Utility.PrintOut();
                    Utility.WaitKey();
                    break;

                case Command.Attack:
                    Utility.Printf("{0}の　{1}（{2}）が　{3}に　せめこみました！\n"
                        , GetCastleName(currentCastle)
                        , GetLordFamilyName(owner)
                        , GetLordFirstName(owner)
                        , GetCastleName(targetCastle)
                    );
                    Utility.PrintOut();
                    Utility.WaitKey();
                    AttackTroop(castle, targetCastle, sendTroopCount);
                    break;
            }
        }
        // 移送処理
        protected void TransitTroop(Castle castle, CastleId targetCastle, int sendTroopCount)
        {
            castle.AddTroopCount(-sendTroopCount);
            Castle target = GetCastle(targetCastle);
            target.AddTroopCount(sendTroopCount);
        }
        // 攻撃処理
        protected void AttackTroop(Castle castle, CastleId targetCastle, int sendTroopCount)
        {
            castle.AddTroopCount(-sendTroopCount);
            LordId offenseLord = castle.owner;
            SiegeBattle(offenseLord, sendTroopCount, targetCastle);
        }
        // 包囲戦闘を行う
        protected void SiegeBattle(LordId offenseLord, int offenseTroopCount, CastleId defenseCastle)
        {
            Utility.ClearScreen();
            Utility.Printf("～ {0}の　たたかい～\n", GetCastleName(defenseCastle));
            Utility.Putchar('\n');
            LordId defenseLord = GetCastleOwner(defenseCastle);
            int defenseTroopCount = GetCastleTroopCount(defenseCastle);

            while (true)
            {
                Utility.Printf("{0}ぐん（{1,5}にん）　Ｘ　{2}ぐん（{3,5}にん）\n"
                    , GetLordFamilyName(offenseLord)
                    , offenseTroopCount * Data.TROOP_UNIT
                    , GetLordFamilyName(defenseLord)
                    , defenseTroopCount * Data.TROOP_UNIT
                );
                Utility.PrintOut();
                Utility.WaitKey();
                if (offenseTroopCount <= 0 || defenseTroopCount <= 0)
                {
                    break;
                }

                int rnd = Utility.GetRand(3);
                if (rnd == 0)
                {
                    defenseTroopCount--;
                    SetCastleTroopCount(defenseCastle, defenseTroopCount);
                }
                else
                {
                    offenseTroopCount--;
                }
            }
            Utility.Putchar('\n');

            if (defenseTroopCount <= 0)
            {
                // 防御側の負け
                SetCastleOwner(defenseCastle, offenseLord);
                SetCastleTroopCount(defenseCastle, offenseTroopCount);

                Utility.Printf("{0}　らくじょう！！\n"
                    , GetCastleName(defenseCastle)
                );
                Utility.Putchar('\n');

                Utility.Printf("{0}は　 {1}の　ものとなります\n"
                    , GetCastleName(defenseCastle)
                    , GetLordFamilyName(offenseLord)
                );
                Utility.PrintOut();
                Utility.WaitKey();

                if (GetCastleCount(defenseLord) <= 0)
                {
                    // 年表に記録
                    m_chro.Record(
                        "{0}ねん　{1}（{2}）が　{3}で　{4}（{5}）を　ほろぼす\n"
                        , m_year
                        , GetLordFamilyName(offenseLord)
                        , GetLordFirstName(offenseLord)
                        , GetCastleName(defenseCastle)
                        , GetLordFamilyName(defenseLord)
                        , GetLordFirstName(defenseLord)
                    );
                }
            }
            else
            {
                // 攻撃側の負け
                Utility.Printf("{0}ぐん　かいめつ！！\n"
                    , GetLordFamilyName(offenseLord)
                );
                Utility.Putchar('\n');
                Utility.Printf("{0}ぐんが　{1}を　まもりきりました！\n"
                    , GetLordFamilyName(defenseLord)
                    , GetCastleName(defenseCastle)
                );
                Utility.PrintOut();
                Utility.WaitKey();
            }
        }
        // プレーヤの負け?
        public bool IsPlayerLose()
        {
            return GetCastleCount(m_playerLord) == 0;
        }
        // プレーヤの勝ち?
        public bool IsPlayerWin()
        {
            return GetCastleCount(m_playerLord) == m_castles.Length;
        }
        // 指定城主の城を数える
        protected int GetCastleCount(LordId owner)
        {
            int count = 0;
            for (int i = 0; i < m_castles.Length; i++)
            {
                if (m_castles[i].owner == owner)
                {
                    count++;
                }
            }
            return count;
        }
        //---------------------------------------------------------
        // 城の名前を取得
        public string GetCastleName(CastleId id)
        {
            Castle castle = GetCastle(id);
            return castle.name;
        }
        // 城の城主を取得
        public LordId GetCastleOwner(CastleId id)
        {
            Castle castle = GetCastle(id);
            return castle.owner;
        }
        // 城の城主を設定
        void SetCastleOwner(CastleId id, LordId owner)
        {
            Castle castle = GetCastle(id);
            castle.owner = owner;
        }
        // 城の兵数を取得
        public int GetCastleTroopCount(CastleId id)
        {
            Castle castle = GetCastle(id);
            return castle.troopCount;
        }
        // 兵数をセット
        void SetCastleTroopCount(CastleId id, int troopCount)
        {
            Castle castle = GetCastle(id);
            castle.troopCount = troopCount;
        }
        // 城の近隣リストを取得
        public CastleId[] GetCastleConnectedList(CastleId id)
        {
            Castle castle = GetCastle(id);
            return castle.connectedList;
        }
        // 城のマップ名を取得
        string GetCastleMapName(CastleId id)
        {
            Castle castle = GetCastle(id);
            return castle.mapName;
        }
        // 城IDから城インタンスを取得
        Castle GetCastle(CastleId id)
        {
            int idx = (int)id;
            Debug.Assert(0 <= idx && idx < m_castles.Length);
            return m_castles[idx];
        }
        //---------------------------------------------------------
        // 城主の名を取得
        public string GetLordFirstName(LordId id)
        {
            id = changeLordId(id);
            return Lord.GetFirstName(id);
        }
        // 城主の姓を取得
        public string GetLordFamilyName(LordId id)
        {
            id = changeLordId(id);
            return Lord.GetFamilyName(id);
        }
        // 城主のマップ上の名前を取得
        public string GetLordMapName(LordId id)
        {
            id = changeLordId(id);
            return Lord.GetMapName(id);
        }
        // 城主変更
        protected LordId changeLordId(LordId id)
        {
            return id;
        }
    } // class
} // namespace 