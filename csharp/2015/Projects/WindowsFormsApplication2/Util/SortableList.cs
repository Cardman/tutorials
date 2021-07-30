using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Util
{
    public class SortableList<T> : MyList<T> where T : IComparable<T>
    {
        /**
	*/
        public SortableList()
        {
        }

        /**
            @param _element
            @param _elements
        */
        public SortableList(T _element) : base(_element)
        {
        }

        /**
            @param _element
            @param _elements
        */
        public SortableList(T _element, T _elementTwo, params T[] _elements)
            : base(_element, _elementTwo, _elements)
        {
        }

        /**
            @param _elements
        */
        public SortableList(T[] _elements)
            : base(_elements)
        {
        }

        /**
            @param _c
        */
        public SortableList(IEnumerable<T> _c)
            : base(_c)
        {
        }

        public void removeComparableDuplicates()
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
                    if (get(i_).CompareTo(get(j_)) == 0)
                    {
                        RemoveAt(j_);
                    }
                    else {
                        j_++;
                    }
                }
                i_++;
            }
        }

        public void sort()
        {
            sortElts(new NaturalComparator<T>());
        }
    }
}
