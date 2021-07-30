using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace StreamTests
{
    public class ReverseComparer : Comparer<string>
    {
        public override int Compare(string x, string y)
        {
            return y.CompareTo(x);
        }
    }
}
