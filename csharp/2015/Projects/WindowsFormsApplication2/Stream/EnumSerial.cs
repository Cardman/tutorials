using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;
using Util;

namespace Stream
{
    class EnumSerial : PrimitiveSerial
    {
        private Object value;

        public EnumSerial(Enum _enumConst)
        {
            value = _enumConst;
        }

        public EnumSerial(XmlNode _node){

            value = initialize(_node);
            XmlNamedNodeMap map_ = _node.Attributes;
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
	    }

        private static Enum initialize(XmlNode _node){
		    XmlNamedNodeMap map_ = _node.Attributes;
            Type class_ = Constants.classForName(_node.Name);
            if (!class_.IsEnum)
            {
                //throw an exception
                throw new ClassFoundException();
            }
            //Class<?> subClass_ = class_.asSubclass(Enum.class);
            XmlNode valueNode_ = map_.GetNamedItem(VALUE);
		    if (valueNode_ == null) {
                //throw new NoAttributeForSerializable(VALUE, _node.getNodeName());
                throw new NoAttributeForSerializable();
            }
		    String name_ = valueNode_.Value;
            try
            {
                return (Enum) Enum.Parse(class_, name_);
            } catch (Exception)
            {
                throw new InexistingValueForEnum();
            }
            
            /*foreach (Object s in class_.GetEnumValues()) { 
                if (class_.GetEnumName(s).Equals(name_)) {
                    return (Enum) s;
			    }
            }
            //return null;
            //throw new InexistingValueForEnum(name_, subClass_.getName());
            throw new InexistingValueForEnum();*/

        }

	    public override XmlElement serialize(XmlDocument _doc)
        {
            XmlElement node_ = base.serialize(_doc);
            node_.SetAttribute(VALUE, ((Enum)getValue()).ToString());
		    return node_;
        }

        public override XmlElement serializeWithoutRef(XmlDocument _doc)
        {
            XmlElement node_ = base.serializeWithoutRef(_doc);
            node_.SetAttribute(VALUE, ((Enum)getValue()).ToString());
		    return node_;
        }

        public override Type getValueClass()
        {
            return value.GetType();
        }

        public override object getValue()
        {
            return value;
        }
    }
}
