using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace Util
{
    public abstract class CriteriaForSearching
    {
        protected static bool match(SearchingMode _searchMode, String _typedString, String _string)
        {
            if (_typedString == null)
            {
                return true;
            }
            if (_string == null)
            {
                return false;
            }
            if (_searchMode == SearchingMode.WHOLE_STRING)
            {
                if (!_string.Equals(_typedString))
                {
                    return false;
                }
            }
            if (_searchMode == SearchingMode.SUBSTRING)
            {
                if (!_string.Contains(_typedString))
                {
                    return false;
                }
            }
            if (_searchMode == SearchingMode.REG_EXP)
            {
                Regex reg_ = new Regex(_typedString);
                if (!reg_.IsMatch(_string))
                {
                    return false;
                }
            }
            if (_searchMode == SearchingMode.META_CHARACTER)
            {
                if (!StringList.match(_string, _typedString))
                {
                    return false;
                }
            }
            return true;
        }

        protected static bool match<T>(T _min, T _max, T _number) where T : IComparable<T>
        {
            if (_min == null)
            {
                if (_max == null)
                {
                    return true;
                }
                if (_max.CompareTo(_number) < 0)
                {
                    return false;
                }
                return true;
            }
            if (_max != null)
            {
                if (_max.CompareTo(_number) < 0)
                {
                    return false;
                }
            }
            if (_min.CompareTo(_number) > 0)
            {
                return false;
            }
            return true;
        }

        protected static bool match<T>(T? _enum, T? _element) where T : struct
        {
            if (_enum == null)
            {
                return true;
            }
            return _enum.Equals(_element);
        }

        protected static bool match(SelectedBoolean _selectedBoolean, bool _boolean)
        {
            if (_selectedBoolean == SelectedBoolean.YES_AND_NO)
            {
                return true;
            }
            return _selectedBoolean.getSelected() == _boolean;
        }

        protected static bool match(SearchingMode _searchMode, String _typedString, StringList _list)
        {
            if (_typedString == null || _typedString.isEmpty())
            {
                return true;
            }
            if (_searchMode == SearchingMode.WHOLE_STRING)
            {
                bool contained_ = false;
                foreach (String s in _list)
                {
                    if (s == null)
                    {
                        continue;
                    }
                    if (s.Equals(_typedString))
                    {
                        contained_ = true;
                        break;
                    }
                }
                if (!contained_)
                {
                    return false;
                }
            }
            if (_searchMode == SearchingMode.SUBSTRING)
            {
                bool contained_ = false;
                foreach (String s in _list)
                {
                    if (s == null)
                    {
                        continue;
                    }
                    if (s.Contains(_typedString))
                    {
                        contained_ = true;
                        break;
                    }
                }
                if (!contained_)
                {
                    return false;
                }
            }
            if (_searchMode == SearchingMode.REG_EXP)
            {
                if (_list.filter(_typedString).isEmpty())
                {
                    return false;
                }
            }
            if (_searchMode == SearchingMode.META_CHARACTER)
            {
                if (_list.filterByMultiWords(_typedString).isEmpty())
                {
                    return false;
                }
            }
            return true;
        }

        protected static bool matchClass(Type _class, Object _object)
        {
            if (_class == null)
            {
                return true;
            }
            return _class.IsAssignableFrom(_object.GetType());
        }
    }
}
