using FormatHtml;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Util;

namespace FormatHtmlTests
{
    public class MyTranslator : Translator
    {
        public string getString(string _pattern, Configuration _conf, Map<string, string> _files, Bean _object, object _value)
        {
            return _value + " &lt;= " + _value;
        }
    }
}
