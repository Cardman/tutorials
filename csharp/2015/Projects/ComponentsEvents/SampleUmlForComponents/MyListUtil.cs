using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SampleUmlForComponents
{
    public static class MyListUtil
    {
        public static bool equals<T>(List<T> _list1, List<T> _list2)
        {
            if (_list1 == null)
            {
                return _list2 == null;
            }
            if (_list1.Count != _list2.Count)
            {
                return false;
            }
            int size_ = _list1.Count;
            for (int i = MyList<T>.FIRST_INDEX; i < size_; i++)
            {
                if (_list1[i] == null)
                {
                    if (_list2[i] != null)
                    {
                        return false;
                    }
                    continue;
                }
                /*if (_list1[i] is Number)
                {
                    if (_list2[i] is Number)
                    {
                        if (!Numbers.eq((Number)_list1.get(i), (Number)_list2.get(i)))
                        {
                            return false;
                        }
                        continue;
                    }
                    return false;
                }*/
                /*if (_list1[i] is Enum<?>) {
                    if (_list2[i] is Enum<?>) {
                        if (_list1[i] != _list2[i])
                        {
                            return false;
                        }
                        continue;
                    }
                    return false;
                }*/
                if (_list1[i] is List<object>)
                {
                    if (_list2[i] is List<object>)
                    {
                        if (!equals(_list1[i] as List<object>, _list2[i] as List<object>))
                        {
                            return false;
                        }
                        continue;
                    }
                    return false;
                }
                if (!_list1[i].Equals(_list2[i]))
                {
                    return false;
                }
            }
            return true;
        }

        public static bool eq<S>(List<S> _obj1, List<S> _obj2)
        {
            if (_obj1 == null)
            {
                return _obj2 == null;
            }
            return MyListUtil.equals(_obj1, _obj2);
        }

        public static bool equalsObjectSet<T>(MyList<T> _list1, IEnumerable<T> _list2)
        {
            MyList<Object> lsOne_ = new MyList<Object>();
            foreach (Object e in _list1)
            {
                lsOne_.Add(e);
            }
            foreach (Object e in _list2)
            {
                if (!lsOne_.containsObj(e))
                {
                    return false;
                }
            }
            MyList<Object> lsTwo_ = new MyList<Object>();
            foreach (Object e in _list2)
            {
                lsTwo_.Add(e);
            }
            foreach (Object e in _list1)
            {
                if (!lsTwo_.containsObj(e))
                {
                    return false;
                }
            }
            return true;
        }

        public static bool equalsSet<S>(MyList<S> _list1, IEnumerable<S> _list2)
        {
            foreach (S e in _list2)
            {
                if (!_list1.containsObj(e))
                {
                    return false;
                }
            }
            MyList<S> ls_ = new MyList<S>();
            foreach (S e in _list2)
            {
                ls_.Add(e);
            }
            foreach (S e in _list1)
            {
                if (!ls_.containsObj(e))
                {
                    return false;
                }
            }
            return true;
        }

        public static bool equalsSet<S>(MyList<S> _list1, MyList<S> _list2)
        {
            if (!_list1.containsAll(_list2))
            {
                return false;
            }
            if (!_list2.containsAll(_list1))
            {
                return false;
            }
            return true;
        }

        public static bool equalsSet<S>(MyList<S> _list1, MyList<S> _list2, bool _eqSize)
        {
            if (_eqSize)
            {
                if (_list1.Count != _list2.Count)
                {
                    return false;
                }
            }
            if (!_list1.containsAll(_list2))
            {
                return false;
            }
            if (!_list2.containsAll(_list1))
            {
                return false;
            }
            return true;
        }
        public static void sortComparable<T>(MyList<T> _list) where T : IComparable<T>
        {
            int size_ = _list.size();
            for (int i = MyList<T>.FIRST_INDEX; i < size_; i++)
            {
                int iSecond_ = i + 1;
                for (int j = iSecond_; j < size_; j++)
                {
                    int res_ = _list.get(i).CompareTo(_list.get(j));
                    if (res_ > 0)
                    {
                        T elt_ = _list[i];
                        _list[i] = _list[j];
                        _list[j] = elt_;
                    }
                }
            }
        }

        public static MyList<E> getReverse<E>(this IEnumerable<E> _it)
        {
            MyList<E> list_ = new MyList<E>(_it);
            return list_.getReverse();
        }

    }
}
