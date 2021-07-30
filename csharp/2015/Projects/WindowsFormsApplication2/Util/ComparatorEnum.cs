using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Util
{
    public class ComparatorEnum<T> : IComparer<T> where T : struct, IComparable
    {
        public int Compare(T x, T y)
        {
            /*object o1_ = x;
            object o2_ = y;*/
            return x.CompareTo(y);
        }
    }
}
