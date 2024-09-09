//======================================
//	三国志 年表
//======================================
using System;       // Object
using System.Text;  // StringBuilder
using Utility = GP2.Utility;

namespace Sangokushi_CS
{
    internal class Chronology
    {
        StringBuilder m_sb;

        // コンストラクター
        public Chronology()
        {
            m_sb = new StringBuilder();
        }
        // クリア
        public void Clear()
        {
            m_sb.Clear();
        }
        // 記録
        public void Record(string fmt, params Object[] args)
        {
            string str = string.Format(fmt, args);
            m_sb.Append(str);
        }
        // プリント
        public void Print()
        {
            Utility.Printf(m_sb.ToString());
        }
    } // class
} // namespace