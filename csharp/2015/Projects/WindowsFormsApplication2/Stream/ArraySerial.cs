using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;
using Util;

namespace Stream
{
    class ArraySerial : TemplateSerial
    {
        private const String ELEMENT_TYPE="type";
	    private const String ARRAY="array";

	    private Array array;
        private Map<int?, long?> indexesRef;

        private ArraySerial() { }
        public ArraySerial(Array _array)
        {
            array = _array;
        }

        public ArraySerial(XmlNode _node)
        {
		    if (!_node.Name.Equals(ARRAY)) {
                //throw new ClassFoundException(_node.getNodeName(), ARRAY);
                throw new ClassFoundException();
            }
            XmlNamedNodeMap map_ = _node.Attributes;
            //		if (map_ == null) {
            //			throw new NoAttributeForSerializable(_node.getNodeName());
            //		}
            XmlNode className_ = map_.GetNamedItem(CLASS);
		    if (className_ != null) {
                setClassName(className_.Value);
            }
            XmlNode typeName_ = map_.GetNamedItem(ELEMENT_TYPE);
		    if (typeName_ == null) {
                //throw new NoAttributeForSerializable(ELEMENT_TYPE, _node.getNodeName());
                throw new NoAttributeForSerializable();
            }
            XmlNode field_ = map_.GetNamedItem(FIELD);
		    if (field_ != null) {
                setField(field_.Value);
            }
            XmlNode keyOfMap_ = map_.GetNamedItem(KEY);
		    if (keyOfMap_ != null) {
                setKeyOfMap(true);
            }
            XmlNode ref_ = map_.GetNamedItem(REF);
		    if (ref_ != null) {
                setRef(long.Parse(ref_.Value));
                return;
            }
            XmlNode id_ = map_.GetNamedItem(ID);
		    if (id_ != null) {
                setId(long.Parse(id_.Value));
            }
            Type class_;
            String typeValue_ = typeName_.Value;
		    try {
                class_ = Constants.classForName(typeValue_);
            } catch (Exception e_) {
                throw e_;
                //			if (typeValue_.equalsIgnoreCase(long.class.getName())) {
                //				class_ = long.class;
                //			} else if (typeValue_.equalsIgnoreCase(int.class.getName())) {
                //				class_ = int.class;
                //			} else if (typeValue_.equalsIgnoreCase(short.class.getName())) {
                //				class_ = short.class;
                //			} else if (typeValue_.equalsIgnoreCase(byte.class.getName())) {
                //				class_ = byte.class;
                //			} else if (typeValue_.equalsIgnoreCase(char.class.getName())) {
                //				class_ = char.class;
                //			} else if (typeValue_.equalsIgnoreCase(float.class.getName())) {
                //				class_ = float.class;
                //			} else if (typeValue_.equalsIgnoreCase(double.class.getName())) {
                //				class_ = double.class;
                //			} else if (typeValue_.equalsIgnoreCase(boolean.class.getName())) {
                //				class_ = boolean.class;
                //			} else {
                //				throw e_;
                //			}
            }
            array = Array.CreateInstance(class_, _node.ChildNodes.Count);
        }

        public static ArraySerial newListSerial(XmlNode _node)
        {
		    if (!_node.Name.Equals(ARRAY)) {
                //throw new ClassFoundException(_node.getNodeName(), ARRAY);
                throw new ClassFoundException();
            }
            XmlNamedNodeMap map_ = _node.Attributes;
            //		if (map_ == null) {
            //			throw new NoAttributeForSerializable(_node.getNodeName());
            //		}
            XmlNode className_ = map_.GetNamedItem(CLASS);
            XmlNode typeName_ = map_.GetNamedItem(ELEMENT_TYPE);
		    if (typeName_ == null) {
                //throw new NoAttributeForSerializable(ELEMENT_TYPE, _node.getNodeName());
                throw new NoAttributeForSerializable();
            }
            ArraySerial listSerial_ = new ArraySerial();
            Type class_;
            String typeValue_ = typeName_.Value;
		    try {
			    class_ = Constants.classForName(typeValue_);
		    } catch (Exception e_) {
			    throw e_;
    //			if (typeValue_.equalsIgnoreCase(long.class.getName())) {
    //				class_ = long.class;
    //			} else if (typeValue_.equalsIgnoreCase(int.class.getName())) {
    //				class_ = int.class;
    //			} else if (typeValue_.equalsIgnoreCase(short.class.getName())) {
    //				class_ = short.class;
    //			} else if (typeValue_.equalsIgnoreCase(byte.class.getName())) {
    //				class_ = byte.class;
    //			} else if (typeValue_.equalsIgnoreCase(char.class.getName())) {
    //				class_ = char.class;
    //			} else if (typeValue_.equalsIgnoreCase(float.class.getName())) {
    //				class_ = float.class;
    //			} else if (typeValue_.equalsIgnoreCase(double.class.getName())) {
    //				class_ = double.class;
    //			} else if (typeValue_.equalsIgnoreCase(boolean.class.getName())) {
    //				class_ = boolean.class;
    //			} else {
    //				throw e_;
    //			}
		    }
            listSerial_.array = Array.CreateInstance(class_, _node.ChildNodes.Count);
		    XmlNode field_ = map_.GetNamedItem(FIELD);
		    if (field_ != null) {
			    listSerial_.setField(field_.Value);
		    }
            XmlNode keyOfMap_ = map_.GetNamedItem(KEY);
		    if (keyOfMap_ != null) {
			    listSerial_.setKeyOfMap(true);
		    }
		    if (className_ != null) {
			    listSerial_.setClassName(className_.Value);
		    }
		    return listSerial_;
	    }

	    public override XmlElement serialize(XmlDocument _doc)
        {
            XmlElement node_ = _doc.CreateElement(ARRAY);
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
            string fullName_ = Constants.getTypeFullString(array.GetType());
            fullName_ = fullName_.Substring(0, fullName_.Length - 2);
            node_.SetAttribute(ELEMENT_TYPE, fullName_);
            /*if (array instanceof long[]) {
                node_.setAttribute(ELEMENT_TYPE, long.class.getName());
		        } else if (array instanceof int[]) {
			        node_.setAttribute(ELEMENT_TYPE, int.class.getName());
		        } else if (array instanceof short[]) {
			        node_.setAttribute(ELEMENT_TYPE, short.class.getName());
		        } else if (array instanceof byte[]) {
			        node_.setAttribute(ELEMENT_TYPE, byte.class.getName());
		        } else if (array instanceof float[]) {
			        node_.setAttribute(ELEMENT_TYPE, float.class.getName());
		        } else if (array instanceof double[]) {
			        node_.setAttribute(ELEMENT_TYPE, double.class.getName());
		        } else if (array instanceof char[]) {
			        node_.setAttribute(ELEMENT_TYPE, char.class.getName());
		        } else if (array instanceof boolean[]) {
			        node_.setAttribute(ELEMENT_TYPE, boolean.class.getName());
		        } else {
			        String type_ = array.getClass().getName();
			        if (type_.startsWith(MULT_ARRAY_BEGIN)) {
				        //array with some dimensions
				        node_.setAttribute(ELEMENT_TYPE, type_.substring(1));
			        } else {
				        //array with one dimension
				        node_.setAttribute(ELEMENT_TYPE, type_.substring(2).replace(ARRAY_END, EMPTY_STRING));
			        }
		        }*/
		    return node_;
	    }

        public override XmlElement serializeWithoutRef(XmlDocument _doc)
        {
            XmlElement node_ = _doc.CreateElement(ARRAY);
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
            string fullName_ = Constants.getTypeFullString(array.GetType());
            fullName_ = fullName_.Substring(0, fullName_.Length - 2);
            node_.SetAttribute(ELEMENT_TYPE, fullName_);
            /*if (array instanceof long[]) {
                node_.setAttribute(ELEMENT_TYPE, long.class.getName());
		        } else if (array instanceof int[]) {
			        node_.setAttribute(ELEMENT_TYPE, int.class.getName());
		        } else if (array instanceof short[]) {
			        node_.setAttribute(ELEMENT_TYPE, short.class.getName());
		        } else if (array instanceof byte[]) {
			        node_.setAttribute(ELEMENT_TYPE, byte.class.getName());
		        } else if (array instanceof float[]) {
			        node_.setAttribute(ELEMENT_TYPE, float.class.getName());
		        } else if (array instanceof double[]) {
			        node_.setAttribute(ELEMENT_TYPE, double.class.getName());
		        } else if (array instanceof char[]) {
			        node_.setAttribute(ELEMENT_TYPE, char.class.getName());
		        } else if (array instanceof boolean[]) {
			        node_.setAttribute(ELEMENT_TYPE, boolean.class.getName());
		        } else {
			        String type_ = array.getClass().getName();
			        if (type_.startsWith(MULT_ARRAY_BEGIN)) {
				        //array with some dimensions
				        node_.setAttribute(ELEMENT_TYPE, type_.substring(1));
			        } else {
				        //array with one dimension
				        node_.setAttribute(ELEMENT_TYPE, type_.substring(2).replace(ARRAY_END, EMPTY_STRING));
			        }
		        }*/
		    return node_;
	    }

        public override void appendElementSerialWithoutRef(MyList<ElementsSerial> _elt)
        {
		    int index_ = 0;
		    foreach (ElementsSerial e in _elt) {
                Object o_ = e.getValue();
                //			if (o_ != null) {
                //				if (!classElements.isInstance(o_)) {
                //					throw new IllegalArgumentException();
                //				}
                //			}
                array.SetValue(o_, index_);
                index_++;
            }
        }

        public override void appendElementSerial(MyList<ElementsSerial> _elt)
        {
            indexesRef = new Map<int?,long?>();
		    int i_ = 0;
		    foreach (ElementsSerial e in _elt) {
			    if (e is TemplateSerial) {
				    if (((TemplateSerial)e).getRef() != null) {
					    indexesRef.put(i_, ((TemplateSerial)e).getRef());
				    }
			    }
			    Object o_ = e.getValue();
                //			if (o_ != null) {
                //				if (!classElements.isInstance(o_)) {
                //					throw new IllegalArgumentException();
                //				}
                //			}
                array.SetValue(o_, i_);
			    i_++;
		    }
	    }

        public override void setElementSerial(ElementsSerial _e, ElementsSerial _newE)
        {
            int l_ = array.Length;
	        for (int i = 0; i<l_; i++) {
                if (!indexesRef.contains(i))
                {
                    continue;
                }
                if (!indexesRef.getVal(i).Equals(((TemplateSerial)_e).getRef()))
                {
                    continue;
                }
                Object o_ = _newE.getValue();
                //			if (o_ != null) {
                //				if (!classElements.isInstance(o_)) {
                //					throw new IllegalArgumentException();
                //				}
                //			}
                array.SetValue(o_, i);
            }
        }

        public override Object getValue()
        {
            return array;
        }

        public override Type getValueClass()
        {
            return array.GetType();
        }
    }
}
