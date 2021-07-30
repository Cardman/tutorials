using FormatHtml;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Util;

namespace FormatHtmlTests
{
    public class Composite
    {
        private int integer;

        private int privateInt;

        private ValueChangeEvent changing;

        private StringList strings;

        private TreeMap<String, int> tree;

        private Map<String, int> map;

        private MyMap<String, int> myMap;

        public void updateValue(ValueChangeEvent _changing)
        {
            getStrings().Add(_changing.getNewValue() + " " + _changing.getOldValue());
            changing = _changing;
        }

        public ValueChangeEvent getChanging()
        {
            return changing;
        }

        public int getInteger()
        {
            return integer;
        }

        public void setInteger(int _integer)
        {
            integer = _integer;
        }

        public int getPrivateInt()
        {
            return privateInt;
        }

        public void setPrivateInt(int _privateInt)
        {
            privateInt = _privateInt;
        }

        public int sum(long _other)
        {
            return integer + (int) _other;
        }

        public int sum(long _other, long _otherTwo)
        {
            return integer + (int)_other + (int) _otherTwo;
        }

        public int sum()
        {
            return integer + privateInt;
        }

        public StringList getStrings()
        {
            return strings;
        }

        public void setStrings(StringList _strings)
        {
            strings = _strings;
        }

        public TreeMap<String, int> getTree()
        {
            return tree;
        }

        public void setTree(TreeMap<String, int> _tree)
        {
            tree = _tree;
        }

        public Map<String, int> getMap()
        {
            return map;
        }

        public void setMap(Map<String, int> _map)
        {
            map = _map;
        }

        public StringList keys()
        {
            StringList list_ = new StringList(map.getKeys());
            list_.sort();
            return list_;
        }

        public MyMap<String, int> getMyMap()
        {
            return myMap;
        }

        public void setMyMap(MyMap<String, int> _myMap)
        {
            myMap = _myMap;
        }

        public String internMethod()
        {
            return "sample";
        }

        public String privateMethod()
        {
            return "sample";
        }

        public String toString()
        {
            return integer + "," + privateInt + "," + strings + "," + tree + "," + map + "," + myMap;
        }
    }
}
