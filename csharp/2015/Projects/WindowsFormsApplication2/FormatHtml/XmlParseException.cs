using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FormatHtml
{
    public class XmlParseException : Exception
    {
        public XmlParseException(string _message)
            :base(_message)
        {

        }
    }
}
