using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Util;

namespace GuiCommon
{
    public abstract class MyComboBox<T> : ComboBox where T : struct
    {
        private MyList<T?> order = new MyList<T?>();

        private TreeMap<T?, String> elements;

        private bool withDefaultValue;

        public abstract void refresh(MyList<T?> _order, String _language, bool _sortStrings);

        public void refresh(MyList<T?> _order, Map<T?, String> _tr)
        {
            order.Clear();
            order.AddRange(_order);
            Items.Clear();
            Map<T?, String> m_ = new Map<T?, String>(_tr);
            //		elements = new TreeMap<T,String>(new Comparator<T>(){
            //			@Override
            //			public int compare(T _o1, T _o2) {
            //				return order.indexOfObj(_o1) - order.indexOfObj(_o2);
            //			}
            //		});
            elements = new TreeMap<T?, String>(new ComparatorIndexes<T>(order));
            if (withDefaultValue)
            {
                m_.put(null, "");
            }
            elements.putAllMap(m_);
            foreach (T? e in elements.getKeys())
            {
                if (_tr.contains(e))
                {
                    Items.Add(_tr.getVal(e));
                }
                else
                {
                    Items.Add("");
                }
            }
        }

        public void refresh(Map<T?, String> _tr)
        {
            Items.Clear();
            Map<T?, String> m_ = new Map<T?, String>(_tr);
            elements = new TreeMap<T?, String>(new ComparatorMapValue<T>(m_));
            if (withDefaultValue)
            {
                m_.put(null, "");
            }
            elements.putAllMap(m_);
            foreach (T? e in elements.getKeys())
            {
                if (_tr.contains(e))
                {
                    Items.Add(_tr.getVal(e));
                } else
                {
                    Items.Add("");
                }
                
            }
        }

        public T? getCurrent()
        {
            int index_ = SelectedIndex;
            if (index_ < 0)
            {
                return null;
            }
            return elements.getKey(index_);
        }

        public void setCurrent(T? _current)
        {
            MyList<T?> keys_ = new MyList<T?>(elements.getKeys());
            int index_ = keys_.indexOfObj(_current);
            if (index_ < 0)
            {
                return;
            }
            SelectedIndex = index_;
        }

        public void setWithDefaultValue(bool _withDefaultValue)
        {
            withDefaultValue = _withDefaultValue;
        }

        public bool isWithDefaultValue()
        {
            return withDefaultValue;
        }
    }
}
