using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using Util;

namespace FormatHtmlTests
{
    public class Rate : Primitivable
    {
        private readonly bool zero;

	    private readonly String stringField;

	    public Rate(String _value)
        {
            Regex reg_ = new Regex("^(-?([0-9]+(/-?0*[1-9][0-9]*|\\.[0-9]*)?|\\.[0-9]*))$");
            if (!reg_.IsMatch(_value))
            {
                throw new FormatException(_value);
            }
            stringField = _value;
            zero = _value.Equals("0");
        }

        public bool isZero()
        {
            return zero;
        }

        public override String ToString()
        {
            return stringField;
        }
    }
}
