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
    class ObjectSerial : TemplateSerial
    {
        private const int NO_DUPLICATE = 1;

        private const String ENUM = "enum";
        private const String ADD = "add";
        private const String SET = "set";
        private const String PUT = "put";
        private const String TYPES = "types";

        private Object value;
        private MyList<Object> keys;
        private MyList<Object> values;
        private Map<int?, long?> indexesRef;
        private Map<int?, long?> keysIndexesRef;
        private Map<int?, long?> valuesIndexesRef;
        private Type[] types;
        private ComparatorSerial cmpSerial;

        private ObjectSerial() { }

        public ObjectSerial(Object _value)
        {
            value = _value;
            types = value.GetType().GetGenericArguments();
        }

        public ObjectSerial(XmlNode _node, bool _requiredClass) {
		    XmlNamedNodeMap map_ = _node.Attributes;
		    if(_requiredClass) {
                XmlNode className_ = map_.GetNamedItem(CLASS);
			    if (className_ != null) {

                    setClassName(className_.Value);
			    }
		    }
            XmlNode field_ = map_.GetNamedItem(FIELD);
		    if (field_ != null) {

                setField(field_.Value);
		    }
            XmlNode keyOfMap_ = map_.GetNamedItem(KEY);
		    if (keyOfMap_ != null) {

                setKeyOfMap(true);
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
            ConstructorInfo constr_ = class_.GetConstructor(new Type[] { });
            value = constr_.Invoke(new object[] { });
            /*try {
			   Type class_ = Constants.classForName(_node.Name);
                Constructor<?> constr_ = class_.getDeclaredConstructor();
    //			constr_.setAccessible(class_.getAnnotation(RwXml.class)!=null);
    //constr_.setAccessible(constr_.getAnnotation(RwXml.class)!=null);
			    value = constr_.newInstance();
		    } catch (IllegalArgumentException e) {
		    } catch (IllegalAccessException e) {
			    e.printStackTrace();
		    }*/
	    }

	    public static ObjectSerial newSerial(XmlNode _node, bool _requiredClass)
        {
            XmlNamedNodeMap map_ = _node.Attributes;
            ObjectSerial serial_ = new ObjectSerial();
		    if(_requiredClass) {
                XmlNode className_ = map_.GetNamedItem(CLASS);
			    if (className_ != null) {
				    serial_.setClassName(className_.Value);
			    }
		    }
            XmlNode types_ = map_.GetNamedItem(TYPES);
            string typesStr_ = "";
            if (types_ != null)
            {
                typesStr_ = types_.Value;
            }
            Type class_ = Constants.classForName(_node.Name, typesStr_);
            serial_.types = class_.GetGenericArguments();
            ConstructorInfo constr_ = class_.GetConstructor(new Type[] { });
            //		constr_.setAccessible(class_.getAnnotation(RwXml.class)!=null);
            //constr_.setAccessible(constr_.getAnnotation(RwXml.class)!=null);
            XmlNode field_ = map_.GetNamedItem(FIELD);
		    if (field_ != null) {
			    serial_.setField(field_.Value);
		    }
            XmlNode keyOfMap_ = map_.GetNamedItem(KEY);
		    if (keyOfMap_ != null) {
			    serial_.setKeyOfMap(true);
		    }
            try {
			    serial_.value = constr_.Invoke(new object[] { });
		    //} catch (IllegalArgumentException e) {
		    //} catch (IllegalAccessException e) {
			 //   e.printStackTrace();
		    /*} catch (InstantiationException e) {
			    throw e;*/
		    } catch (TargetInvocationException e) {
			    throw e;
		    }
		    return serial_;
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
            /*if (value instanceof EnumMap) {
                node_.setAttribute(ENUM, ((EnumMap <?,?>)value).getLocalClass().getName());
            }*/
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
            /*if (value instanceof EnumMap) {
                node_.setAttribute(ENUM, ((EnumMap <?,?>)value).getLocalClass().getName());
            }*/
            return node_;
        }

        public override Type getValueClass()
        {
            return value.GetType();
        }

        public override Object getValue()
        {
            return value;
        }

        public ComparatorSerial getCmpSerial()
        {
            return cmpSerial;
        }

        public override void appendElementSerial(MyList<ElementsSerial> _elt)
        {
            indexesRef = new Map<int?, long?>();
		    int i_ = 0;
            keys = new MyList<object>();
		    keysIndexesRef = new Map<int?, long?>();
		    int iKey_ = 0;
            values = new MyList<object>();
		    valuesIndexesRef = new Map<int?, long?>();
		    int iValue_ = 0;
            MethodInfo ADD_METHOD = value.GetType().GetMethod("Add");
		    foreach (ElementsSerial e in _elt) {
			    if (e is ComparatorSerial) {
				    continue;
			    }
                if (typeof(IEnumerable).FullName.ToLower().Equals(e.getClassName().ToLower()))
                {
                    if (e is TemplateSerial)
                    {
                        if (((TemplateSerial)e).getRef() != null)
                        {
                            indexesRef.put(i_, ((TemplateSerial)e).getRef());
                        }
                    }
                    ADD_METHOD.Invoke(value, new object[] { e.getValue() });
                    i_++;
                    continue;
                }
		    }
		    foreach (ElementsSerial e in _elt) {
			    if (e is ComparatorSerial) {
				    cmpSerial = (ComparatorSerial) e;
				    continue;
			    }
                //ListableKey
                //
                if (!typeof(ListableKey).FullName.ToLower().Equals(e.getClassName().ToLower()))
                {
                    continue;
                }
                /*if (!e.getClassName().equalsIgnoreCase(Map.class.getName())) {
				    continue;
			    }*/
			    if (!e.isKeyOfMap()) {
				    if (e is TemplateSerial) {
					    if (((TemplateSerial)e).getRef() != null) {
						    valuesIndexesRef.put(iValue_, ((TemplateSerial)e).getRef());
					    }
				    }
				    values.Add(e.getValue());
				    iValue_ ++;
			    } else {
				    if (e is TemplateSerial) {
					    if (((TemplateSerial)e).getRef() != null) {
						    keysIndexesRef.put(iKey_, ((TemplateSerial)e).getRef());
					    }
				    }
				    keys.Add(e.getValue());
				    iKey_ ++;
			    }
		    }
		    foreach (ElementsSerial e in _elt) {
                if (e is ComparatorSerial) {
				    continue;
			    }
                Type t_ = typeof(IEnumerable);
                string fullType_ = Constants.getTypeFullString(t_);
                if (fullType_.ToLower().Equals(e.getClassName().ToLower()))
                {
                    continue;
                }
                t_ = typeof(ListableKey);
                fullType_ = Constants.getTypeFullString(t_);
                if (fullType_.ToLower().Equals(e.getClassName().ToLower()))
                {
                    continue;
                }
                /*if (e.getClassName().equalsIgnoreCase(List.class.getName())) {
				    continue;
			    }
			    if (e.getClassName().equalsIgnoreCase(Map.class.getName())) {
				    continue;
			    }*/
                string str_ = e.getClassName();
                Type class_;
                if (str_.Contains(SPECIAL_SEP))
                {
                    string types_ = str_.Substring(str_.IndexOf(SPECIAL_SEP));
                    class_ = Constants.classForName(str_, types_);
                } else
                {
                    class_ = Constants.classForName(str_);
                }
                if (!class_.IsInstanceOfType(value)) {
				    continue;
			    }
			    //FieldInfo field_ = class_.GetField(e.getField(), BindingFlags.NonPublic |
                //         BindingFlags.Instance);
                FieldInfo field_ = SerializeXmlObject.getField(class_, e.getField());
                /*if (!SerializeXmlObject.isUpdateFinalFields()) {
				    if (Modifier.isFinal(field_.getModifiers())) {
					    continue;
				    }
			    }*/
                /*if (Modifier.isStatic(field_.getModifiers())) {
				    continue;
			    }*/
                //field_.setAccessible(class_.getAnnotation(RwXml.class)!=null);
                field_.SetValue(value, e.getValue());
		    }
	    }
        public override void appendElementSerialWithoutRef(MyList<ElementsSerial> _elt)
        {
            keys = new MyList<object>();
		    values = new MyList<object>();
            MethodInfo ADD_METHOD = value.GetType().GetMethod("Add", types);
            foreach (ElementsSerial e in _elt) {
                if (e is ComparatorSerial) {
				    continue;
			    }
                Type t_ = typeof(IEnumerable);
                string fullType_ = Constants.getTypeFullString(t_);
                if (fullType_.ToLower().Equals(e.getClassName().ToLower()))
                {
                    object obj_ = e.getValue();
                    /*if (obj_ != null)
                    {
                        if (obj_.GetType().IsPrimitive)
                        {
                            if (types.ElementAt(0).IsEnum)
                            {
                                throw new ArgumentException();
                                //Console.WriteLine("%%%"+ obj_);
                            }
                        }
                        if (types.ElementAt(0).IsPrimitive)
                        {
                            if (obj_.GetType().IsEnum)
                            {
                                throw new ArgumentException();
                                //Console.WriteLine("%%%"+ obj_);
                            }
                        }
                    }*/
                    ADD_METHOD.Invoke(value, new object[] { obj_ });
                    continue;
                }
                /*if (typeof(IEnumerable).FullName.ToLower().Equals(e.getClassName().ToLower()))
                {
				    ADD_METHOD.Invoke(value, new object[] { e.getValue() });
				    continue;
			    }*/
		    }
            foreach (ElementsSerial e in _elt)
            {
                if (e is ComparatorSerial) {
				    cmpSerial = (ComparatorSerial) e;
				    continue;
			    }
                Type t_ = typeof(ListableKey);
                string fullType_ = Constants.getTypeFullString(t_);
                if (!fullType_.ToLower().Equals(e.getClassName().ToLower()))
                {
                    continue;
                }
                object obj_ = e.getValue();
               
                /*if (!typeof(ListableKey).FullName.ToLower().Equals(e.getClassName().ToLower()))
                {
                    continue;
                }*/
                /*if (!e.getClassName().equalsIgnoreCase(Map.class.getName())) {
				continue;
			    }*/
                if (!e.isKeyOfMap()) {
                    /*if (obj_ != null)
                    {
                        if (obj_.GetType().IsPrimitive)
                        {
                            if (types.ElementAt(1).IsEnum)
                            {
                                throw new ArgumentException();
                                //Console.WriteLine("%%%"+ obj_);
                            }
                        }
                        if (types.ElementAt(1).IsPrimitive)
                        {
                            if (obj_.GetType().IsEnum)
                            {
                                throw new ArgumentException();
                                //Console.WriteLine("%%%"+ obj_);
                            }
                        }
                    }*/
                    values.Add(e.getValue());
			    } else {
                    /*if (obj_ != null)
                    {
                        if (obj_.GetType().IsPrimitive)
                        {
                            if (types.ElementAt(0).IsEnum)
                            {
                                throw new ArgumentException();
                                //Console.WriteLine("%%%"+ obj_);
                            }
                        }
                        if (types.ElementAt(0).IsPrimitive)
                        {
                            if (obj_.GetType().IsEnum)
                            {
                                throw new ArgumentException();
                                //Console.WriteLine("%%%"+ obj_);
                            }
                        }
                    }*/
                    keys.Add(e.getValue());
			    }
		    }
            foreach (ElementsSerial e in _elt)
            {
                if (e is ComparatorSerial) {
				    continue;
			    }
                Type t_ = typeof(IEnumerable);
                string fullType_ = Constants.getTypeFullString(t_);
                //Console.WriteLine(e.getClassName() + "%%" + fullType_);
                /*Type t2_ = typeof(IEnumerable);
                string str2_ = ElementsSerial.getType(t_);
                string assName2_ = t_.Assembly.GetName().Name;
                string fullType2_ = assName_ + ".." + str_;*/
                if (fullType_.ToLower().Equals(e.getClassName().ToLower()))
                {
                    continue;
                }
                t_ = typeof(ListableKey);
                fullType_ = Constants.getTypeFullString(t_);
                if (fullType_.ToLower().Equals(e.getClassName().ToLower()))
                {
                    continue;
                }
                /*if (typeof(IEnumerable).FullName.ToLower().Equals(e.getClassName().ToLower()))
                {
                    continue;
                }
                if (typeof(ListableKey).FullName.ToLower().Equals(e.getClassName().ToLower()))
                {
                    continue;
                }*/
                /*if (e.getClassName().equalsIgnoreCase(List.class.getName())) {
				    continue;
			    }
			    if (e.getClassName().equalsIgnoreCase(Map.class.getName())) {
				    continue;
			    }*/
			    //Type class_ = Constants.classForName(e.getClassName());
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
                if (!class_.IsInstanceOfType(value)) {
				    continue;
			    }
			    /*FieldInfo field_ = class_.GetField(e.getField(), BindingFlags.NonPublic |
                         BindingFlags.Instance);*/
                FieldInfo field_ = SerializeXmlObject.getField(class_, e.getField());
                object obj_ = e.getValue();
                /*if (obj_ != null)
                {
                    if (obj_.GetType().IsPrimitive)
                    {
                        if (field_.FieldType.IsEnum)
                        {
                            throw new ArgumentException();
                            //Console.WriteLine("%%%"+ obj_);
                        }
                    }
                    if (obj_.GetType().IsEnum)
                    {
                        if (field_.FieldType.IsPrimitive)
                        {
                            throw new ArgumentException();
                            //Console.WriteLine("%%%"+ obj_);
                        }
                    }
                }*/
                /*if (!SerializeXmlObject.isUpdateFinalFields()) {
				    if (Modifier.isFinal(field_.getModifiers())) {
					    continue;
				    }
			    }
			    if (Modifier.isStatic(field_.getModifiers())) {
				    continue;
			    }*/
                //field_.setAccessible(class_.getAnnotation(RwXml.class)!=null);

                field_.SetValue(value, e.getValue());
		    }
            if (value is ListableKey && !(value is IComparableKeys))
            {
                FieldInfo LIST_FIELD = value.GetType().GetField("list", BindingFlags.NonPublic |
                         BindingFlags.Instance);
                Object list_ = LIST_FIELD.GetValue(value);
                ADD_METHOD = list_.GetType().GetMethod("Add");
                Type treeMapTypeGene_ = typeof(Map<,>);
                //string treeMapType_ = treeMapTypeGene_.Assembly.GetName().Name + ".." + treeMapTypeGene_.Namespace + "." + treeMapTypeGene_.Name;
                string treeMapType_ = treeMapTypeGene_.Assembly.GetName().Name + "." + treeMapTypeGene_.Namespace + "." + treeMapTypeGene_.Name;
                treeMapType_ = treeMapType_.Substring(0, treeMapType_.IndexOf(ElementsSerial.SPECIAL_SEP) + 1);
                Type curType_ = value.GetType();
                while (true)
                {
                    if (curType_ == null)
                    {
                        break;
                    }
                    if (Constants.getTypeFullString(curType_).StartsWith(treeMapType_))
                    {
                        break;
                    }
                    curType_ = curType_.BaseType;
                }
                Type[] args_ = curType_.GetGenericArguments();
                Type genericType_ = typeof(Entry<,>).MakeGenericType(args_);
                ConstructorInfo ctor_ = genericType_.GetConstructor(args_);
                int len_ = keys.size();
                for (int i = 0; i < len_; i++)
                {
                    //PUT_METHOD.invoke(value, keys.get(i),values.get(i));
                    object e_ = ctor_.Invoke(new object[] { keys.get(i), values.get(i) });
                    ADD_METHOD.Invoke(list_, new object[] { e_ });
                }
                keys.Clear();
                values.Clear();
            }
            if (value is IComparableKeys)
            {
                Type treeMapTypeGene_ = typeof(TreeMap<,>);
                //string treeMapType_ = treeMapTypeGene_.Assembly.GetName().Name + ".." + treeMapTypeGene_.Namespace + "." + treeMapTypeGene_.Name;
                string treeMapType_ = treeMapTypeGene_.Assembly.GetName().Name + "." + treeMapTypeGene_.Namespace + "." + treeMapTypeGene_.Name;
                treeMapType_ = treeMapType_.Substring(0, treeMapType_.IndexOf(ElementsSerial.SPECIAL_SEP) + 1);
                Type curType_ = value.GetType();
                while (true)
                {
                    if (curType_ == null)
                    {
                        break;
                    }
                    if (Constants.getTypeFullString(curType_).StartsWith(treeMapType_))
                    {
                        break;
                    }
                    curType_ = curType_.BaseType;
                }
                Type[] args_ = curType_.GetGenericArguments();
                if (cmpSerial != null)
                {
                    Type dicoMapType_;// = typeof(SortedDictionary<,>);
                    Type speTreeMapType_;// = dicoMapType_.MakeGenericType(args_);
                    /*foreach (PropertyInfo p in SerializeXmlObject.getProperties(speTreeMapType_))
                    {
                        Console.WriteLine(p.Name);
                    }*/
                    //PropertyInfo p_ = SerializeXmlObject.getProperty(speTreeMapType_, COMPARATOR);
                    //f_.setAccessible(true);
                    //Console.WriteLine(cmpSerial.getValue().GetType());
                    //Console.WriteLine(p_.PropertyType);
                    //p_.GetSetMethod(true)
                    //p_.GetSetMethod(true).Invoke(value, new object[] { cmpSerial.getValue() });
                    //p_.SetValue(value, cmpSerial.getValue());
                    dicoMapType_ = typeof(TreeMap<,>);
                    speTreeMapType_ = dicoMapType_.MakeGenericType(args_);
                    FieldInfo f_ = SerializeXmlObject.getField(speTreeMapType_, "comparator");
                    //f_.setAccessible(true);
                    f_.SetValue(value, cmpSerial.getValue());
                }
                MethodInfo m_ = curType_.GetMethod("put", args_);
                int len_ = keys.size();
                for (int i = 0; i < len_; i++)
                {
                    m_.Invoke(value, new object[] { keys.get(i), values.get(i) });
                }
                keys.Clear();
                values.Clear();
            }
		    /*if (PairUtil.isMap(value)) {
			
		    }*/
	    }
        public override void setElementSerial(ElementsSerial _e, ElementsSerial _newE)
        {
		   /* if(value instanceof List) {
                int len_ = ((List <?>)value).size();
                for (int i = Constants.getFirstIndex(); i < len_; i++)
                {
                    if (!indexesRef.containsKey(i))
                    {
                        continue;
                    }
                    if (!indexesRef.get(i).equals(((TemplateSerial)_e).getRef()))
                    {
                        continue;
                    }
                    SET_METHOD.invoke(value, i, _newE.getValue());
                }
            }
		if(value instanceof Map) {
        int len_ = keys.size();
        for (int i = Constants.getFirstIndex(); i < len_; i++)
        {
            if (!keysIndexesRef.containsKey(i))
            {
                continue;
            }
            if (!keysIndexesRef.get(i).equals(((TemplateSerial)_e).getRef()))
            {
                continue;
            }
            keys.set(i, _newE.getValue());
        }
        for (int i = Constants.getFirstIndex(); i < len_; i++)
        {
            if (!valuesIndexesRef.containsKey(i))
            {
                continue;
            }
            if (!valuesIndexesRef.get(i).equals(((TemplateSerial)_e).getRef()))
            {
                continue;
            }
            values.set(i, _newE.getValue());
        }
    }
    Class<?> class_ = Constants.classForName(_e.getClassName());
		if (!class_.isInstance(value)) {
        return;
    }
		if (_e.getField() == null) {
        return;
    }
    Field field_;
		try {
        field_ = class_.getDeclaredField(_e.getField());
    } catch (NoSuchFieldException exception) {
        return;
    }
		if (!SerializeXmlObject.isUpdateFinalFields()) {
        if (Modifier.isFinal(field_.getModifiers()))
        {
            return;
        }
    }
		if (Modifier.isStatic(field_.getModifiers())) {
        return;
    }
    field_.setAccessible(class_.getAnnotation(RwXml.class)!=null);
		field_.set(value, _newE.getValue());*/
	}
        public void setComponents()
{
            if (cmpSerial != null) {
                Type treeMapType_ = typeof(Dictionary<,>);
                Type speTreeMapType_ = treeMapType_.MakeGenericType(types);
                PropertyInfo f_ = SerializeXmlObject.getProperty(speTreeMapType_, COMPARATOR);
                //f_.setAccessible(true);
                f_.SetValue(value, cmpSerial.getValue());
            }
            MethodInfo PUT_METHOD = value.GetType().GetMethod("put");
            int len_ = keys.size();
		    for (int i = 0; i<len_; i++) {
			    PUT_METHOD.Invoke(value, new object[] { keys.get(i), values.get(i) });
		    }
	}

    /*public bool keysAllDifferent()
    {
        foreach (Object o in keys)
        {
            if (Collections.frequency(keys, o) > NO_DUPLICATE)
            {
                return false;
            }
        }
        return true;
    }*/

    public bool mapIsEmpty()
{
    return keys.isEmpty();
}
    }
}
