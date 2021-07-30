using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Util
{
    public class NaturalComparator<T> : IComparer<T> where T : IComparable<T>
    {
        public int Compare(T x, T y)
        {
            return x.CompareTo(y);
        }
    }
}
