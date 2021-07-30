using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SampleUmlForComponents
{
    public class Pair<T,S> : IPair<T,S>
    {
        private const String SEPARATOR = " ";

	    private T first;

        private S second;

        public Pair()
        {

        }
        public Pair(T _first, S _second)
        {
            first = _first;
            second = _second;
        }
        public Pair(Pair<T, S> _other)
        {
            first = _other.first;
            second = _other.second;
        }
        public static bool eq<T1, S1>(Pair<T1, S1> _pair1, Pair<T1, S1> _pair2)
        {
            if (_pair1 == null)
            {
                return _pair2 == null;
            }
            return _pair1.Equals(_pair2);
        }
        public override bool Equals(Object _obj)
        {
            if (_obj == null)
            {
                return false;
            }
            if (!(_obj is Pair<T,S>)) {
                return false;
            }
            Pair<T,S> pair_ = _obj as Pair<T, S>;
            if (first == null)
            {
                if (second == null)
                {
                    if (pair_.second != null)
                    {
                        return false;
                    }
                    return pair_.first == null;
                }
                if (!second.Equals(pair_.second))
                {
                    return false;
                }
                return pair_.first == null;
            }
            if (second == null)
            {
                if (!first.Equals(pair_.first))
                {
                    return false;
                }
                return pair_.second == null;
            }
            if (!first.Equals(pair_.first))
            {
                return false;
            }
            if (!second.Equals(pair_.second))
            {
                return false;
            }
            return true;
        }

        public T getFirst()
        {
            return first;
        }

        public void setFirst(T _first)
        {
            first = _first;
        }

        public S getSecond()
        {
            return second;
        }

        public void setSecond(S _second)
        {
            second = _second;
        }

        public override String ToString()
        {
            return first + SEPARATOR + second;
        }
    }
    public interface IPair<out T,out S>
    {
        T getFirst();
        S getSecond();
    }
}
