using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FormatHtml
{
    public class KeyValueException : Exception
    {
        public KeyValueException(String _keyValue)
            : base(_keyValue)
        {
        }
    }
}
