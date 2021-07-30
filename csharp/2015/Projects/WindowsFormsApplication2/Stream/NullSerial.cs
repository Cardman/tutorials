using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;
using Util;

namespace Stream
{
    class NullSerial : ElementsSerial
    {
        private const String NULL_ATTR = "null";

	    public NullSerial()
        {
        }

        public NullSerial(XmlNode _node)

        {
		    if (!_node.Name.Equals(NULL_ATTR)) {
                //throw new ClassFoundException(_node.getNodeName(), NULL_ATTR);
                throw new ClassFoundException();
            }
            XmlNamedNodeMap map_ = _node.Attributes;
            XmlNode field_ = map_.GetNamedItem(FIELD);
		    if (field_ != null) {
                setField(field_.Value);
            }
            XmlNode className_ = map_.GetNamedItem(CLASS);
		    if (className_ != null) {
                setClassName(className_.Value);
            }
            XmlNode keyOfMap_ = map_.GetNamedItem(KEY);
		    if (keyOfMap_ != null) {
                setKeyOfMap(true);
            }
        }

        public override Object getValue()
        {
            return null;
        }

        public override Type getValueClass()
        {
            return null;
        }

        public override XmlElement serialize(XmlDocument _doc)
        {
            XmlElement node_ = _doc.CreateElement(NULL_ATTR);
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

        public override XmlElement serializeWithoutRef(XmlDocument _doc)
        {
            XmlElement node_ = _doc.CreateElement(NULL_ATTR);
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
