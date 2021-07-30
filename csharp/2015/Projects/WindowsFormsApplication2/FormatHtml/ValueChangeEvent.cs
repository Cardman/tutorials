using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Util;

namespace FormatHtml
{
    public class ValueChangeEvent
    {
        private readonly MyList<long> indexes;

        private readonly Object oldValue;

	    private readonly Object newValue;


        public ValueChangeEvent(MyList<long> _indexes, Object _oldValue, Object _newValue)
        {
            indexes = _indexes;
            oldValue = _oldValue;
            newValue = _newValue;
        }

        public List<long> getIndexes()
        {
            return indexes;
        }

        public Object getOldValue()
        {
            return oldValue;
        }

        public Object getNewValue()
        {
            return newValue;
        }
    }
}
