using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Util;

namespace FormatHtmlTests
{
    public class MyMap<K, V> : Map<K, V> where K : IComparable<K>
    {
        public SortableList<K> list()
        {
            SortableList<K> l_ = new SortableList<K>(getKeys());
            l_.sort();
            return l_;
        }
    }
}
