using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Util
{
    public interface ListableEntries<K,V> : ListableKey<K,V>//IEnumerable<IEntry<K, object>>,
    {
        //MyList<Entry<K, V>> entryList();

        void putAllMap(ListableEntries<K,V> _m);

        MyList<V> getValues(K _key);
        V getVal(K _key);
    }
    public interface ListableKey
    {
        IMyList<IEntry> entryListGene();
        IMyList<object> getKeysGene();
        object getGene(object _obj);
    }
    public interface ListableKey<out K,out V>
    {
        IMyList<IEntry<K, V>> entryList();
        IMyList<K> getKeys();
        V get(object _obj);
    }
    public static class Entries
    {
        public static IMyList<K> getKeys<K>(this IEnumerable<IEntry<K, object>> _map)
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
