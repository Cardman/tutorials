using ReflectionCore;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Util;

namespace StreamTests
{
    public class Rate : Primitivable
    {
        private long num;
        private long den;
        public Rate()
        {
            den = 1;
        }
        public Rate(long _num, long _den)
        {
            num = _num;
            den = _den;
        }
        [FromAndToString()]
        public static Rate newLgInt(string _input)
        {
            string[] sep_ = _input.Split('/');
            Rate lg_ = new Rate();
            lg_.num = long.Parse(sep_[0]);
            lg_.den = long.Parse(sep_[1]);
            return lg_;
        }

        [FromAndToString()]
        public string toString()
        {
            return num + "/" + den;
        }
        // override object.Equals
        public override bool Equals(object obj)
        {

            if (obj == null || GetType() != obj.GetType())
            {
                return false;
            }
            Rate r_ = (Rate)obj;
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
