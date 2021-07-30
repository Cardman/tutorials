using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;
using Util;

namespace Stream
{
    public abstract class TemplateSerial : ElementsSerial
    {
        public const String COMPARATOR = "Comparer";

        public const String ID = "id";
        public const String REF = "ref";

	    private long? id;

        private long? refId;

        public override XmlElement serialize(XmlDocument _doc)
        {
            XmlElement node_ = _doc.CreateElement(ElementsSerial.getType(getValueClass()));
            if (getId() != null)
            {
                node_.SetAttribute(ID, getId().ToString());
            }
            if (getRef() != null)
            {
                node_.SetAttribute(REF, getRef().ToString());
            }
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
            XmlElement node_ = _doc.CreateElement(ElementsSerial.getType(getValueClass()));//TODO test
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
        //	List<TemplateSerial> references(List<TemplateSerial> _list) {
        //		List<TemplateSerial> list_ = new ArrayList<>();
        //		if (id == null) {
        //			return list_;
        //		}
        //		for(TemplateSerial e: _list) {
        //			if (e.ref != id) {
        //				continue;
        //			}
        //			//id != null && e.ref == id ==> e.ref != null
        //			list_.add(e);
        //		}
        //		return list_;
        //	}
        public abstract void appendElementSerialWithoutRef(MyList<ElementsSerial> _elt);
        public abstract void appendElementSerial(MyList<ElementsSerial> _elt);
        public abstract void setElementSerial(ElementsSerial _e, ElementsSerial _newE);
        public long? getId()
        {
            return id;
        }

        public void setId(long? _id)
        {
            id = _id;
        }

        public long? getRef()
        {
            return refId;
        }

        public void setRef(long? _ref)
        {
            refId = _ref;
        }
    }
}
