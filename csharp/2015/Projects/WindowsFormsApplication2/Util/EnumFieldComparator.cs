using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Util
{
    public class EnumFieldComparator<E> where E : struct
    {
        private SelectedBoolean increasing = SelectedBoolean.YES_AND_NO;

        private int priority;

        private Map<E, String> translations;

        public int compare(E _o1, E _o2)
        {
            if (increasing == SelectedBoolean.YES)
            {
                return translations.getVal(_o1).CompareTo(translations.getVal(_o2));
            }
            if (increasing == SelectedBoolean.NO)
            {
                return translations.getVal(_o2).CompareTo(translations.getVal(_o1));
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

        public Map<E, String> getTranslations()
        {
            return translations;
        }

        public void setTranslations(Map<E, String> _translations)
        {
            translations = _translations;
        }
    }
}
