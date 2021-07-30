using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Util
{
    public class FieldComparator<T> where T : IComparable<T>
    {
        private SelectedBoolean increasing = SelectedBoolean.YES_AND_NO;

        private int priority;

        public int compare(T _o1, T _o2)
        {
            if (increasing == SelectedBoolean.YES)
            {
                return _o1.CompareTo(_o2);
            }
            if (increasing == SelectedBoolean.NO)
            {
                return _o2.CompareTo(_o1);
            }
            return 0;
        }

        public SelectedBoolean getIncreasing()
        {
            return increasing;
        }

        public void setIncreasing(SelectedBoolean _increasing)
        {
            increasing = _increasing;
        }

        public int getPriority()
        {
            return priority;
        }

        public void setPriority(int _priority)
        {
            priority = _priority;
        }
    }
}
