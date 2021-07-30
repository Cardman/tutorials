using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace StreamTests
{
    public class Composite
    {
        private long num;
        private long den;
        public Composite()
        {
            den = 1;
        }
        public Composite(long _num, long _den)
        {
            num = _num;
            den = _den;
        }
        // override object.Equals
        public override bool Equals(object obj)
        {

            if (obj == null || GetType() != obj.GetType())
            {
                return false;
            }
            Composite r_ = (Composite)obj;
            if (r_.num != num)
            {
                return false;
            }
            if (r_.den != den)
            {
                return false;
            }
            return true;
        }
        public override string ToString()
        {
            return num + "/" + den;
        }
    }
}
