using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MyLibrary
{
    public class Map<K,V>
    {
        private List<Entry<K, V>> list = new List<Entry<K, V>>();
        public Map()
        {

        }
        public Map(Map<K,V> _map)
        {
            list.AddRange(_map.list);
        }
        public List<Entry<K, V>> entryList()
        {
            return list;
        }
        public int size()
        {
            return list.Count;
        }
        public List<K> keyList()
        {
            List<K> list_ = new List<K>();
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
        public V getVal(K _key)
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
    }
    public class Entry<K,V>
    {
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
    }
}
