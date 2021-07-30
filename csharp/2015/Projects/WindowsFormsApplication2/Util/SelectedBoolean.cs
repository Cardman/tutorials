using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Util
{
    public enum SelectedBoolean
    {
        YES,NO,YES_AND_NO
    }
    static class SelectedBooleanExt
    {
        public static bool? getSelected(this SelectedBoolean _sel)
        {
            if (_sel == SelectedBoolean.YES)
            {
                return true;
            }
            if (_sel == SelectedBoolean.NO)
            {
                return false;
            }
            return null;
        }
        public static SelectedBoolean neg(this SelectedBoolean _sel)
        {
            if (_sel.Equals(SelectedBoolean.YES))
            {
                return SelectedBoolean.NO;
            }
            if (_sel.Equals(SelectedBoolean.NO))
            {
                return SelectedBoolean.YES;
            }
            return SelectedBoolean.YES_AND_NO;
        }
    }
}
