using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Util;

namespace FormatHtml
{
    public interface Translator
    {
        String getString(String _pattern, Configuration _conf, Map<String, String> _files, Bean _object, Object _value);
    }
}
