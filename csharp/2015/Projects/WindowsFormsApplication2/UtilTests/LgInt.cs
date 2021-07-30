using ReflectionCore;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Util;

namespace UtilTests
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
            lg_.den = long.Parse(sep_[2]);
            return lg_;
        }

        [FromAndToString()]
        public string toString()
        {
            return num+"/"+den;
        }
    }
}
