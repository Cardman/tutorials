using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;
using Util;

namespace Stream
{
    class NumberSerial<T> : PrimitiveSerial where T : struct
    {
        private T? value;

        public NumberSerial(T? _value)
        {
            value = _value;
        }

        public NumberSerial(XmlNode _node) {

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
		    try {
			    //class_ can be a native class inheriting from Number
			    //and is found by comparing, in a case insensitive way, its name
			    //with the name of a native class inheriting from Number
			    XmlNode value_ = map_.GetNamedItem(VALUE);
                Type t_ = typeof(long);
                string longType_ = Constants.getTypeFullString(t_);
                t_ = typeof(int);
                string intType_ = Constants.getTypeFullString(t_);
                if (name_.ToLower().Equals(longType_.ToLower())) {
				    value = long.Parse(value_.Value) as T?;
			    } else if (name_.ToLower().Equals(intType_.ToLower()))
                {
                    value = int.Parse(value_.Value) as T?;
                }
                else {
                    //class_ does not inherit from Number
                    //throw new ClassFoundException(true, name_, Number.class.getName());
                    throw new ClassFoundException();
                }
                if (value == null)
                {
                    throw new ClassFoundException();
                }
		    } catch (NullReferenceException) {
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
