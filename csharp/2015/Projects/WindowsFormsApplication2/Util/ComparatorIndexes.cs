using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Util
{
    public class ComparatorIndexes<T> : IComparer<T?> where T : struct
    {//, IComparer
        private MyList<T?> order;

        public ComparatorIndexes(MyList<T?> _order)
        {
            order = _order;
        }

        /*public int Compare(object _o1, object _o2)
        {
            return order.indexOfObj((T)_o1) - order.indexOfObj((T)_o2);
        }*/

        public int Compare(T? _o1, T? _o2)
        {
            return order.indexOfObj(_o1) - order.indexOfObj(_o2);
        }
    }
}
