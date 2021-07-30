using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;
using Util;

namespace Stream
{
    class BooleanSerial : PrimitiveSerial
    {
        private bool? value;

        public BooleanSerial(bool? _value)
        {
            value = _value;
        }

        public BooleanSerial(XmlNode _node){

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
            //Boolean.class.getName()
            Type t_ = typeof(bool);
            string fullType_ = Constants.getTypeFullString(t_);
            if (!fullType_.ToLower().Equals(name_.ToLower()))
            {
                throw new ClassFoundException();
                //throw new ClassFoundException(name_, Boolean.class.getName());
            }
            XmlNode value_ = map_.GetNamedItem(VALUE);
		    if (value_ != null) {
                //value = new Boolean(value_.Value);
                value = bool.Parse(value_.Value);
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
