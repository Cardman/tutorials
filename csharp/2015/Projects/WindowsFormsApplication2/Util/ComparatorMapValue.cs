using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Util
{
    public class ComparatorMapValue<T> : IComparer<T?> where T: struct
    {
        private Map<T?, String> map;

        public ComparatorMapValue(Map<T?, String> _map)
        {
            map = _map;
        }

        public int Compare(T? _o1, T? _o2)
        {
            return map.getVal(_o1).CompareTo(map.getVal(_o2));
        }
    }
}
