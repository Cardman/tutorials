using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FormatHtml
{
    public class AlreadyDefinedVarException : Exception
    {
        public AlreadyDefinedVarException(String _keyValue)
            : base(_keyValue)
        {
        }
    }
}
