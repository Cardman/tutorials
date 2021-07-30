using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HelloWorld
{
    public interface ListableEntries<K,V> : IEnumerable<IEntry<K, object>>, ListableKey<K,V>
    {
        MyList<Entry<K, V>> entryList();

        void putAllMap(ListableEntries<K,V> _m);

        MyList<V> getValues(K _key);
        V getVal(K _key);
    }
    public interface ListableKey<out K,out V>
    {
        MyIList<K> getKeys();
        V get(object _obj);
    }
    public static class Entries
    {
        public static MyIList<K> getKeys<K>(this IEnumerable<IEntry<K, object>> _map)
        {
            MyList<K> keys_ = new MyList<K>();
            foreach (IEntry<K,object> e in _map)
            {
                keys_.Add(e.getKey());
            }
            return keys_;
        }
        public static object getValue(this IEnumerable<IEntry<object, object>> _map, object _key)
        {
            if (_key == null)
            {
                foreach (IEntry<object, object> e in _map)
                {
                    if (e.getKey() == null)
                    {
                        return e.getValue();
                    }
                }
                return null;
            }
            foreach (IEntry<object, object> e in _map)
            {
                if (_key.Equals(e.getKey()))
                {
                    return e.getValue();
                }
            }
            return null;
        }
    }
}
