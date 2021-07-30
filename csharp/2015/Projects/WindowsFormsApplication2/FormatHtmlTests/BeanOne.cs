using FormatHtml;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Util;

namespace FormatHtmlTests
{
    public class BeanOne : Bean
    {
        private Composite composite = new Composite();

        private MyList<EnumNumber> combobox = new MyList<EnumNumber>();

        private TreeMap<EnumNumber, String> translations = new TreeMap<EnumNumber, String>(new ComparatorEnum<EnumNumber>());

        private TreeMap<String, MyList<int>> numbers = new TreeMap<String, MyList<int>>();

        private EnumNumber? chosenNumber = EnumNumber.ONE;

        private String message = "Test {0}";

        private ValueChangeEvent changing;

        private TreeMap<String, int> tree = new TreeMap<String, int>();

        private Map<String, int> map = new Map<String, int>();

        private String selectedString = "ONE";

        public BeanOne()
        {
            composite.setStrings(new StringList());
            foreach (EnumNumber e in typeof(EnumNumber).GetEnumValues())
            {
                translations.put(e, (e.ordinal() + 1).ToString());
                combobox.Add(e);
            }
            numbers.put("ONE", new MyList<int>(1));
            numbers.put("TWO", new MyList<int>(2, 3));
            numbers.put("THREE", new MyList<int>(4, 5, 6));
        }

        public Composite getComposite()
        {
            return composite;
        }

        public void setComposite(Composite _composite)
        {
            composite = _composite;
        }

        public void updateValue(ValueChangeEvent _changing)
        {
            composite.getStrings().Add(_changing.getNewValue() + " " + _changing.getOldValue());
            changing = _changing;
        }

        public String invokeMethod(long _index)
        {
            composite.getStrings().Add(_index.ToString());
            return "returned value";
        }

        public ValueChangeEvent getChanging()
        {
            return changing;
        }

        public TreeMap<String, int> getTree()
        {
            return tree;
        }

        public Map<String, int> getMap()
        {
            return map;
        }

        public StringList getKeys()
        {
            StringList list_ = new StringList(map.getKeys());
            list_.sort();
            return list_;
        }

        public int getDouble(long _index)
        {
            return 2 * (int) _index;
        }

        public MyList<int> getList(long _index)
        {
            if (_index >= numbers.size())
            {
                return numbers.getValue(numbers.size() - 1);
            }
            return numbers.getValue((int)_index);
        }
        public void setCombobox(MyList<EnumNumber> _list)
        {
            combobox = _list;
        }
        public MyList<EnumNumber> getCombobox()
        {
            return combobox;
        }
        public EnumNumber getDefaultChoice()
        {
            if (chosenNumber == null)
            {
                return EnumNumber.THREE;
            }
            Array arr_ = typeof(EnumNumber).GetEnumValues();
            return (EnumNumber) arr_.GetValue(arr_.Length - chosenNumber.Value.ordinal() - 1);
        }

        public String goToPage()
        {
            return "page";
        }

        public String goToNullPage()
        {
            return null;
        }

        public String goToPage(long _index)
        {
            return "page" + _index;
        }
    }
}
