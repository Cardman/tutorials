using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Util
{
    public sealed class Pagination
    {
        public const int NO_PRIORITY = 0;

        public const int MIN_PRIORITY = 1;
    }
    public abstract class Pagination<T, U, C, L>
        where T : Sorting where U : class where C : CriteriaForSearching where L : IMyList<object>
    {
        protected const int NO_PRIORITY = Pagination.NO_PRIORITY;

        protected const int MIN_PRIORITY = Pagination.MIN_PRIORITY;

        protected const int EQUALS_ELEMENTS = 0;

        private C criteria;

        private int numberPage = List.INDEX_NOT_FOUND_ELT;

        private int nbResultsPerPage = 1;

        private int line = List.INDEX_NOT_FOUND_ELT;

        private int delta = 1;

        public Pagination(C _criteria)
        {
            criteria = _criteria;
        }

        public void clear()
        {
            getResults().Clear();
            setLine(List.INDEX_NOT_FOUND_ELT);
            setNumberPage(List.INDEX_NOT_FOUND_ELT);
            getRendered().Clear();
        }

        protected abstract void search(L _list);

        protected abstract bool match(U _object);

        protected abstract bool sortable();

        protected abstract void sort();

        public void newSearch()
        {
            List<T> list_ = getResults().getKeys();
            foreach (T k in list_)
            {
                U value_ = getResults().getVal(k);
                if (match(value_))
                {
                    continue;
                }
                getResults().removeKey(k);
            }
            checkLine(List.INDEX_NOT_FOUND_ELT);
            if (!getResults().isEmpty())
            {
                begin();
            }
            else {
                setNumberPage(List.INDEX_NOT_FOUND_ELT);
                getRendered().Clear();
            }
        }

        public void checkLine(int _line)
        {
            if (line == _line)
            {
                line = List.INDEX_NOT_FOUND_ELT;
                return;
            }
            line = _line;
        }

        public int currentIndex()
        {
            if (line == List.INDEX_NOT_FOUND_ELT)
            {
                return line;
            }
            int index_ = numberPage * nbResultsPerPage + line;
            List<T> list_ = new List<T>(getResults().getKeys());
            return list_.ElementAt(index_).getIndex();
        }

        public U currentObject()
        {
            if (line == List.INDEX_NOT_FOUND_ELT)
            {
                return null;
            }
            int index_ = numberPage * nbResultsPerPage + line;
            //		List<T> list_ = new List<>(getResults().getKeys());
            //		return getResults().getVal(list_.get(index_));
            return getResults().getValue(index_);
        }

        public void changeNbResultsPerPage(int _nbResultsPerPage)
        {
            nbResultsPerPage = _nbResultsPerPage;
            if (!getRendered().isEmpty())
            {
                begin();
            }
        }

        public bool enabledPrevious()
        {
            return numberPage > List.FIRST_INDEX;
        }

        public void previous()
        {
            changePage(numberPage - 1);
        }

        public void previousDelta()
        {
            changePage(Math.Max(numberPage - delta, List.FIRST_INDEX));
        }

        public void begin()
        {
            changePage(List.FIRST_INDEX);
        }

        public bool enabledNext()
        {
            return numberPage + 1 < pages();
        }

        public void next()
        {
            changePage(numberPage + 1);
        }

        public void nextDelta()
        {
            changePage(Math.Min(numberPage + delta, pages() - 1));
        }

        public void end()
        {
            changePage(pages() - 1);
        }

        public void changePage(int _page)
        {
            if (numberPage != _page)
            {
                line = List.INDEX_NOT_FOUND_ELT;
            }
            numberPage = _page;
            calculateRendered();
        }

        public void calculateRendered()
        {
            MyList<T> list_ = new MyList<T>(getResults().getKeys());
            int end_ = nbResultsPerPage * (numberPage + 1);
            if (end_ > list_.size())
            {
                end_ = list_.size();
            }
            getRendered().Clear();
            if (end_ < nbResultsPerPage * numberPage)
            {
                return;
            }
            getRendered().AddRange(list_.sub(nbResultsPerPage * numberPage, end_));
        }

        public int pages()
        {
            if (getResults().size() % nbResultsPerPage == 0)
            {
                return getResults().size() / nbResultsPerPage;
            }
            return getResults().size() / nbResultsPerPage + 1;
        }

        protected abstract TreeMap<T, U> getResults();

        protected abstract MyList<T> getRendered();

        public C getCriteria()
        {
            return criteria;
        }

        public int getNumberPage()
        {
            return numberPage;
        }

        public void setNumberPage(int _numberPage)
        {
            numberPage = _numberPage;
        }

        public int getNbResultsPerPage()
        {
            return nbResultsPerPage;
        }

        public void setNbResultsPerPage(int _nbResultsPerPage)
        {
            nbResultsPerPage = _nbResultsPerPage;
            begin();
        }

        public int getLine()
        {
            return line;
        }

        public void setLine(int _line)
        {
            line = _line;
        }

        public int getDelta()
        {
            return delta;
        }

        public void setDelta(int _delta)
        {
            delta = _delta;
        }
    }
}
