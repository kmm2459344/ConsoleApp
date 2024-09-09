//======================================
//	三国志 AI
//======================================
using System.Collections.Generic; // List<T>
using Utility = GP2.Utility;

namespace Sangokushi_CS
{
    internal static class AI
    {
        // NPCターンの入力(思考)
        public static Command InputNpcTurn(Stage stage, Castle castle, out CastleId targetCastle, out int sendTroopCount)
        {
            LordId npcLord = castle.owner;
            int npcTroopCount = castle.troopCount;
            Command cmd = Command.Cancel;
            CastleId _targetCastle = CastleId.NONE;
            int _sendTroopCount = 0;

            List<CastleId> enemyCastleList = new List<CastleId>();
            //
            // 隣接する敵の城をリスティング
            //
            CastleId[] connectedList = castle.connectedList;
            for (int i = 0; i < connectedList.Length; i++)
            {
                CastleId id = connectedList[i];
                if (stage.GetCastleOwner(id) != npcLord)
                {
                    enemyCastleList.Add(id);
                }
            }

            if (enemyCastleList.Count > 0)
            {
                // troopCount最初の城を取得
                _targetCastle = GetMinTroopCastle(enemyCastleList, stage);

                // 攻め込む条件チェック
                //  ・こちらの兵力は標準値以上であるか?
                //  ・こちらの兵力が守備兵を差し引いて相手の2倍以上か?
                int tgtTroopCount = stage.GetCastleTroopCount(_targetCastle);
                if (npcTroopCount >= Data.TROOP_BASE
                || npcTroopCount - 1 >= tgtTroopCount * 2)
                {
                    _sendTroopCount = npcTroopCount - 1;
                    if (_sendTroopCount > 0)
                    {
                        cmd = Command.Attack;
                    }
                }
            }
            else
            {
                // 隣接する敵がいない
                List<CastleId> connectedCastleList = new List<CastleId>(connectedList);
                List<CastleId> frontCastleList = new List<CastleId>();
                // 前線の敵をリスティング
                for (int i = 0; i < connectedList.Length; i++)
                {
                    CastleId id = connectedList[i];
                    if (isFrontCastle(id, stage))
                    {
                        frontCastleList.Add(id);
                    }
                }
                if (frontCastleList.Count > 0)
                {
                    _targetCastle = GetMinTroopCastle(frontCastleList, stage);
                    _sendTroopCount = Data.TROOP_MAX - stage.GetCastleTroopCount(_targetCastle);
                    if (_sendTroopCount > npcTroopCount)
                    {
                        // 前線に送るなら全兵員
                        _sendTroopCount = npcTroopCount;
                    }
                }
                else
                {
                    _targetCastle = GetMinTroopCastle(connectedCastleList, stage);
                    _sendTroopCount = Data.TROOP_MAX - stage.GetCastleTroopCount(_targetCastle);
                    int tmp = npcTroopCount - (Data.TROOP_BASE - 1);
                    if (_sendTroopCount > tmp)
                    {
                        // 前線でないなら、BASE-1を残して、それより大きい分を
                        _sendTroopCount = tmp;
                    }
                }
                if (_sendTroopCount > 0)
                {
                    cmd = Command.Transit;
                }
            }
            targetCastle = _targetCastle;
            sendTroopCount = _sendTroopCount;
            return cmd;
        }
        // TroopCount最小の城をlistから取得
        static CastleId GetMinTroopCastle(List<CastleId> list, Stage stage)
        {
            // TroopCountの小さい順にソート
            list.Sort((a, b) =>
            {
                int a_troopCount = stage.GetCastleTroopCount(a);
                int b_troopCount = stage.GetCastleTroopCount(b);
                return a_troopCount - b_troopCount;
            });
            // TroopCount最小の数をかぞえる
            int minTroopCount = stage.GetCastleTroopCount(list[0]);
            int i = 1;
            for (; i < list.Count; i++)
            {
                if (minTroopCount < stage.GetCastleTroopCount(list[i]))
                {
                    break;
                }
            }
            // TroopCount最小の中からランダムに選ぶ
            int idx = Utility.GetRand(i);
            return list[idx];
        }
        // 前線の城か?
        static bool isFrontCastle(CastleId castleId, Stage stage)
        {
            // 近隣に敵の城がある?
            CastleId[] connectedList = stage.GetCastleConnectedList(castleId);
            LordId owner = stage.GetCastleOwner(castleId);
            for (int i = 0; i < connectedList.Length; i++)
            {
                CastleId id = connectedList[i];
                if (stage.GetCastleOwner(id) != owner)
                {
                    return true;
                }
            }
            return false;
        }
    } // class
} // namespace 