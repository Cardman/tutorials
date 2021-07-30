using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SampleUmlForComponents
{
    public class MyList<T> : List<T>, IEnumerable<T>, MyIList<T>
    {
        public const int INDEX_NOT_FOUND_ELT = -1;

        public const int FIRST_INDEX = 0;

        public const int SECOND_INDEX = 1;

        public const int ONE_ELEMENT = 1;

        public const int SIZE_EMPTY = 0;

        protected const string EMPTY_STRING = "";

        //private const string UNCHECKED = "unchecked";

        public MyList()
        {
        }

        public MyList(T _element)
        {
            Add(_element);
        }

        public MyList(T _element, T _elementTwo, params T[] _elements)
        {
            Add(_element);
            Add(_elementTwo);
            foreach (T e in _elements)
            {
                Add(e);
            }
        }

        public MyList(T[] _elements)
        {
            foreach (T e in _elements)
            {
                Add(e);
            }
        }

        public MyList(IEnumerable<T> _c)
        {
            foreach (T e in _c)
            {
                Add(e);
            }
        }
        public override sealed int GetHashCode()
        {
            return 1;
        }
        public static bool eqStrings(List<String> _list1, List<String> _list2)
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
            for (int i = FIRST_INDEX; i < size_; i++)
            {
                if (_list1[i] == null)
                {
                    if (_list2[i] != null)
                    {
                        return false;
                    }
                    continue;
                }
                if (!_list1[i].Equals(_list2[i]))
                {
                    return false;
                }
            }
            return true;
        }




        public bool isValidIndex(int _index)
        {
            if (_index < FIRST_INDEX)
            {
                return false;
            }
            if (_index >= size())
            {
                return false;
            }
            return true;
        }
        public int size()
        {
            return Count;
        }

        public MyList<T> intersect(MyList<T> _list)
        {
            MyList<T> list_ = new MyList<T>();
            foreach (T s in _list)
            {
                if (containsObj(s))
                {
                    //_list.containsObj(s)
                    list_.Add(s);
                }
            }
            return list_;
        }
        public T get(int _index)
        {
            return this[_index];
        }
        public Numbers<int> indexesOfObject(T _string)
        {
            Numbers<int> list_ = new Numbers<int>();
            int size_ = size();
            if (_string == null)
            {
                for (int i = FIRST_INDEX; i < size_; i++)
                {
                    if (get(i) == null)
                    {
                        list_.Add(i);
                    }
                }
            }
            else {
                for (int i = FIRST_INDEX; i < size_; i++)
                {
                    if (get(i) == null)
                    {
                        continue;
                    }
                    if (get(i).Equals(_string))
                    {
                        list_.Add(i);
                    }
                }
            }
            return list_;
        }

        public void swapIndexes(int _i, int _j)
        {
            T elt_ = this[_i];
            this[_i] = this[_j];
            this[_j] = elt_;
        }

        public void sortElts(IComparer<T> _comp)
        {
            Sort(_comp);
        }

        public void replace(T _old, T _new)
        {
            //setModified();
            int size_ = size();
            if (_old == null)
            {
                for (int i = FIRST_INDEX; i < size_; i++)
                {
                    if (get(i) == null)
                    {
                        set(i, _new);
                    }
                }
                return;
            }
            for (int i = FIRST_INDEX; i < size_; i++)
            {
                if (_old.Equals(get(i)))
                {
                    set(i, _new);
                }
            }
        }

        public void removeObj(T _obj)
        {
            //setModified();
            Remove(_obj);
        }

        public void removeAllObj(T _obj)
        {
            //setModified();
            while (containsObj(_obj))
            {
                Remove(_obj);
            }
        }

        public bool removedObj(T _obj)
        {
            //setModified();
            return Remove(_obj);
        }

        public virtual void removeDuplicates()
        {
            //setModified();
            int i_ = FIRST_INDEX;
            while (true)
            {
                if (i_ >= size())
                {
                    break;
                }
                int j_ = i_;
                j_++;
                while (true)
                {
                    if (j_ >= size())
                    {
                        break;
                    }
                    if (get(i_) == null)
                    {
                        if (get(j_) == null)
                        {
                            RemoveAt(j_);
                        }
                        else {
                            j_++;
                        }
                    }
                    /* else if (get(i_) is Number && get(j_) is Number) {
                         if (Numbers.eq((Number)get(i_), (Number)get(j_)))
                         {
                             remove(j_);
                         }
                         else {
                             j_++;
                         }
                     } */
                    else {
                        if (get(i_).Equals(get(j_)))
                        {
                            RemoveAt(j_);
                        }
                        else {
                            j_++;
                        }
                    }
                }
                i_++;
            }
        }

        public String join(String _join)
        {
            if (isEmpty())
            {
                return EMPTY_STRING;
            }
            StringBuilder return_ = new StringBuilder();
            return_.Append(get(FIRST_INDEX));
            int size_ = size();
            for (int i = SECOND_INDEX; i < size_; i++)
            {
                return_.Append(_join);
                return_.Append(get(i));
            }
            return return_.ToString();
        }
        public override string ToString()
        {
            return "["+join(" ")+"]";
        }
        public bool containsObj(T _element)
        {
            if (_element == null)
            {
                foreach (T e in this)
                {
                    if (e == null)
                    {
                        return true;
                    }
                }
                return false;
            }
            /*if (_element is Number) {
                foreach (T e in this)
                {
                    if (e == null)
                    {
                        continue;
                    }
                    if (e is Number) {
                        if (Numbers.eq((Number)_element, (Number)e))
                        {
                            return true;
                        }
                    }
                }
                return false;
            }
            if (_element is Enum<?>) {
                foreach (T e in this) {
                    if (e == _element)
                    {
                        return true;
                    }
                }
                return false;
            }*/
            if (_element is List<object>) {
                return Contains(_element);
                //			for (T e:this) {
                //				if (e instanceof List<?>) {
                //					if (equals((List<?>)_element,(List<?>)e)) {
                //						return true;
                //					}
                //				}
                //			}
                //			return false;
            }
            foreach (T e in this) {
                if (_element.Equals(e))
                {
                    return true;
                }
            }
            return false;
        }

        public bool containsAll(List<T> _list)
        {
            foreach (T e in _list)
            {
                if (!containsObj(e))
                {
                    return false;
                }
            }
            return true;
        }

        public int indexOfObj(T _element)
        {
            int i_ = FIRST_INDEX;
            if (_element == null)
            {
                foreach (T e in this)
                {
                    if (e == null)
                    {
                        return i_;
                    }
                    i_++;
                }
                return INDEX_NOT_FOUND_ELT;
            }
            foreach (T e in this)
            {
                if (_element.Equals(e))
                {
                    return i_;
                }
                i_++;
            }
            return INDEX_NOT_FOUND_ELT;
        }

        /*public T removeAt(Number _n)
        {
            return remove(_n.intValue());
        }*/

        public T first()
        {
            return get(FIRST_INDEX);
        }

        public T last()
        {
            return get(getLastIndex());
        }

        /**
        Returns the previous element at the specified position in this list.
        @param _index - index of the previous element to return */
        public T getPrev(int _index)
        {
            int index_ = _index;
            index_--;
            return get(index_);
        }

        /**
        Returns the next element at the specified position in this list.
        @param _index - index of the next element to return */
        public T getNext(int _index)
        {
            int index_ = _index;
            index_++;
            return get(index_);
        }

        public MyList<T> mid(int _beginIndex, int _nbElements)
        {
            if (_beginIndex + _nbElements > size())
            {
                return mid(_beginIndex);
            }
            return new MyList<T>(sub(_beginIndex, _beginIndex + _nbElements));
        }

        public MyList<T> mid(int _beginIndex)
        {
            return new MyList<T>(sub(_beginIndex, size()));
        }

        public void setLast(T _element)
        {
            set(getLastIndex(), _element);
        }
        public void set(int _index, T _element)
        {
            this[_index] = _element;
        }
        public int getLastIndex()
        {
            int last_ = size();
            last_--;
            return last_;
        }

        public MyList<MyList<T>> getGroupsSameCompare(IComparer<T> _cmp)
        {
            MyList<T> copy_ = new MyList<T>(this);
            copy_.sortElts(_cmp);
            MyList<MyList<T>> groups_;
            groups_ = new MyList<MyList<T>>();
            MyList<T> group_;
            group_ = new MyList<T>();
            int i_ = MyList<T>.FIRST_INDEX;
            int j_ = i_;
            j_--;
            while (i_ < copy_.size())
            {
                if (i_ > MyList<T>.FIRST_INDEX)
                {
                    int res_ = _cmp.Compare(copy_.get(i_), copy_.get(j_));
                    if (res_ != 0)
                    {
                        groups_.Add(group_);
                        group_ = new MyList<T>();
                    }
                }
                group_.Add(copy_.get(i_));
                i_++;
                j_++;
            }
            groups_.Add(group_);
            return groups_;
        }

        public void removeFirst()
        {
            if (isEmpty())
            {
                return;
            }
            RemoveAt(FIRST_INDEX);
        }

        public void removeLast()
        {
            if (isEmpty())
            {
                return;
            }
            RemoveAt(getLastIndex());
        }

        public bool isEmpty()
        {
            return Count == 0;
        }
        public MyList<T> getReverse()
        {
            MyList<T> list_ = new MyList<T>(this);
            int i_ = FIRST_INDEX;
            int j_ = list_.size();
            j_--;
            while (i_ < j_)
            {
                list_.swapIndexes(i_, j_);
                i_++;
                j_--;
            }
            return list_;
        }

        public MyList<T> sub(int _from, int _to)
        {
            if (_from > _to)
            {
                return new MyList<T>();
            }
            int b_ = Math.Max(_from, FIRST_INDEX);
            int e_ = Math.Min(_to, size());
            return subList(b_, e_);
        }

        public MyList<T> subList(int _from, int _to)
        {
            if (_from > _to)
            {
                return new MyList<T>();
            }
            return new MyList<T>(GetRange(Math.Max(_from, FIRST_INDEX), _to - _from + 1));
        }
    }
    public interface MyIList<out T> : IEnumerable<T>
    {
        T get(int _index);
        int size();
        T getPrev(int _index);
        T getNext(int _index);
        void swapIndexes(int _i, int _j);
        bool isEmpty();
        int getLastIndex();
        //MyIList<T> subList(int _from, int _to);
    }
    /*public interface MyList {
        bool isValidIndex(int _index);
        int size();

        MyList intersect<T>(List<T> _list);
        T get<T>(int _index);
        Numbers<int> indexesOfObject<T>(T _string);

        void swapIndexes(int _i, int _j);

        void sortElts<T>(IComparer<T> _comp);

        void replace<T>(T _old, T _new);

        void removeObj<T>(T _obj);

        void removeAllObj<T>(T _obj);

        bool removedObj<T>(T _obj);

        void removeDuplicates();

        String join(String _join);

        bool containsObj<T>(T _element);

        bool containsAll<T>(List<T> _list);

        int indexOfObj<T>(T _element);

        T first<T>();

        T last<T>();

        T getPrev<T>(int _index);

        T getNext<T>(int _index);

        MyList mid(int _beginIndex, int _nbElements);

        MyList mid(int _beginIndex);

        void setLast<T>(T _element);

        void set<T>(int _index, T _element);

        int getLastIndex();

        MyList getGroupsSameCompare<T>(IComparer<T> _cmp);

        void removeFirst();

        void removeLast();

        bool isEmpty();

        MyList getReverse();

        MyList sub(int _from, int _to);

        MyList subList(int _from, int _to);
    }*/
}
