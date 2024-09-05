//======================================
//      疑似3Dダンジョン　キャラクター
//======================================
using Vector2 = GP2.Vector2;
using System.Diagnostics;   // Debug

namespace _3DDungeonGame_CS
{
    internal class Character
    {
        Vector2 m_pos;    // 座標
        Direction m_dir;  // 向いている方位

        // コンストラクタ
        public Character(Vector2 pos, Direction dir)
        {
            m_pos = pos;
            m_dir = dir;
        }
        // プロパティpos
        public Vector2 pos
        {
            get { return m_pos; }
            set { m_pos = value; }
        }
        // プロパティdir
        public Direction dir
        {
            get { return m_dir; }
            set { m_dir = value; }
        }
        // 後ろを向く
        public void TurnBack()
        {
            m_dir = Misc.DirectionAdd(m_dir, 2);
        }
        // 左を向く
        public void TurnLeft()
        {
            // 北→西→南→東
            m_dir = Misc.DirectionAdd(m_dir, 1);
        }
        // 右を向く
        public void TurnRight()
        {
            // 北→東→南→西
            m_dir = Misc.DirectionAdd(m_dir, -1);
        }
    } // class
} // namespace