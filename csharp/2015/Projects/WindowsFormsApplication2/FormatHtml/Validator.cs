using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;

namespace FormatHtml
{
    public interface Validator
    {
        void validate(Navigation _navigation, XmlNode _node, Object _value);
    }
}
