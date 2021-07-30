using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Util
{
    public class Sorting : IComparable<Sorting>
    {

        private int index;

        public int getIndex()
        {
            return index;
        }

        public void setIndex(int _index)
        {
            index = _index;
        }

        public int CompareTo(Sorting _o2)
        {
            return index.CompareTo(_o2.index);
        }
    }
}
