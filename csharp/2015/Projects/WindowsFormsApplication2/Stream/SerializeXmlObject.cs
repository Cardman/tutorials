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
    public class SerializeXmlObject
    {
        public static FieldInfo getField(Type _class, String _name)
        {
            foreach (FieldInfo fieldInfo_ in getFields(_class))
            {
                if (fieldInfo_.Name.Equals(_name))
                {
                    return fieldInfo_;
                }
            }
            return null;
        }
        public static List<FieldInfo> getFields(Type _class)
        {
            List<FieldInfo> l_;
            l_ = new List<FieldInfo>();
            foreach (FieldInfo fieldInfo_ in _class.GetFields(BindingFlags.NonPublic |
                         BindingFlags.Instance))
            {
                l_.Add(fieldInfo_);
            }
            foreach (FieldInfo fieldInfo_ in _class.GetFields(BindingFlags.Public |
                         BindingFlags.Instance))
            {
                l_.Add(fieldInfo_);
            }
            return l_;
        }
        public static PropertyInfo getProperty(Type _class, String _name)
        {
            foreach (PropertyInfo fieldInfo_ in getProperties(_class))
            {
                if (fieldInfo_.Name.Equals(_name))
                {
                    return fieldInfo_;
                }
            }
            return null;
        }
        public static List<PropertyInfo> getProperties(Type _class)
        {
            List<PropertyInfo> l_;
            l_ = new List<PropertyInfo>();
            foreach (PropertyInfo fieldInfo_ in _class.GetProperties(BindingFlags.NonPublic |
                         BindingFlags.Instance))
            {
                l_.Add(fieldInfo_);
            }
            foreach (PropertyInfo fieldInfo_ in _class.GetProperties(BindingFlags.Public |
                         BindingFlags.Instance))
            {
                l_.Add(fieldInfo_);
            }
            return l_;
        }
        public static MethodInfo getDirectDeclaredMethod(Type _class, String _name, params Type[] _argsClass)
        {
            StringList traces_ = new StringList();
            MethodInfo method_ = _class.GetMethod(_name, _argsClass);
            if (method_ != null)
            {
                return method_;
            }
            //throw new NoSuchMethodException(traces_.join(RETURN_TAB));
            throw new Exception();

        }
        public static FieldInfo getDirectDeclaredField(Type _class, String _name)
        {
            StringList traces_ = new StringList();
            foreach (FieldInfo f in getFields(_class))
            {
                if (f.Name.Equals(_name))
                {
                    return f;
                }
            }
            //throw new NoSuchMethodException(traces_.join(RETURN_TAB));
            throw new Exception();

        }
        public static MethodInfo getDeclaredMethod(Type _class, String _name, params Type[] _argsClass)
        {
            Type class_ = _class;
            StringList traces_ = new StringList();
		    while (class_ != typeof(Object)) {
                /*foreach (MethodInfo m in class_.GetMethods())
                {
                    Console.WriteLine(m+" "+class_);
                }*/
                //Exception e_ = null;
                /*foreach (MethodInfo m in class_.GetMethods(BindingFlags.NonPublic |
                         BindingFlags.Public | BindingFlags.Instance))
                {
                    
                }*/
                /*foreach (MethodInfo m in class_.GetMethods(BindingFlags.NonPublic |
                         BindingFlags.Public | BindingFlags.Static))
                {
                    Console.WriteLine(m.Name + " " + class_);
                }*/
                MethodInfo method_ = class_.GetMethod(_name, _argsClass);
                if (method_ != null) {
                    return method_;
                }
                /*try {
				    MethodInfo method_ = class_.GetMethod(_name, _argsClass);
				    return method_;
                    } catch (NoSuchMethodException e) {
                        if (class_.BaseType == typeof(Object)) {
                            e_ = e;
                        }
                    } catch (SecurityException e) {
        //				e_ = e;
                        throw e;
                    }
                if (e_ != null) {
                    Exception tr_ = e_;
                    String trace_ = tr_.ToString() + RETURN_TAB + _class.getName();
				    foreach (StackTraceElement s in e_.getStackTrace()) {
					    trace_ += RETURN_TAB + s;
				    }
				    traces_.Add(trace_);
			    }*/
                class_ = class_.BaseType;
		    }
		    //throw new NoSuchMethodException(traces_.join(RETURN_TAB));
            throw new Exception();

        }
        public static FieldInfo getDeclaredField(Type _class, String _name)
        {
            Type class_ = _class;
            StringList traces_ = new StringList();
            while (class_ != typeof(Object))
            {
                /*foreach (MethodInfo m in class_.GetMethods())
                {
                    Console.WriteLine(m+" "+class_);
                }*/
                //Exception e_ = null;
                /*foreach (MethodInfo m in class_.GetMethods(BindingFlags.NonPublic |
                         BindingFlags.Public | BindingFlags.Instance))
                {
                    
                }*/
                /*foreach (MethodInfo m in class_.GetMethods(BindingFlags.NonPublic |
                         BindingFlags.Public | BindingFlags.Static))
                {
                    Console.WriteLine(m.Name + " " + class_);
                }*/
                foreach (FieldInfo f in getFields(_class))
                {
                    if (f.Name.Equals(_name))
                    {
                        return f;
                    }
                }
                /*MethodInfo method_ = class_.GetMethod(_name, _argsClass);
                if (method_ != null)
                {
                    return method_;
                }*/
                /*try {
				    MethodInfo method_ = class_.GetMethod(_name, _argsClass);
				    return method_;
                    } catch (NoSuchMethodException e) {
                        if (class_.BaseType == typeof(Object)) {
                            e_ = e;
                        }
                    } catch (SecurityException e) {
        //				e_ = e;
                        throw e;
                    }
                if (e_ != null) {
                    Exception tr_ = e_;
                    String trace_ = tr_.ToString() + RETURN_TAB + _class.getName();
				    foreach (StackTraceElement s in e_.getStackTrace()) {
					    trace_ += RETURN_TAB + s;
				    }
				    traces_.Add(trace_);
			    }*/
                class_ = class_.BaseType;
            }
            //throw new NoSuchMethodException(traces_.join(RETURN_TAB));
            throw new Exception();

        }
        public static string toXmlString(Object _serialisable)
        {
            XmlDocument doc_ = getSource(_serialisable);
            return XmlParser.toXml(doc_);
        }
        public static XmlDocument getSource(Object _serialisable)
        {
            //XmlDocument document_ = DocumentBuilderFactory.newInstance().newDocumentBuilder().newDocument();
            XmlDocument document_ = new XmlDocument();
            try {
                ElementsSerial primitive_;
                primitive_ = CurrentSerializableElements.createPrimitive(_serialisable);
                if (primitive_ != null)
                {
                    XmlElement elt_ = primitive_.serializeWithoutRef(document_);
                    document_.AppendChild(elt_);
                    return document_;
                }
            } catch (Exception) {
            }
            //XmlNode firstNode_ = document_.CreateElement(_serialisable.GetType().FullName);
            //XmlNode firstNode_ = document_.CreateElement(_serialisable.GetType().FullName.Split(new string[] { "`" }, StringSplitOptions.None)[0]);
            ObjectSerial base_ = new ObjectSerial(_serialisable);

            //XmlNode firstNode_ = document_.CreateElement(ElementsSerial.getTypeName(_serialisable));
            XmlNode firstNode_ = base_.serializeWithoutRef(document_);
            document_.AppendChild(firstNode_);
            MyList<XmlNode> currentNodesToBeCompleted_ = new MyList<XmlNode>();
            currentNodesToBeCompleted_.Add(firstNode_);

            CurrentSerializableElements currentThread_ = new CurrentSerializableElements(base_);

			currentThread_.initializeObjectsWithoutIdRef();
            MyList<TemplateSerial> currentSerializableElements_ = new MyList<TemplateSerial>();
            currentSerializableElements_.Add(base_);
            MyList<XmlNode> newNodesToBeCompleted_ = new MyList<XmlNode>();
            MyList<TemplateSerial> newSerializableElements_ = new MyList<TemplateSerial>();
            bool modif_ = true;
			while (modif_) {
				modif_ = false;
				newSerializableElements_ = new MyList<TemplateSerial>();
				newNodesToBeCompleted_ = new MyList<XmlNode>();
				int len_;
len_ = currentNodesToBeCompleted_.size();
				for (int i = List.FIRST_INDEX; i<len_; i++) {
					XmlNode currentNode_ = currentNodesToBeCompleted_.get(i);
                    TemplateSerial currentSerializable_ = currentSerializableElements_.get(i);
                    List<ElementsSerial> elts_ = currentThread_.getComponentComposite(currentSerializable_);
					foreach (ElementsSerial e in elts_) {
                        XmlNode newNode_ = e.serializeWithoutRef(document_);
						if (e is TemplateSerial && !(e is EnumSerial)) {
							TemplateSerial t_ = (TemplateSerial)e;
							if (t_.getRef() == null) {
								newNodesToBeCompleted_.Add(newNode_);
								newSerializableElements_.Add(t_);
							}
						}
						currentNode_.AppendChild(newNode_);
					}
				}
				if (!newSerializableElements_.isEmpty()) {
					currentNodesToBeCompleted_ = new MyList<XmlNode>(newNodesToBeCompleted_);
					currentSerializableElements_ = new MyList<TemplateSerial>(newSerializableElements_);
					modif_ = true;
				}
			}
		    return document_;
	    }
        public static Object fromXmlStringObject(String _xmlString)
        {

            XmlElement root_ = XmlParser.documentElement(XmlParser.parseSax(_xmlString));
		try {
                ElementsSerial elt_ = createPrimitive(root_);
                if (elt_ != null)
                {
                    return elt_.getValue();
                }
            } catch (Exception) {
            }
            MyList<XmlNode> currentNodesToBeRead_ = new MyList<XmlNode>();
		    currentNodesToBeRead_.Add(root_);
            MyList<TemplateSerial> currentSerializableElements_ = new MyList<TemplateSerial>();
        ObjectSerial rootElement_;
            rootElement_ = ObjectSerial.newSerial(root_, false);
            currentSerializableElements_.Add(rootElement_);
            MyList<XmlNode> newNodesToBeRead_ = new MyList<XmlNode>();
            MyList<TemplateSerial> newSerializableElements_ = new MyList<TemplateSerial>();
            MyList<ObjectSerial> notEmptyMaps_ = new MyList<ObjectSerial>();
            bool modif_ = true;
            while (modif_)
            {
                modif_ = false;
                newSerializableElements_ = new MyList<TemplateSerial>();
                newNodesToBeRead_ = new MyList<XmlNode>();
                int len_;
                len_ = currentNodesToBeRead_.size();
                for (int i = List.FIRST_INDEX; i < len_; i++)
                {
                    XmlNode currentNode_ = currentNodesToBeRead_.get(i);
                    TemplateSerial composite_ = currentSerializableElements_.get(i);
                    bool isTreeMap_ = false;
                    bool containsTree_ = false;
                    foreach (XmlNode nCh_ in XmlParser.childrenNodes(currentNode_))
                    {
                        if (!(nCh_ is XmlElement)) {
                            continue;
                        }
                        containsTree_ = nCh_.Attributes.GetNamedItem(TemplateSerial.COMPARATOR) != null;
                        if (containsTree_)
                        {
                            break;
                        }
                    }
                    if (containsTree_)
                    {
                        isTreeMap_ = true;
                    }
                    MyList<ElementsSerial> elt_ = new MyList<ElementsSerial>();
                    foreach (XmlNode n in XmlParser.childrenNodes(currentNode_))
                    {
                        if (!(n is XmlElement)) {
                            continue;
                        }
                        try
                        {
                            ArraySerial serialArray_ = ArraySerial.newListSerial(n);
                            elt_.Add(serialArray_);
                            newSerializableElements_.Add(serialArray_);
                            newNodesToBeRead_.Add(n);
                            continue;
                        }
                        catch (NoAttributeForSerializable e_)
                        {
                            throw e_;
                        }
                        catch (ClassFoundException)
                        {
                        }
                        try
                        {
                            ElementsSerial primitive_ = createPrimitive(n);
                            if (primitive_ == null)
                            {
                                throw new NullReferenceException();
                            }
                            elt_.Add(primitive_);
                            continue;
                        }
                        catch (NoAttributeForSerializable e_)
                        {
                            throw e_;
                        }
                        catch (InexistingValueForEnum e_)
                        {
                            throw e_;
                        }
                        catch (FormatException e_)
                        {
                            throw e_;
                        }
                        /*catch (InvocationTargetException e_)
                        {
                            throw e_;
                        }
                        catch (InstantiationException e_)
                        {
                            throw e_;
                        }
                        catch (SecurityException e_)
                        {
                            throw e_;
                        }
                        catch (ClassNotFoundException e_)
                        {
                            throw e_;
                        }*/
                        catch (NullReferenceException)
                        {
                        }
                        ComparatorSerial cmp_ = getCmpSerial(n, isTreeMap_, composite_);
                        if (cmp_ != null)
                        {
                            elt_.Add(cmp_);
                            newSerializableElements_.Add(cmp_);
                            newNodesToBeRead_.Add(n);
                            continue;
                        }
                        ObjectSerial serial_ = ObjectSerial.newSerial(n, true);
                        elt_.Add(serial_);
                        newSerializableElements_.Add(serial_);
                        newNodesToBeRead_.Add(n);
                    }
                    composite_.appendElementSerialWithoutRef(elt_);
					if (composite_ is ObjectSerial) {
						if (!((ObjectSerial) composite_).mapIsEmpty()) {
							notEmptyMaps_.Add((ObjectSerial) composite_);
						}
                    }
				}
				if (!newSerializableElements_.isEmpty()) {
					currentNodesToBeRead_ = new MyList<XmlNode>(newNodesToBeRead_);
					currentSerializableElements_ = new MyList<TemplateSerial>(newSerializableElements_);
					modif_ = true;
				}
			}
			List<ObjectSerial> filledMaps_ = new MyList<ObjectSerial>();
            List<ObjectSerial> fillableMaps_ = new MyList<ObjectSerial>();
			/*foreach (ObjectSerial m in notEmptyMaps_) {
				if (m.keysAllDifferent()) {
					fillableMaps_.Add(m);
				}
			}
			while (true) {
				for (MayBeMap m : fillableMaps_) {
					m.setComponents();
					filledMaps_.add(m);
				}
				fillableMaps_.clear();
				for (MayBeMap m : notEmptyMaps_) {
					if (!m.keysAllDifferent()) {
						continue;
					}
					if (filledMaps_.containsObj(m)) {
						continue;
					}
					fillableMaps_.add(m);
				}
				if (fillableMaps_.isEmpty()) {
					break;
				}
			}
			for (MayBeMap m : notEmptyMaps_) {
				if (!filledMaps_.containsObj(m)) {
					m.setComponents();
				}
			}*/
		    return rootElement_.getValue();
	    }

	    private static ElementsSerial createPrimitive(XmlNode _node)

        {
		    try {
			    return new NullSerial(_node);
		    } catch (ClassFoundException) {
		    }
            try
            {
                return new NumberSerial<int>(_node);
            }
            catch (NoAttributeForSerializable e_)
            {
                throw e_;
            }
            catch (FormatException e_)
            {
                throw e_;
            }
            catch (ClassFoundException)
            {
            }
            try
            {
                return new NumberSerial<long>(_node);
            }
            catch (NoAttributeForSerializable e_)
            {
                throw e_;
            }
            catch (FormatException e_)
            {
                throw e_;
            }
            catch (ClassFoundException)
            {
            }
        try {
			return new StringSerial(_node);
		} catch (NoAttributeForSerializable e_) {
			throw e_;
		} catch (ClassFoundException) {
		}
		try {
			return new CharacterSerial(_node);
		} catch (NoAttributeForSerializable e_) {
			throw e_;
		} catch (ClassFoundException) {
		}
		try {
			return new BooleanSerial(_node);
		} catch (NoAttributeForSerializable e_) {
			throw e_;
		} catch (ClassFoundException) {
		}
		try {
			return new StringObjectSerial(_node);
                /*} catch (SecurityException e) {
                    throw e;*/
                /*} catch (InvocationTargetException e) {
                    throw e;
                } catch (InstantiationException e) {
                    throw e;
                } catch (ClassNotFoundException e) {
                    throw e;*/
                /*} catch (NoSuchMethodException e) {
                    e.printStackTrace();
                } catch (ClassCastException e) {*/
            }
            catch (ClassFoundException) { }
        catch (NoValueException) {
		}
		try {
			return new EnumSerial(_node);
		} catch (ClassFoundException) {
		} catch (NoAttributeForSerializable e_) {
			throw e_;
		} catch (InexistingValueForEnum e_) {
			throw e_;
                /*} catch (ClassNotFoundException e_) {
                    throw e_;
                } catch (ClassCastException e_) {*/
            }
            catch (NullReferenceException) {
			//e_.printStackTrace();
		}
		return null;
	}

	    private static ComparatorSerial getCmpSerial(XmlNode _node,
                bool _isTreeMap, TemplateSerial _composite)
        {
		    if (!_isTreeMap) {
                return null;
            }
            XmlNamedNodeMap attributes_ = _node.Attributes;
    //		if (attributes_ == null) {
    //			return null;
    //		}
		    if (attributes_.GetNamedItem(TemplateSerial.COMPARATOR) == null) {
                return null;
            }
		    if (_composite is ObjectSerial) {
                //			return ((MayBeMap) _composite).getCmpSerial();
                return new ComparatorSerial(_node);
            }
		    return null;
        }
    }
}
