using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Util
{
    public class TreeMap<K,V> : ListableEntries<K,V>, ListableKey, IComparableKeys
    {//SortedDictionary<K,V>,<K>
        private IComparer<K> comparator;
        [NonSerialized()]
        private MyList<Entry<K, V>> list = new MyList<Entry<K, V>>();

        public TreeMap()
        {
        }

        public TreeMap(IComparer<K> _cmp)
            //: base(_cmp)
        {
            comparator = _cmp;
        }

        public TreeMap(Map<K, V> _map)
        {
            putAllMap(_map);
        }
        public IComparer<K> getComparator()
        {
            return comparator;
        }
        public IMyList<IEntry> entryListGene()
        {
            return entryList();
        }
        public IMyList<object> getKeysGene()
        {
            MyList<object> keys_ = new MyList<object>();
            foreach (object o in getKeys())
            {
                keys_.Add(o);
            }
            return keys_;
        }

        internal void Clear()
        {
            list.Clear();
        }

        public object getGene(object _key)
        {
            return get(_key);
        }
        /*public TreeMap(SortedMap<K, V> _map)
        {
            super(_map);
        }*/

        public void putAllMap(ListableEntries<K, V> _m)
        {
            //setModified();
            foreach (Entry <K,V> e in _m.entryList())
            {
                put(e.getKey(), e.getValue());
            }
        }

        public void putAllTreeMap(TreeMap<K,V> _m)
        {
            //setModified();
            foreach (Entry <K,V > e in _m.entryList())
            {
                put(e.getKey(), e.getValue());
            }
        }

        public bool contains(K _key)
        {
            if (_key == null)
            {
                foreach (Entry<K, V> e in list)
                {
                    if (e.getKey() != null)
                    {
                        continue;
                    }
                    return true;
                }
                return false;
            }
            foreach (Entry<K, V> e in list)
            {
                if (!_key.Equals(e.getKey()))
                {
                    continue;
                }
                return true;
            }
            return false;
        }

        public bool has(V _value)
        {
            MyList<K> keys_ = new MyList<K>();
            if (_value == null)
            {
                foreach (Entry<K, V> e in list)
                {
                    if (getVal(e.getKey()) != null)
                    {
                        continue;
                    }
                    return true;
                }
                return false;
            }
            foreach (Entry<K, V> e in list)
            {
                if (!_value.Equals(getVal(e.getKey())))
                {
                    continue;
                }
                return true;
            }
            return false;
        }

        public V getVal(K _key)
        {
            return get(_key);
        }

        public void removeKey(K _key)
        {
            int i_ = 0;
            if (_key == null)
            {
                while (true)
                {
                    if (list.size() <= i_)
                    {
                        break;
                    }
                    if (list.get(i_).getKey() == null)
                    {
                        list.RemoveAt(i_);
                    }
                    i_++;
                }
                return;
            }
            while (true)
            {
                if (list.size() <= i_)
                {
                    break;
                }
                if (_key.Equals(list.get(i_).getKey()))
                {
                    list.RemoveAt(i_);
                }
                i_++;
            }
            /*foreach (Entry<K, V> e in list)
            {
                if (!_key.Equals(e.getKey()))
                {
                    i_++;
                    continue;
                }
                list.RemoveAt(i_);
            }*/
        }

        public V getValue(int _index)
        {
            return list.ElementAt(_index).getValue();
        }

        public K getKey(int _index)
        {
            return list.ElementAt(_index).getKey();
        }

        public MyList<K> getKeys(V _value)
        {
            MyList<K> keys_ = new MyList<K>();
            if (_value == null)
            {
                foreach (Entry<K, V> e in list)
                {
                    if (getVal(e.getKey()) != null)
                    {
                        continue;
                    }
                    keys_.Add(e.getKey());
                }
                return keys_;
            }
            foreach (Entry<K, V> e in list)
            {
                if (!_value.Equals(getVal(e.getKey())))
                {
                    continue;
                }
                keys_.Add(e.getKey());
            }
            return keys_;
        }

        public MyList<K> getKeys()
        {
            MyList<K> keys_ = new MyList<K>();
            foreach (Entry<K, V> e in list)
            {
                keys_.Add(e.getKey());
            }
            return keys_;
        }

        public IMyList<IEntry<K, V>> entryList()
        {
            //return new MyList<Entry<K, V>>(list);
            return list;
        }

        /*IMyList<IEntry<K, V>> entryList()
        {
            MyList<Entry<K, V>> list_ = new MyList<Entry<K, V>>();
            int l_ = Count;
            for (int i = 0; i < l_; i++)
            {
                list_.Add(new Entry<K, V>(Keys.ElementAt(i), Values.ElementAt(i)));
            }
            return list_;
        }*/

        public MyList<V> getValues(K _key)
        {
            MyList<V> values_ = new MyList<V>();
            if (_key == null)
            {
                foreach (Entry<K, V> e in list)
                {
                    if (e.getKey() != null)
                    {
                        continue;
                    }
                    values_.Add(e.getValue());
                }
                return values_;
            }
            foreach (Entry<K, V> e in list)
            {
                if (!_key.Equals(e.getKey()))
                {
                    continue;
                }
                values_.Add(e.getValue());
            }
            return values_;
        }
        public MyList<V> getValues()
        {
            MyList<V> values_ = new MyList<V>();
            foreach (Entry<K, V> e in list)
            {
                values_.Add(e.getValue());
            }
            return values_;
        }
        /*IEnumerator<IEntry<K, object>> IEnumerable<IEntry<K, object>>.GetEnumerator()
        {
            MyList<IEntry<K, object>> list_ = new MyList<IEntry<K, object>>();
            int l_ = Count;
            for (int i = 0; i < l_; i++)
            {
                list_.Add(new Entry<K, object>(Keys.ElementAt(i), Values.ElementAt(i)));
            }
            return list_.GetEnumerator();
        }*/

        IMyList<K> ListableKey<K, V>.getKeys()
        {
            MyList<K> keys_ = new MyList<K>();
            foreach (Entry<K, V> e in list)
            {
                keys_.Add(e.getKey());
            }
            return keys_;
        }

        public V get(object _key)
        {
            MyList<V> values_ = new MyList<V>();
            if (_key == null)
            {
                foreach (Entry<K, V> e in list)
                {
                    if (e.getKey() != null)
                    {
                        continue;
                    }
                    return e.getValue();
                }
                return default(V);
            }
            foreach (Entry<K, V> e in list)
            {
                if (!_key.Equals(e.getKey()))
                {
                    continue;
                }
                return e.getValue();
            }
            return default(V);
        }
        public int size()
        {
            return list.Count;
        }
        public bool isEmpty()
        {
            return list.Count == 0;
        }
        public void put(K _key, V _value)
        {
            int index_ = 0;
            if (comparator == null)
            {
                if (_key.GetType().IsValueType)
                {
                    object o_ = _key;
                    long elt_ = (long) o_;
                    while (true)
                    {
                        if (index_ >= list.size())
                        {
                            list.Add(new Entry<K, V>(_key, _value));
                            return;
                        }
                        Entry<K, V> c_ = list.ElementAt(index_);
                        object o2_ = c_.getKey();
                        int res_ = elt_.CompareTo((long)o2_);
                        if (res_ < 0)
                        {
                            list.Insert(index_, new Entry<K, V>(_key, _value));
                            return;
                        }
                        if (res_ == 0)
                        {
                            list.ElementAt(index_).setValue(_value);
                            return;
                        }
                        index_++;
                    }
                } else
                {
                    IComparable<K> elt_ = _key as IComparable<K>;
                    while (true)
                    {
                        if (index_ >= list.size())
                        {
                            list.Add(new Entry<K, V>(_key, _value));
                            return;
                        }
                        Entry<K, V> c_ = list.ElementAt(index_);
                        int res_ = elt_.CompareTo(c_.getKey());
                        if (res_ < 0)
                        {
                            list.Insert(index_, new Entry<K, V>(_key, _value));
                            return;
                        }
                        if (res_ == 0)
                        {
                            list.ElementAt(index_).setValue(_value);
                            return;
                        }
                        index_++;
                    }
                }
                
            } else
            {
                while (true)
                {
                    if (index_ >= list.size())
                    {
                        list.Add(new Entry<K, V>(_key, _value));
                        return;
                    }
                    Entry<K, V> c_ = list.ElementAt(index_);
                    int res_ = comparator.Compare(_key, c_.getKey());
                    if (res_ < 0)
                    {
                        list.Insert(index_, new Entry<K, V>(_key, _value));
                        return;
                    }
                    if (res_ == 0)
                    {
                        list.ElementAt(index_).setValue(_value);
                        return;
                    }
                    index_++;
                }
            }
            /*bool added_ = false;
            int index_ = 0;
            foreach (Entry<K, V> e in list)
            {
                if (e.getKey().Equals(_key))
                {
                    added_ = true;
                    break;
                }
                index_++;
            }
            if (!added_)
            {
                //Add(_key, _value);
                list.Add(new Entry<K, V>(_key, _value));
                if (comparator == null)
                {
                    int len_ = list.size();
                    for (int i = 0; i < len_; i++)
                    {
                        for (int j = i + 1; j < len_; j++)
                        {
                            Entry<K, V> e1_ = list.get(i);
                            Entry<K, V> e2_ = list.get(j);
                            K k1_ = e1_.getKey();
                            K k2_ = e2_.getKey();
                            IComparable<K> cmp1_ = k1_ as IComparable<K>;
                            int res_ = cmp1_.CompareTo(k2_);
                            if (res_ > 0)
                            {
                                list.swapIndexes(i, j);
                            }
                        }
                    }
                } else
                {
                    int len_ = list.size();
                    for (int i = 0; i < len_; i++)
                    {
                        for (int j = i + 1; j < len_; j++)
                        {
                            Entry<K, V> e1_ = list.get(i);
                            Entry<K, V> e2_ = list.get(j);
                            K k1_ = e1_.getKey();
                            K k2_ = e2_.getKey();
                            int res_ = comparator.Compare(k1_, k2_);
                            if (res_ > 0)
                            {
                                list.swapIndexes(i, j);
                            }
                        }
                    }
                }
            } else
            {
                //this[_key] = _value;
                list[index_].setValue(_value);
            }*/
        }
        public void applyChanges()
        {
            if (comparator == null)
            {
                int len_ = list.size();
                for (int i = 0; i < len_; i++)
                {
                    for (int j = i + 1; j < len_; j++)
                    {
                        Entry<K, V> e1_ = list.get(i);
                        Entry<K, V> e2_ = list.get(j);
                        K k1_ = e1_.getKey();
                        K k2_ = e2_.getKey();
                        IComparable<K> cmp1_ = k1_ as IComparable<K>;
                        int res_ = cmp1_.CompareTo(k2_);
                        if (res_ > 0)
                        {
                            list.swapIndexes(i, j);
                        }
                    }
                }
            } else
            {
                int len_ = list.size();
                for (int i = 0; i < len_; i++)
                {
                    for (int j = i + 1; j < len_; j++)
                    {
                        Entry<K, V> e1_ = list.get(i);
                        Entry<K, V> e2_ = list.get(j);
                        K k1_ = e1_.getKey();
                        K k2_ = e2_.getKey();
                        int res_ = comparator.Compare(k1_, k2_);
                        if (res_ > 0)
                        {
                            list.swapIndexes(i, j);
                        }
                    }
                }
            }
        }
    }
    public interface IComparableKeys
    {
        void applyChanges();
    }
}
