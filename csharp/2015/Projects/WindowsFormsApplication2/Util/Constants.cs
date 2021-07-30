using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using System.Xml;

namespace Util
{
    public class Constants
    {
        internal const String NODE_INT = "node";
        internal const String TYPE_INT = "type";
        internal const String ASSEMBLY_INT = "assembly";
        private static String _language_;
        private static Assembly _assembly_;
        public static void reinitAssembly()
        {
            _assembly_ = null;
        }
        public static Assembly getAssembly()
        {
            return _assembly_;
        }
        public static void setAssembly(Assembly _assembly)
        {
            _assembly_ = _assembly;
        }
        public static void setLanguage(string _language)
        {
            _language_ = _language;
        }
        public static String getLanguage()
        {
            return _language_;
        }
        public static MethodInfo getParseMethod(Type _class)
        {
            MethodInfo methNb_ = null;
            Type strType_ = typeof(string);
            foreach (MethodInfo m in _class.GetMethods())
            {
                if (!m.Name.Equals("Parse"))
                {
                    continue;
                }
                if (!m.IsStatic)
                {
                    continue;
                }
                if (m.ReturnType == null)
                {
                    continue;
                }
                if (!_class.IsAssignableFrom(m.ReturnType))
                {
                    continue;
                }
                ParameterInfo[] param_ = m.GetParameters();
                if (param_.LongLength != 1)
                {
                    continue;
                }
                if (param_[0].ParameterType != strType_)
                {
                    continue;
                }
                methNb_ = m;
                break;
            }
            return methNb_;
        }
        public static Type classForName(String _name)
        {
            /*Type classLoad_ = ClassesMap.getClassByName(_name);
		    if (classLoad_ != null) {
                return classLoad_;
            }*/
            /*if (_assembly_ != null)
            {

            }*/
		    //return classForNameKnownClasses(_name)
            return dynamicClassForName(_assembly_,_name);
        }

        public static Type dynamicClassForName(Assembly _assembly, String _name)
        {
            TreeMap<MyList<int>, String> types_;
            int indexDot_ = _name.IndexOf(".");
            string libType_ = _name.Substring(0, indexDot_);
            string typeName_ = _name.Substring(indexDot_ + 1);
            types_ = new TreeMap<MyList<int>, string>(new ComparatorNumberList());
            types_.put(new MyList<int>(0), libType_+" "+ typeName_);
            TreeMap<MyList<int>, Type> typesBuilt_;
            typesBuilt_ = new TreeMap<MyList<int>, Type>(new ComparatorNumberList());
            if (_assembly == null)
            {
                Assembly as_ = Assembly.Load(libType_);
                typesBuilt_.put(new MyList<int>(0), as_.GetType(typeName_, false));
            }
            else
            {
                try
                {
                    typesBuilt_.put(new MyList<int>(0), _assembly.GetType(typeName_, true));
                }
                catch (Exception)
                {
                    Assembly as_ = Assembly.Load(libType_);
                    typesBuilt_.put(new MyList<int>(0), as_.GetType(typeName_, false));
                }
            }
            //typesBuilt_.put(new MyList<int>(0), null);
            int deep_ = 0;
            while (true)
            {
                bool containsBracket_ = false;
                foreach (IEntry<MyList<int>, string> e in types_.entryList())
                {
                    if (e.getValue().Contains("["))
                    {
                        containsBracket_ = true;
                        break;
                    }
                }
                if (!containsBracket_)
                {
                    break;
                }
                deep_++;
                foreach (MyList<int> k in types_.getKeys())
                {
                    String v_ = types_.getVal(k);
                    StringList typesStr_ = StringList.getTypes(v_);
                    /*foreach (string t in typesStr_) {
                        Console.WriteLine("%" + t);
                    }*/
                    string prefix_ = v_;
                    int index_ = v_.IndexOf("[");
                    if (index_ >= 0)
                    {
                        prefix_ = v_.Substring(0, index_);
                        types_.put(k, prefix_);
                        if (_assembly == null)
                        {
                            libType_ = prefix_.Split(' ').ElementAt(0);
                            Assembly as_ = Assembly.Load(libType_);
                            typeName_ = prefix_.Split(' ').ElementAt(1);
                            typesBuilt_.put(k, as_.GetType(typeName_, false));
                        } else
                        {
                            try
                            {
                                typeName_ = prefix_.Split(' ').ElementAt(1);
                                typesBuilt_.put(k, _assembly.GetType(typeName_, true));
                            }
                            catch (Exception)
                            {
                                libType_ = prefix_.Split(' ').ElementAt(0);
                                Assembly as_ = Assembly.Load(libType_);
                                typeName_ = prefix_.Split(' ').ElementAt(1);
                                typesBuilt_.put(k, as_.GetType(typeName_, false));
                            }
                        }
                        int indexType_ = 0;
                        foreach (string t in typesStr_)
                        {
                            string t_ = t.Trim();
                            t_ = t_.Substring(1, t_.Length - 2);
                            MyList<int> l_ = new MyList<int>(k);
                            l_.Add(indexType_);
                            int lastIndex_ = t_.LastIndexOf(',');
                            string as_ = t_.Substring(lastIndex_+2);
                            string type_ = t_.Substring(0, lastIndex_);
                            types_.put(l_, as_+" "+type_);
                            if (_assembly == null)
                            {
                                typesBuilt_.put(l_, Assembly.Load(as_).GetType(type_, false));
                            }
                            else
                            {
                                try
                                {
                                    typesBuilt_.put(l_, _assembly.GetType(type_, true));
                                }
                                catch (Exception)
                                {
                                    typesBuilt_.put(l_, Assembly.Load(as_).GetType(type_, false));
                                }
                            }
                            indexType_++;
                        }
                    }
                }
            }
            /*foreach (MyList<int> k in typesBuilt_.getKeys())
            {
                Console.WriteLine(k.join(",")+";"+ typesBuilt_.getVal(k));
            }*/
            //deep_--;
            //Console.WriteLine(deep_);
            //Type typeRet_ = null;
            while (true)
            {
                if (types_.size() == 1)
                {
                    break;
                }
                foreach (MyList<int> k in types_.getKeys())
                {
                    if (k.size() != deep_)
                    {
                        continue;
                    }
                    Type type_ = typesBuilt_.getVal(k);
                    MyList<Type> typesStruct_ = new MyList<Type>();
                    foreach (MyList<int> s in types_.getKeys())
                    {
                        if (s.size() != deep_ + 1)
                        {
                            continue;
                        }
                        bool startsWith_ = true;
                        for (int i = 0; i < deep_; i++)
                        {
                            if (k.get(i) != s.get(i))
                            {
                                startsWith_ = false;
                                break;
                            }
                        }
                        if (!startsWith_)
                        {
                            continue;
                        }
                        types_.removeKey(s);
                        typesStruct_.Add(typesBuilt_.getVal(s));
                    }
                    //Console.WriteLine("%" + k+"%"+ type_);
                    if (!type_.IsGenericType)
                    {
                        continue;
                    }
                    typesBuilt_.put(k, type_.MakeGenericType(typesStruct_.ToArray()));
                }
                deep_--;
            }
            return typesBuilt_.getValue(0);
        }

        static Type classForNameKnownClasses(String _name)
        {
            Type primitive_ = getPrimitiveClass(_name);
		    if (primitive_ != null) {
                return primitive_;
            }
            Type class_;
            int indexDot_ = _name.IndexOf(".");
            /*if (_name.Contains(".."))
            {
                string[] infos_ = _name.Split(new string[] { ".." }, StringSplitOptions.None);
                string lib_ = infos_[0];
                string type_ = infos_[1];
                Assembly a_ = Assembly.Load(lib_);
                class_ = a_.GetType(type_, true, true);
            } else {
                class_ = Type.GetType(_name, true, true);
            }*/
            string lib_ = _name.Substring(0, indexDot_);
            string type_ = _name.Substring(indexDot_ + 1);
            Assembly a_ = Assembly.Load(lib_);
            class_ = a_.GetType(type_, true, true);
            return class_;
        }
        public static string getTypeFullString(Type _type)
        {
            string str_ = getTypeString(_type);
            string assName_ = _type.Assembly.GetName().Name;
            //string fullType_ = assName_ + ".." + str_;
            string fullType_ = assName_ + "." + str_;
            return fullType_;
        }
        public static XmlDocument getTypeStringXml(Type _type)
        {
            XmlDocument doc_ = new XmlDocument();
            XmlElement elt_ = doc_.CreateElement(NODE_INT);
            elt_.SetAttribute(TYPE_INT, _type.Namespace + "." + _type.Name);
            elt_.SetAttribute(ASSEMBLY_INT, _type.Assembly.GetName().Name);
            doc_.AppendChild(elt_);
            List<Type> currentSubTypes_ = new List<Type>();
            currentSubTypes_.Add(_type);
            List<Type> newSubTypes_ = new List<Type>();
            List<XmlNode> currentSubTypesNode_ = new List<XmlNode>();
            currentSubTypesNode_.Add(elt_);
            List<XmlNode> newSubTypesNode_ = new List<XmlNode>();
            while (true)
            {
                int i_ = 0;
                foreach (Type t in currentSubTypes_)
                {
                    foreach (Type e in t.GetGenericArguments())
                    {
                        XmlElement subElt_ = doc_.CreateElement(NODE_INT);
                        subElt_.SetAttribute(TYPE_INT, e.Namespace + "." + e.Name);
                        subElt_.SetAttribute(ASSEMBLY_INT, e.Assembly.GetName().Name);
                        currentSubTypesNode_.ElementAt(i_).AppendChild(subElt_);
                        newSubTypesNode_.Add(subElt_);
                        newSubTypes_.Add(e);
                    }
                    i_++;
                }
                if (newSubTypes_.Count == 0)
                {
                    break;
                }
                currentSubTypes_ = new List<Type>(newSubTypes_);
                currentSubTypesNode_ = new List<XmlNode>(newSubTypesNode_);
                newSubTypes_ = new List<Type>();
                newSubTypesNode_ = new List<XmlNode>();
            }
            return doc_;
        }
        public static String getTypeString(Type _type)
        {
            //TODO add iterations
            XmlDocument doc_ = getTypeStringXml(_type);
            while (true)
            {
                bool emptyTypes_ = true;
                XmlElement elt_ = XmlParser.documentElement(doc_);
                foreach (XmlNode n in XmlParser.childrenNodes(elt_))
                {
                    if (!(n as XmlElement).GetAttribute(TYPE_INT).isEmpty())
                    {
                        emptyTypes_ = false;
                        break;
                    }
                }
                if (emptyTypes_)
                {
                    break;
                }
                setupDocument(doc_);
            }
            //return XmlParser.toXml(doc_);
            return XmlParser.documentElement(doc_).GetAttribute(TYPE_INT);
            //return XmlParser.toXml(getTypeStringXml(_type));
        }
        public static void setupDocument(XmlDocument _xml)
        {
            XmlElement mainElt_ = XmlParser.documentElement(_xml);
            MyList<XmlNode> currentNodes_ = new MyList<XmlNode>();
            currentNodes_.Add(mainElt_);
            MyList<XmlNode> newNodes_ = new MyList<XmlNode>();
            while (true)
            {
                foreach (XmlNode n in currentNodes_)
                {
                    bool final_ = true;
                    //bool noChild_ = true;
                    foreach (XmlNode e in XmlParser.childrenNodes(n))
                    {
                        bool empty_ = true;
                        //noChild_ = false;
                        foreach (XmlNode x in XmlParser.childrenNodes(e))
                        {
                            if (!(x as XmlElement).GetAttribute(TYPE_INT).isEmpty())
                            {
                                empty_ = false;
                                break;
                            }
                        }
                        if (!empty_)
                        {
                            final_ = false;
                            newNodes_.Add(e);
                        } /*else if (!(e as XmlElement).GetAttribute(TYPE_INT).isEmpty())
                        {
                            newNodes_.Add(e);
                        }*/
                    }
                    if (final_)
                    {// && !noChild_
                        StringList types_ = new StringList();
                        foreach (XmlNode e in XmlParser.childrenNodes(n))
                        {
                            XmlElement e_ = e as XmlElement;
                            types_.Add("[" + e_.GetAttribute(TYPE_INT) + ", " + e_.GetAttribute(ASSEMBLY_INT) + "]");
                            e_.SetAttribute(TYPE_INT, "");
                        }
                        XmlElement n_ = n as XmlElement;
                        if (!types_.isEmpty())
                        {
                            string typeLoc_ = n_.GetAttribute(TYPE_INT);
                            typeLoc_ += "[" + types_.join(", ") + "]";
                            n_.SetAttribute(TYPE_INT, typeLoc_);
                        }

                    }
                }
                if (newNodes_.isEmpty())
                {
                    break;
                }
                currentNodes_ = new MyList<XmlNode>(newNodes_);
                newNodes_ = new MyList<XmlNode>();
            }
        }
        public static Type classForName(String _name, String _geneTypes)
        {
            /*Type classLoad_ = ClassesMap.getClassByName(_name);
		    if (classLoad_ != null) {
                return classLoad_;
            }*/
            return classForNameKnownClasses(_name, _geneTypes);
        }

        static Type classForNameKnownClasses(String _name, String _geneTypes)
        {
            Type primitive_ = getPrimitiveClass(_name);
            if (primitive_ != null)
            {
                return primitive_;
            }
            Type class_;
            int indexDot_ = _name.IndexOf(".");
            /*if (_name.Contains(".."))
            {
                string[] infos_ = _name.Split(new string[] { ".." }, StringSplitOptions.None);
                string lib_ = infos_[0];
                string type_ = infos_[1]+ _geneTypes;
                Assembly a_ = Assembly.Load(lib_);
                class_ = a_.GetType(type_, true, true);
            }
            else {
                class_ = Type.GetType(_name, true, true);
            }*/
            string lib_ = _name.Substring(0, indexDot_);
            string type_ = _name.Substring(indexDot_ + 1) + _geneTypes;
            Assembly a_ = Assembly.Load(lib_);
            class_ = a_.GetType(type_, true, true);
            return class_;
        }
        private static Type getPrimitiveClass(String _name)
        {
            if (typeof(int).FullName.Equals(_name)) {
			    return typeof(int);
            }
            if (typeof(long).FullName.Equals(_name))
            {
                return typeof(long);
            }
            if (typeof(short).FullName.Equals(_name))
            {
                return typeof(short);
            }
            if (typeof(byte).FullName.Equals(_name))
            {
                return typeof(byte);
            }
            if (typeof(bool).FullName.Equals(_name))
            {
                return typeof(bool);
            }
            if (typeof(char).FullName.Equals(_name))
            {
                return typeof(char);
            }
            if (typeof(float).FullName.Equals(_name))
            {
                return typeof(float);
            }
            if (typeof(double).FullName.Equals(_name))
            {
                return typeof(double);
            }
		    return null;
	    }
    }
}
