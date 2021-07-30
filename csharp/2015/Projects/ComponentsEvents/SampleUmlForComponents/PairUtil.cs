using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SampleUmlForComponents
{
    public class PairUtil
    {
        public static bool eq<T1, S1>(Pair<T1, S1> _pair1, Pair<T1, S1> _pair2)
        {
            if (_pair1 == null)
            {
                return _pair2 == null;
            }
            return _pair1.Equals(_pair2);
        }
    }
}
