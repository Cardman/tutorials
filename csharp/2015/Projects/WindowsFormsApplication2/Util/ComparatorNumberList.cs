using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Util
{
    public class ComparatorNumberList : IComparer<MyList<int>>
    {
        public int Compare(MyList<int> _o1, MyList<int> _o2)
        {
            int minimumSize_ = Math.Min(_o1.size(), _o2.size());
            for (int i = List.FIRST_INDEX; i < minimumSize_; i++)
            {
                int res_ = _o1.get(i).CompareTo(_o2.get(i));
                if (res_ != 0)
                {
                    return res_;
                }
            }
            if (_o1.size() > _o2.size())
            {
                return 1;
            }
            if (_o1.size() < _o2.size())
            {
                return -1;
            }
            return 0;
        }
    }
}
