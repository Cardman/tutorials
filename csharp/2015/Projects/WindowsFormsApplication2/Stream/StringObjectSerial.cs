using ReflectionCore;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using System.Xml;
using Util;

namespace Stream
{
    class StringObjectSerial : PrimitiveSerial
    {
        private Object value;

        public StringObjectSerial(Object _value)
        {
            value = _value;
        }

        public StringObjectSerial(XmlNode _node) {
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
		    //try {
			    Type class_ = Constants.classForName(_node.Name);
                XmlNode value_ = map_.GetNamedItem(VALUE);
			    if (value_ == null) {
                //throw new NoValueException(name_);
                    throw new NoValueException();

                }
			    MethodInfo method_ = ConverterMethod.getFromStringMethod(class_);
			    if (method_ != null) {
				    value = method_.Invoke(null, new object[] { value_.Value });
				    return;
			    }
                if (!typeof(Primitivable).IsAssignableFrom(class_))
                {
                    //throw an exception
                    throw new ClassFoundException();
                }
			    //Class<? extends Primitivable> subClass_ = class_.asSubclass(Primitivable.class);
			    ConstructorInfo constr_ = class_.GetConstructor(new Type[] {typeof(string)});
			    //constr_.setAccessible(constr_.getAnnotation(RwXml.class)!=null);
    //			constr_.setAccessible(true);
			    value = constr_.Invoke(new object[] { value_.Value });
		    /*} catch (IllegalArgumentException e) {
		    } catch (IllegalAccessException e) {
			    e.printStackTrace();*/
		    //}
	    }

	    public override XmlElement serialize(XmlDocument _doc)
        {
            XmlElement node_ = base.serializeMetaInfo(_doc);
            MethodInfo method_ = ConverterMethod.getToStringMethod(getValueClass());
		    if (method_ != null) {
                node_.SetAttribute(VALUE, method_.Invoke(getValue(), new object[] { }).ToString());
            } else {
                node_.SetAttribute(VALUE, getValue().ToString());
            }
		    return node_;
        }

        public override XmlElement serializeWithoutRef(XmlDocument _doc)
        {
            XmlElement node_ = base.serializeMetaInfo(_doc);
            MethodInfo method_ = ConverterMethod.getToStringMethod(getValueClass());
		    if (method_ != null) {
                node_.SetAttribute(VALUE, method_.Invoke(getValue(), new object[] { }).ToString());
            } else {
                node_.SetAttribute(VALUE, getValue().ToString());
            }
		    return node_;
        }

        public override Object getValue()
        {
            return value;
        }
    }
}
