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
    public abstract class ElementsSerial
    {
        protected const String EMPTY_STRING = "";
        protected const String SEPARATOR = ";";
        protected const String COMMA = ",";
        public const String CLASS = "class";
        public const String FIELD = "field";
        public const String KEY = "key";
        //private const char ACUTE = (char)180;
        public const String SPECIAL_SEP="`";// { get { return new string(new char[] { ACUTE }); }}
        internal const String NODE_INT = "node";
        internal const String TYPE_INT = "type";
        internal const String ASSEMBLY_INT = "assembly";

        private String className;

        private String field;

        private bool keyOfMap;

        public abstract Object getValue();

        public abstract Type getValueClass();

        public abstract XmlElement serialize(XmlDocument _doc);

        public abstract XmlElement serializeWithoutRef(XmlDocument _doc);

        public static string getTypeRec(Type _type)
        {
            if (_type.GetGenericArguments().Length == 0)
            {
                return _type.FullName + " " + _type.Assembly.GetName().Name;
            }
            StringList list_ = new StringList();
            foreach (Type t in _type.GetGenericArguments()) {
                list_.Add(getTypeRec(t));
            }
            return _type.Namespace + "."+_type.Name + "["+ list_.join(",")+ "] " + _type.Assembly.GetName().Name;
        }
        internal static string getType(Type _obj)
        {
            Assembly ass_ = _obj.Assembly;
            //return ass_.GetName().Name + ".." + _obj.FullName.Split(new string[] { SPECIAL_SEP }, StringSplitOptions.None)[0];
            return ass_.GetName().Name + "." + _obj.FullName.Split(new string[] { SPECIAL_SEP }, StringSplitOptions.None)[0];
        }
        public static MyList<TemplateSerial> findSerialisableInList(Object _o, MyList<TemplateSerial> _allComposites)
        {
            MyList<TemplateSerial> list_ = new MyList<TemplateSerial>();
            foreach (TemplateSerial e in _allComposites)
            {
                if (e.getValue() != _o)
                {
                    continue;
                }
                list_.Add(e);
                break;
            }
            return list_;
        }

        public String getClassName()
        {
            return className;
        }

        public void setClassName(String _className)
        {
            className = _className;
        }

        public String getField()
        {
            return field;
        }

        public void setField(String _field)
        {
            field = _field;
        }

        public bool isKeyOfMap()
        {
            return keyOfMap;
        }

        public void setKeyOfMap(bool _keyOfMap)
        {
            keyOfMap = _keyOfMap;
        }

        public override bool Equals(Object _arg0)
        {
            if (_arg0 == null)
            {
                return false;
            }
            if (!(_arg0 is ElementsSerial)) {
                return false;
            }
            ElementsSerial e_ = (ElementsSerial)_arg0;
            return getValue() == e_.getValue();
        }
        private void ln()
        {

        }
    }
}
