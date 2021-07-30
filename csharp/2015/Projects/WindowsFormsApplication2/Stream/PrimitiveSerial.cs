using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;
using Util;

namespace Stream
{
    public abstract class PrimitiveSerial : ElementsSerial
    {
        public const String VALUE = "value";

        public override Type getValueClass()
        {
            return getValue().GetType();
        }

        public override XmlElement serialize(XmlDocument _doc)
        {
            XmlElement node_ = serializeMetaInfo(_doc);
            node_.SetAttribute(VALUE, getValue().ToString());
		    return node_;
        }

        public override XmlElement serializeWithoutRef(XmlDocument _doc)
        {
            XmlElement node_ = serializeMetaInfo(_doc);
            node_.SetAttribute(VALUE, getValue().ToString());
		    return node_;
        }

        public XmlElement serializeMetaInfo(XmlDocument _doc)
        {
            XmlElement node_ = _doc.CreateElement(ElementsSerial.getType(getValueClass()));
            if (getField() != null && !getField().isEmpty())
            {
                node_.SetAttribute(FIELD, getField());
            }
            if (getClassName() != null)
            {
                node_.SetAttribute(CLASS, getClassName());
            }
            if (isKeyOfMap())
            {
                node_.SetAttribute(KEY, EMPTY_STRING);
            }
            return node_;
        }
    }
}
