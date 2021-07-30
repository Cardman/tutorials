using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using System.Xml;
using Util;

namespace Stream
{
    class ComparatorSerial : TemplateSerial
    {
        private const String TYPES = "types";
        private Object value;
        private Type[] types;

        public ComparatorSerial(IComparer _value)
        {
            value = _value;
            types = value.GetType().GetGenericArguments();
        }

        public ComparatorSerial(XmlNode _node)
        {
            XmlNamedNodeMap map_ = _node.Attributes;
            XmlNode className_ = map_.GetNamedItem(CLASS);
		    if (className_ == null) {
                //throw new NoAttributeForSerializable(CLASS, _node.getNodeName());
                throw new NoAttributeForSerializable();
            }
            XmlNode types_ = map_.GetNamedItem(TYPES);
            string typesStr_ = "";
            if (types_ != null)
            {
                typesStr_ = types_.Value;
            }
            Type class_ = Constants.classForName(_node.Name, typesStr_);
            types = class_.GetGenericArguments();
            XmlNode ref_ = map_.GetNamedItem(REF);
		    if (ref_ != null) {
                setRef(long.Parse(ref_.Value));
                return;
            }
            XmlNode id_ = map_.GetNamedItem(ID);
		    if (id_ != null) {
                setId(long.Parse(id_.Value));
            }
            ConstructorInfo constr_ = class_.GetConstructor(new Type[0]);
            //constr_.setAccessible(constr_.getAnnotation(RwXml.class)!=null);
		    value = constr_.Invoke(new object[0]);
	    }
        public override Object getValue()
        {
            return value;
        }

        public override Type getValueClass()
        {
            return value.GetType();
        }

        public override XmlElement serialize(XmlDocument _doc)
        {
            XmlElement node_ = base.serialize(_doc);
            if (types.Length > 0)
            {
                string res_ = Constants.getTypeString(value.GetType());
                res_ = res_.Substring(res_.IndexOf(SPECIAL_SEP));
                node_.SetAttribute(TYPES, res_);
            }
            node_.SetAttribute(COMPARATOR, EMPTY_STRING);
            return node_;
        }

        public override XmlElement serializeWithoutRef(XmlDocument _doc)
        {
            XmlElement node_ = base.serializeWithoutRef(_doc);
            if (types.Length > 0)
            {
                string res_ = Constants.getTypeString(value.GetType());
                res_ = res_.Substring(res_.IndexOf(SPECIAL_SEP));
                node_.SetAttribute(TYPES, res_);
            }
            node_.SetAttribute(COMPARATOR, EMPTY_STRING);
            return node_;
        }

        public override void appendElementSerial(MyList<ElementsSerial> _elt)
        {
		    foreach (ElementsSerial e in _elt) {
                string str_ = e.getClassName();
                Type class_;
                if (str_.Contains(SPECIAL_SEP))
                {
                    string types_ = str_.Substring(str_.IndexOf(SPECIAL_SEP));
                    class_ = Constants.classForName(str_, types_);
                }
                else
                {
                    class_ = Constants.classForName(str_);
                }
                FieldInfo field_ = SerializeXmlObject.getField(class_, e.getField());
                field_.SetValue(value, e.getValue());
                /*foreach (FieldInfo f: class_.getDeclaredFields())
                {
                    if (!f.getName().equals(e.getField()))
                    {
                        continue;
                    }
                    if (!SerializeXmlObject.isUpdateFinalFields())
                    {
                        if (Modifier.isFinal(f.getModifiers()))
                        {
                            continue;
                        }
                    }
                    f.setAccessible(cl_.getAnnotation(RwXml.class)!=null);
				    f.set(value, e.getValue());
				    break;
			    }*/
		    }
	    }

        public override void setElementSerial(ElementsSerial _e, ElementsSerial _newE)
        {
            string str_ = _e.getClassName();
            Type class_;
            if (str_.Contains(SPECIAL_SEP))
            {
                string types_ = str_.Substring(str_.IndexOf(SPECIAL_SEP));
                class_ = Constants.classForName(str_, types_);
            }
            else
            {
                class_ = Constants.classForName(str_);
            }
            FieldInfo field_ = SerializeXmlObject.getField(class_, _e.getField());
            field_.SetValue(value, _newE.getValue());
            /*for (Field f: cl_.getDeclaredFields()) {
            if (!f.getName().equals(_e.getField()))
            {
                continue;
            }
            if (!SerializeXmlObject.isUpdateFinalFields())
            {
                if (Modifier.isFinal(f.getModifiers()))
                {
                    continue;
                }
            }
            f.setAccessible(cl_.getAnnotation(RwXml.class)!=null);
			    f.set(value, _newE.getValue());
			    break;
		    }*/
	    }

        public override void appendElementSerialWithoutRef(MyList<ElementsSerial> _elt)
        {
            foreach (ElementsSerial e in _elt)
            {
                string str_ = e.getClassName();
                Type class_;
                if (str_.Contains(SPECIAL_SEP))
                {
                    string types_ = str_.Substring(str_.IndexOf(SPECIAL_SEP));
                    class_ = Constants.classForName(str_, types_);
                }
                else
                {
                    class_ = Constants.classForName(str_);
                }
                FieldInfo field_ = SerializeXmlObject.getField(class_, e.getField());
                field_.SetValue(value, e.getValue());
            }
            /*for (ElementsSerial e: _elt) {
                Class <?> cl_ = Constants.classForName(e.getClassName());
                for (Field f: cl_.getDeclaredFields())
                {
                    if (!f.getName().equals(e.getField()))
                    {
                        continue;
                    }
                    if (!SerializeXmlObject.isUpdateFinalFields())
                    {
                        if (Modifier.isFinal(f.getModifiers()))
                        {
                            continue;
                        }
                    }
                    f.setAccessible(cl_.getAnnotation(RwXml.class)!=null);
				        f.set(value, e.getValue());
				        break;
			        }
		        }
	        }*/
        }
    }
}
