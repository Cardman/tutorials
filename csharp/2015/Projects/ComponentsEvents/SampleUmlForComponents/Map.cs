using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SampleUmlForComponents
{
    public sealed class Map<K,V> : ListableEntries<K,V>
    {
        private MyList<Entry<K, V>> list = new MyList<Entry<K, V>>();
        public Map()
        {

        }
        public Map(Map<K, V> _map)
        {
            list.AddRange(_map.list);
        }
        public MyList<Entry<K, V>> entryList()
        {
            return list;
        }
        public int size()
        {
            return list.Count;
        }
        public MyIList<K> getKeys()
        {
            MyList<K> list_ = new MyList<K>();
            foreach (Entry<K, V> e in list)
            {
                list_.Add(e.getKey());
            }
            return list_;
        }
        public void put(K _key, V _value)
        {
            if (_key == null)
            {
                foreach (Entry<K, V> e in list)
                {
                    if (e.getKey() == null)
                    {
                        e.setValue(_value);
                        return;
                    }
                }
                list.Add(new Entry<K, V>(_key, _value));
                return;
            }
            foreach (Entry<K, V> e in list)
            {
                if (_key.Equals(e.getKey()))
                {
                    e.setValue(_value);
                    return;
                }
            }
            list.Add(new Entry<K, V>(_key, _value));
        }
        public bool contains(K _key)
        {
            if (_key == null)
            {
                foreach (Entry<K, V> e in list)
                {
                    if (e.getKey() == null)
                    {
                        return true;
                    }
                }
                return false;
            }
            foreach (Entry<K, V> e in list)
            {
                if (_key.Equals(e.getKey()))
                {
                    return true;
                }
            }
            return false;
        }
        public MyList<V> getValues(K _key)
        {
            MyList<V> values_ = new MyList<V>();
            if (_key == null)
            {
                foreach (Entry<K, V> e in list)
                {
                    if (e.getKey() == null)
                    {
                        values_.Add(e.getValue());
                    }
                }
                return values_;
            }
            foreach (Entry<K, V> e in list)
            {
                if (_key.Equals(e.getKey()))
                {
                    values_.Add(e.getValue());
                }
            }
            return values_;
        }
        public V getVal(K _key)
        {
            return get(_key);
        }
        public V get(object _key)
        {
            if (_key == null)
            {
                foreach (Entry<K, V> e in list)
                {
                    if (e.getKey() == null)
                    {
                        return e.getValue();
                    }
                }
                return default(V);
            }
            foreach (Entry<K, V> e in list)
            {
                if (_key.Equals(e.getKey()))
                {
                    return e.getValue();
                }
            }
            return default(V);
        }
        public void removeKey(K _key)
        {
            int i_ = 0;
            if (_key == null)
            {
                foreach (Entry<K, V> e in list)
                {
                    if (e.getKey() == null)
                    {
                        list.RemoveAt(i_);
                        return;
                    }
                    i_++;
                }
                return;
            }
            foreach (Entry<K, V> e in list)
            {
                if (_key.Equals(e.getKey()))
                {
                    list.RemoveAt(i_);
                    return;
                }
                i_++;
            }
        }

        /*public IEnumerator<Entry> GetEnumerator()
        {
            return list.GetEnumerator();
        }*/

        IEnumerator IEnumerable.GetEnumerator()
        {
            //Or return GetEnumerator();
            return list.GetEnumerator();
        }

        IEnumerator<IEntry<K, object>> IEnumerable<IEntry<K, object>>.GetEnumerator()
        {
            List<IEntry<K, object>> list_ = new List<IEntry<K, object>>();
            foreach (Entry<K, V> e in list)
            {
                list_.Add(new Entry<K,object>(e.getKey(),e.getValue()));
            }
            return list_.GetEnumerator();
        }

        public void putAllMap(ListableEntries<K, V> _m)
        {
            foreach (Entry<K,V> e in _m)
            {
                put(e.getKey(), e.getValue());
            }
        }
    }
    public class Entry<K, V> : IEntry<K, V>
    {//Entry,
        private K key { get; set; }
        private V value { get; set; }
        public Entry(K _key, V _value)
        {
            key = _key;
            value = _value;
        }
        public K getKey()
        {
            return key;
        }
        public V getValue()
        {
            return value;
        }
        public void setValue(V _value)
        {
            value = _value;
        }
        public void setObjValue(object _value)
        {
            if (_value is V)
            {
                value = ((V)_value);
            }
        }
        public override string ToString()
        {
            return key + " "+value;
        }
    }
    /*public class Entry
    {
        internal Entry() { }
    }*/
    public interface IEntry<out K, out V>
    {
        K getKey();
        V getValue();
        void setObjValue(object _value);
    }
}
