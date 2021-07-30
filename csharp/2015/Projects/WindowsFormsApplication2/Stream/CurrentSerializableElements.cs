using ReflectionCore;
using Stream;
using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using Util;

namespace Stream
{
    class CurrentSerializableElements
    {
        private MyList<TemplateSerial> allComposites = new MyList<TemplateSerial>();
        private MyList<TemplateSerial> news = new MyList<TemplateSerial>();
        private MyList<TemplateSerial> currents = new MyList<TemplateSerial>();
        private MyList<ElementsSerial> allImplicitComparators = new MyList<ElementsSerial>();
        private Map<TemplateSerial, MyList<ElementsSerial>> componentComposite = new Map<TemplateSerial, MyList<ElementsSerial>>();
        private MyList<ElementsSerial> components = new MyList<ElementsSerial>();
        private long id;

        public CurrentSerializableElements(ObjectSerial _base)
        {
            currents.Add(_base);
        }
        public void initializeObjectsWithoutIdRef()
        {
            bool modif_ = true;
		    while(modif_) {
                modif_ = false;
                setNews(new MyList<TemplateSerial>());
                foreach (TemplateSerial e in getCurrents())
                {
                    setComponents(new MyList<ElementsSerial>());
                    Object currentValue_ = e.getValue();
                    if (currentValue_ is IEnumerable && !currentValue_.GetType().IsArray)
                    {
                        /*bool treeMap_ = false;
                        Type treeMapTypeGene_ = typeof(TreeMap<,>);
                        string treeMapType_ = treeMapTypeGene_.Assembly.GetName().Name+".."+ treeMapTypeGene_.Namespace+"."+ treeMapTypeGene_.Name;
                        treeMapType_ = treeMapType_.Substring(0, treeMapType_.IndexOf(ElementsSerial.SPECIAL_SEP) + 1);
                        Type curType_ = currentValue_.GetType();
                        while (true)
                        {
                            if (curType_ == null)
                            {
                                break;
                            }
                            if (Constants.getTypeFullString(curType_).StartsWith(treeMapType_))
                            {
                                treeMap_ = true;
                                break;
                            }
                            curType_ = curType_.BaseType;
                        }
                        if (treeMap_)
                        {
                            Type[] args_ = curType_.GetGenericArguments();
                            Type pairType_ = typeof(KeyValuePair<,>).MakeGenericType(args_);
                            foreach (Object o in (IEnumerable)currentValue_)
                            {
                                if (pairType_.IsInstanceOfType(o))
                                {
                                    continue;
                                }
                                addElementInListWithoutIdRef(o);
                            }
                        } else
                        {
                            foreach (Object o in (IEnumerable)currentValue_)
                            {
                                addElementInListWithoutIdRef(o);
                            }
                        }*/
                        foreach (Object o in (IEnumerable)currentValue_)
                        {
                            addElementInListWithoutIdRef(o);
                        }
                        /*Type[] args_ = currentValue_.GetType().GetGenericArguments();
                    Type pairType_ = null;
                    if (args_.Length == 2)
                    {
                        Type spec_ = typeof(TreeMap<,>).MakeGenericType(args_);
                        pairType_ = typeof(KeyValuePair<,>).MakeGenericType(args_);
                        if (spec_.IsInstanceOfType(currentValue_))
                        {
                            treeMap_ = true;
                        }
                    }
                    if (treeMap_)
                    {
                        foreach (Object o in (IEnumerable)currentValue_)
                        {
                            if (pairType_.IsInstanceOfType(o))
                            {
                                continue;
                            }
                            addElementInListWithoutIdRef(o);
                        }
                    }*/

                    }
                    if (currentValue_ is ListableKey) {
                        /*if (currentValue_ instanceof TreeNodeMap) {
                            Object value_ = ((TreeNodeMap <?,?>)currentValue_).getCmp();
                            addElementInMapWithoutIdRef(value_, true, true);
                        }else if (currentValue_ instanceof TreeMap

                                && !(currentValue_ instanceof NaturalTreeNodeMap)) {
                            Object value_ = ((TreeMap <?,?>)currentValue_).comparator();
                            if (value_ != null)
                            {
                                addElementInMapWithoutIdRef(value_, false, true);
                            }
                        }*/
                        //					List<Object> keys_ = new List<>();
                        //					for (Object o: ((Map<?,?>)currentValue_).keySet()) {
                        //						keys_.add(o);
                        //					}

                        //					for (Object o: keys_) {
                        //						addElementInMapWithoutIdRef(o,true, false);
                        //
                        //					}
                        //					for (Object o: keys_) {
                        //						Object value_ = ((Map<?,?>)currentValue_).get(o);
                        //						addElementInMapWithoutIdRef(value_,false, false);
                        //					}
                        bool treeMap_ = false;
                        Type treeMapTypeGene_ = typeof(TreeMap<,>);
                        //string treeMapType_ = treeMapTypeGene_.Assembly.GetName().Name + ".." + treeMapTypeGene_.Namespace + "." + treeMapTypeGene_.Name;
                        string treeMapType_ = treeMapTypeGene_.Assembly.GetName().Name + "." + treeMapTypeGene_.Namespace + "." + treeMapTypeGene_.Name;
                        treeMapType_ = treeMapType_.Substring(0, treeMapType_.IndexOf(ElementsSerial.SPECIAL_SEP) + 1);
                        Type curType_ = currentValue_.GetType();
                        while (true)
                        {
                            if (curType_ == null)
                            {
                                break;
                            }
                            if (Constants.getTypeFullString(curType_).StartsWith(treeMapType_))
                            {
                                treeMap_ = true;
                                break;
                            }
                            curType_ = curType_.BaseType;
                        }
                        if (treeMap_)
                        {
                            FieldInfo p_ = SerializeXmlObject.getField(curType_, "comparator");
                            object cmp_ = p_.GetValue(currentValue_);
                            if (cmp_ != null)
                            {
                                addElementInMapWithoutIdRef(cmp_, false, true);
                            }
                        }
                        
                        ListableKey l_ = (ListableKey)currentValue_;
                        foreach (IEntry k in l_.entryListGene())
                        {
                            addElementInMapWithoutIdRef(k.getKeyObj(), true, false);
                            addElementInMapWithoutIdRef(k.getValueObj(), false, false);
                        }
                    }
                    if (currentValue_.GetType().IsArray)
                    {
                        Array array_ = currentValue_ as Array;
                        int length_ = array_.Length;
                        for (int i = 0; i < length_; i++)
                        {
                            addElementInArrayWithoutIdRef(array_.GetValue(i));
                        }
                        addComponentsToComposite(e);
                        continue;
                    }

                    /*if (currentValue_.getClass().isArray())
                    {
                        int length_ = Array.getLength(currentValue_);
                        for (int i = Constants.getFirstIndex(); i < length_; i++)
                        {
                            addElementInArrayWithoutIdRef(Array.get(currentValue_, i));
                        }
                    }*/
                    Type cl_;
                    if (getAllImplicitComparators().containsObj(e))
                    {
                        cl_ = currentValue_.GetType();
                        while (cl_ != typeof(Object)) {
                            bool comparatorClass_ = typeof(Comparer).IsAssignableFrom(cl_);
                            //try {
                            //    cl_.asSubclass(Comparator.class);
                            //    comparatorClass_ = true;
                            //} catch (Exception _e) {
                            //}
                            if (!comparatorClass_) {
                                break;
                            }

                            foreach (FieldInfo f in SerializeXmlObject.getFields(cl_)) {
                                if (f.IsNotSerialized)
                                {
                                    continue;
                                }
                                //if (Modifier.isTransient(f.getModifiers())) {
                                //    if (!SerializeXmlObject.isCopying()) {
                                //        continue;
                                //    }
                                //}
                                //if (Modifier.isStatic(f.getModifiers())) {
                                //    continue;
                                //}
                                //f.setAccessible(cl_.getAnnotation(RwXml.class)!=null);
                                Object value_ = f.GetValue(currentValue_);

                                addElementInSerializableWithoutIdRef(value_, cl_, f.Name);
                            }
                            cl_ = cl_.BaseType;
                        }

                        addComponentsToComposite(e);
                        continue;
                    }

                    cl_ = currentValue_.GetType();
				    while (cl_ != null) {
                        Type base_ = cl_.BaseType;
                        if (base_ == null)
                        {
                            break;
                        }
                        string name_ = base_.Name;
                        if (name_.ToLower().StartsWith(typeof(List<object>).Name.ToLower()))
                        {
                            break;
                        }
                        if (cl_.Name.ToLower().StartsWith(typeof(Map<object, object>).Name.ToLower()))
                        {
                            break;
                        }
                        if (cl_.Name.ToLower().StartsWith(typeof(TreeMap<object, object>).Name.ToLower()))
                        {
                            break;
                        }
                        /*if (cl_.getSuperclass() == AbstractList.class) {
                            break;
                        }*/
                        /*if (cl_.getSuperclass() == AbstractMap.class) {
                            break;
                        }*/
                        foreach (FieldInfo f in SerializeXmlObject.getFields(cl_)) {
                            if (f.IsNotSerialized)
                            {
                                continue;
                            }
						    /*if (Modifier.isTransient(f.getModifiers())) {
							    if (!SerializeXmlObject.isCopying()) {
								    continue;
							    }
						    }*/
						    /*if (Modifier.isStatic(f.getModifiers())) {
							    continue;
						    }*/
						    //f.setAccessible(cl_.getAnnotation(RwXml.class)!=null);
						    Object value_ = f.GetValue(currentValue_);
                            addElementInSerializableWithoutIdRef(value_, cl_, f.Name);
					    }
					    cl_ = cl_.BaseType;
				    }

                    addComponentsToComposite(e);
			    }
			    if(!getNews().isEmpty()) {
				    modif_ = true;

                    setCurrents(new MyList<TemplateSerial>(getNews()));
			    }
		    }
	    }
        public void addComponentsToComposite(TemplateSerial _e)
        {
            componentComposite.put(_e, components);
        }
        private void addElementInSerializableWithoutIdRef(
            Object _value, Type _cl, String _fieldName)
        {
            addElementWithoutIdRef(_value,
				false, _cl, _fieldName, false);
        }
        private void addElementInListWithoutIdRef(Object _value)
        {
            addElementWithoutIdRef(_value,
				false, typeof(IEnumerable), null, false);
	}

    private void addElementInMapWithoutIdRef(Object _value,
            bool _isKey, bool _isComparator)
    {
        addElementWithoutIdRef(_value,
				_isKey, typeof(ListableKey), null, _isComparator);
	}

private void addElementInArrayWithoutIdRef(Object _value)
{
		if (isPrimitive(_value)) {
            ElementsSerial elt_ = createPrimitive(_value, false, null);
            getComponents().Add(elt_);
        } else {
            TemplateSerial elt_ = createComposite(_value, false, null, false);
                getNews().Add(elt_);
                getComponents().Add(elt_);
                return;
               /* if (!SerializeXmlObject.isCheckReferences())
            {
                getNews().Add(elt_);
                getComponents().Add(elt_);
                return;
            }
            MyList<TemplateSerial> records_ = ElementsSerial.findSerialisableInList(_value, getAllComposites());
            if (records_.isEmpty())
            {
                getNews().Add(elt_);
                getAllComposites().Add(elt_);
                getComponents().Add(elt_);
            }
            else {
                throw new RefException();
            }*/
        }
}
private void addElementWithoutIdRef(Object _value,
            bool _isKey, Type _cl, String _fieldName, bool _isComparator)


{
		if (isPrimitive(_value)) {
        ElementsSerial elt_ = createPrimitive(_value, _isKey, _cl, _fieldName);
        getComponents().Add(elt_);
    } else {
        TemplateSerial elt_ = createComposite(_value, _isKey, _cl, _fieldName, _isComparator);
                if (elt_ == null)
                {
                    return;
                }
        if (_isComparator)
        {
            getAllImplicitComparators().Add(elt_);
        }
                getNews().Add(elt_);
                getComponents().Add(elt_);
                return;
                /*
                if (!SerializeXmlObject.isCheckReferences())
        {
            getNews().Add(elt_);
            getComponents().Add(elt_);
            return;
        }
        MyList<TemplateSerial> records_ = ElementsSerial.findSerialisableInList(_value, getAllComposites());
        if (records_.isEmpty())
        {
            getNews().Add(elt_);
            getAllComposites().Add(elt_);
            getComponents().Add(elt_);
        }
        else {
            throw new RefException();
        }*/
    }
}
        public static ElementsSerial createPrimitive(Object _value)
        {
            return createPrimitive(_value, false, null);
        }

        private static ElementsSerial createPrimitive(
                Object _value, bool _isKey, String _field)
        {
            if (_value == null)
            {
                NullSerial null_ = new NullSerial();
                null_.setField(_field);
                null_.setKeyOfMap(_isKey);
                return null_;
            }
            MethodInfo method_ = ConverterMethod.getToStringMethod(_value.GetType());
            if (method_ != null || _value is Primitivable) {
                StringObjectSerial number_ = new StringObjectSerial(_value);
                number_.setKeyOfMap(_isKey);
                number_.setField(_field);
                return number_;
            }
            if (_value is int) {
                NumberSerial<int> number_ = new NumberSerial<int>((int)_value);
                number_.setKeyOfMap(_isKey);
                number_.setField(_field);
                return number_;
            }
            if (_value is long)
            {
                NumberSerial<long> number_ = new NumberSerial<long>((long)_value);
                number_.setKeyOfMap(_isKey);
                number_.setField(_field);
                return number_;
            }
            if (_value is String) {
                StringSerial number_ = new StringSerial((String)_value);
                number_.setKeyOfMap(_isKey);
                number_.setField(_field);
                return number_;
            }
            if (_value is char) {
                CharacterSerial number_ = new CharacterSerial((char)_value);
                number_.setKeyOfMap(_isKey);
                number_.setField(_field);
                return number_;
            }
            if (_value is Boolean) {
                BooleanSerial boolean_ = new BooleanSerial((Boolean)_value);
                boolean_.setKeyOfMap(_isKey);
                boolean_.setField(_field);
                return boolean_;
            }
            if (_value is Enum) {
                EnumSerial enum_ = new EnumSerial((Enum) _value);
                enum_.setKeyOfMap(_isKey);
                enum_.setField(_field);
                return enum_;
            }
            return null;
        }

        private static ElementsSerial createPrimitive(
                Object _value, bool _isKey, Type _cl, String _field)
        {
            ElementsSerial elt_ = createPrimitive(_value, _isKey, _field);
            elt_.setClassName(Constants.getTypeFullString(_cl));
            return elt_;
        }

        private static TemplateSerial createComposite(
                Object _value, bool _isKey, String _field, bool _isComparator)
        {
            if (_isComparator) {
                if (_value is IComparer)
                {
                    ComparatorSerial serializableFieldBis_ = new ComparatorSerial((IComparer)_value);
                    serializableFieldBis_.setKeyOfMap(_isKey);
                    serializableFieldBis_.setField(_field);
                    return serializableFieldBis_;
                }
                return null;
            }
            if (_value.GetType().IsArray)
            {
                ArraySerial serializableFieldTer_ = new ArraySerial((Array)_value);
                serializableFieldTer_.setKeyOfMap(_isKey);
                serializableFieldTer_.setField(_field);
                return serializableFieldTer_;
            }
            ObjectSerial serializableField_ = new ObjectSerial(_value);
            serializableField_.setKeyOfMap(_isKey);
            serializableField_.setField(_field);
            return serializableField_;

        }

        private static TemplateSerial createComposite(
                Object _value, bool _isKey, Type _cl, String _field, bool _isComparator)
        {
            TemplateSerial temp_ = createComposite(_value, _isKey, _field, _isComparator);
            if (temp_ == null)
            {
                return temp_;
            }
            temp_.setClassName(Constants.getTypeFullString(_cl));
            return temp_;

        }

        private static bool isPrimitive(Object _o)
        {
            if (_o == null)
            {
                return true;
            }
            if (_o is int)
            {
                return true;
            }
            if (_o is long) {
                return true;
            }
            if (_o is char) {
                return true;
            }
            if (_o is String) {
                return true;
            }
            if (_o is Boolean) {
                return true;
            }
            if (_o is Enum) {
                return true;
            }
            if (_o is Primitivable) {
                return true;
            }
            MethodInfo method_ = ConverterMethod.getToStringMethod(_o.GetType());
            if (method_ != null)
            {
                return true;
            }
            return false;
        }

        public MyList<ElementsSerial> getComponentComposite(TemplateSerial _temp)
        {
            return componentComposite.getVal(_temp);
        }

        public MyList<TemplateSerial> getAllComposites()
        {
            return allComposites;
        }

        public void setAllComposites(MyList<TemplateSerial> _allComposites)
        {
            allComposites = _allComposites;
        }

        public MyList<TemplateSerial> getNews()
        {
            return news;
        }

        public void setNews(MyList<TemplateSerial> _news)
        {
            news = _news;
        }

        public MyList<TemplateSerial> getCurrents()
        {
            return currents;
        }

        public void setCurrents(MyList<TemplateSerial> _currents)
        {
            currents = _currents;
        }

        public MyList<ElementsSerial> getAllImplicitComparators()
        {
            return allImplicitComparators;
        }

        public void setAllImplicitComparators(MyList<ElementsSerial> _allImplicitComparators)
        {
            allImplicitComparators = _allImplicitComparators;
        }

        public MyList<ElementsSerial> getComponents()
        {
            return components;
        }

        public void setComponents(MyList<ElementsSerial> _components)
        {
            components = _components;
        }

        public long getId()
        {
            return id;
        }

        public void setId(long _id)
        {
            id = _id;
        }
    }
}
