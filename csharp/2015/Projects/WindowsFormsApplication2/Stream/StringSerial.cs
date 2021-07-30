using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;
using Util;

namespace Stream
{
    class StringSerial : PrimitiveSerial
    {
        private String value;

        public StringSerial(String _value)
        {
            value = _value;
        }

        public StringSerial(XmlNode _node) {

            XmlNamedNodeMap map_ = _node.Attributes;
            String name_ = _node.Name;
            XmlNode className_ = map_.GetNamedItem(CLASS);
		    if (className_ != null) {

                setClassName(className_.Value);
		    }
            XmlNode field_ = map_.GetNamedItem(FIELD);
		    if (field_ != null) {

                setField(field_.Value);
		    }
            XmlNode keyOfMap_ = map_.GetNamedItem(KEY);
		    if (keyOfMap_ != null) {

                setKeyOfMap(true);
		    }
            Type t_ = typeof(string);
            string stringType_ = Constants.getTypeFullString(t_);
            if (!stringType_.ToLower().Equals(name_.ToLower()))
            {
                //throw new ClassFoundException(name_, String.class.getName());
                throw new ClassFoundException();
            }
            /*if (!name_.equalsIgnoreCase(String.class.getName())) {
			throw new ClassFoundException(name_, String.class.getName());
		}*/
            XmlNode value_ = map_.GetNamedItem(VALUE);
		    if (value_ != null) {
			    value = value_.Value;
		    } else {
                //throw new NoAttributeForSerializable(VALUE, name_);
                throw new NoAttributeForSerializable();

            }
	    }
	
        public override object getValue()
        {
            return value;
        }
    }
}
