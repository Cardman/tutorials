using SampleUmlForComponents;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace SampleUmlForComponents
{
    public class StringList : MyList<string>
    {
        public const String BACK_SLASH = "\\";

	    public const String BOUNDS = "\\b";

	    public const String CHAR_WORD = "\\w";

	    public const String LEFT_PAR_REG_EXP = "(";

	    public const String RIGHT_PAR_REG_EXP = ")";

	    public const String BEGIN_REG_EXP = "^";

	    public const int WHOLE_STRING = 1;

        public const int SUBSTRING = 2;

        public const int META_CHARACTER = 3;

        public const int REG_EXP = 4;

        public const String OR_REG_EXP = "|";

	    public const String END_REG_EXP = "$";

	    public const String LEFT_CLASS_REG_EXP = "[";

	    public const String RIGHT_CLASS_REG_EXP = "]";

	    public const char LEFT_PAR = '(';

        public const char RIGHT_PAR = ')';

        public const char LEFT_BRACE = '{';

        public const char RIGHT_BRACE = '}';

        public const String PIPE = "|";

	    public const String POINT = ".";

	    public const String AT_LEAST ="+";

	    public const String POSSIBLE ="*";

	    public const String NO_MORE_ONE = "?";
        
	    private static String ESCAPED_META { get; } = escapedMeta();

        private const char CHARACTER = '.';

        private const char STRING = '*';

        private const char POSSIBLE_CHAR = '?';

        private const char ESCAPING_CHAR = '\\';

        private const char QUOTE = '\'';

        private const char LT = '<';

        private const char GT = '>';

        private const char COMMA = ',';

        private const String VAR_REG_EXP = "$1";

        public StringList()
        {
        }

        public StringList(List<String> _list) : base(_list)
        {
        }

        public StringList(String[] _array)
        {
            foreach (String s in _array)
            {
                Add(s);
            }
        }

        public StringList(String _string, params String[] _strings)
        {
            Add(_string);
            foreach (String s in _strings)
            {
                Add(s);
            }
        }

        static String escapedMeta()
        {
            String escaped_ = StringList.BACK_SLASH;
            StringList list_ = new StringList();
            list_.Add(POSSIBLE);
            list_.Add(AT_LEAST);
            list_.Add(LEFT_CLASS_REG_EXP);
            list_.Add(RIGHT_CLASS_REG_EXP);
            list_.Add(char.ToString(LEFT_BRACE));
            list_.Add(char.ToString(RIGHT_BRACE));
            list_.Add(char.ToString(LEFT_PAR));
            list_.Add(char.ToString(RIGHT_PAR));
            list_.Add(POINT);
            list_.Add(PIPE);
            escaped_ += list_.join(PIPE + StringList.BACK_SLASH);
            return pars(escaped_);
        }
        public override bool Equals(object _obj)
        {
            if (!(_obj is StringList))
            {
                return false;
            }
            StringList list_ = _obj as StringList;
            if (list_.size() != size())
            {
                return false;
            }
            int len_ = size();
            for (int i = 0; i < len_; i++)
            {
                if (get(i).Equals(list_.get(i)))
                {
                    continue;
                }
                return false;
            }
            return true;
        }
        public static String pars(String _exp)
        {
            return LEFT_PAR_REG_EXP + _exp + RIGHT_PAR_REG_EXP;
        }

        public static String wholeString(String _string)
        {
            return BEGIN_REG_EXP + _string + END_REG_EXP;
        }

        public static String beginString(String _string)
        {
            return BEGIN_REG_EXP + _string;
        }

        public static String endString(String _string)
        {
            return _string + END_REG_EXP;
        }

        public static String quote(String _string)
        {
            Regex rgx_ = new Regex(ESCAPED_META);
            return rgx_.Replace(_string, BACK_SLASH + BACK_SLASH + VAR_REG_EXP);
        }

        public static String classOfCharacters(params String[] _args)
        {
            StringList escaped_ = new StringList();
            foreach (String s in _args)
            {
                escaped_.Add(quote(s));
            }
            return LEFT_CLASS_REG_EXP + escaped_.join(EMPTY_STRING) + RIGHT_CLASS_REG_EXP;
        }

        public static String outOfClassOfCharacters(params String[] _args)
        {
            StringList escaped_ = new StringList();
            foreach (String s in _args)
            {
                escaped_.Add(quote(s));
            }
            return LEFT_CLASS_REG_EXP + BEGIN_REG_EXP + escaped_.join(EMPTY_STRING) + RIGHT_CLASS_REG_EXP;
        }

        //	public boolean isValid() {
        //		return areInstance(String.class);
        //	}

        public static bool eq(String _string1, String _string2)
        {
            return _string1.Equals(_string2);
        }

        public static String skipStringUntil(String _string, String _search)
        {
            return _string.Substring(_string.IndexOf(_search) + ONE_ELEMENT);
        }

        public void sort()
        {
            //setModified();
            sortElts(new NaturalComparator<string>());
        }

        public void replaceInStrings(String _replaced, String _replacing)
        {
            //setModified();
            int size_ = size();
            for (int i = FIRST_INDEX; i < size_; i++)
            {
                set(i, get(i).Replace(_replaced, _replacing));
            }
        }

        public List<int> indexesOfString(String _string)
        {
            List<int> list_ = new List<int>();
            int size_ = size();
            for (int i = FIRST_INDEX; i < size_; i++)
            {
                if (eq(get(i), _string))
                {
                    list_.Add(i);
                }
            }
            return list_;
        }

        public List<int> indexesOfSubstring(String _subSubstring)
        {
            List<int> list_ = new List<int>();
            int size_ = size();
            for (int i = FIRST_INDEX; i < size_; i++)
            {
                if (get(i).Contains(_subSubstring))
                {
                    list_.Add(i);
                }
            }
            return list_;
        }
        public List<int> indexesOfRegExp(String _regExp)
        {
            List<int> list_ = new List<int>();
            int size_ = size();
            for (int i = FIRST_INDEX; i < size_; i++)
            {
                if (!matchingRegExp(get(i), _regExp).isEmpty())
                {
                    list_.Add(i);
                }
            }
            return list_;
        }
        public List<int> indexesOfMultiWords(String _exp)
        {
            List<int> list_ = new List<int>();
            int size_ = size();
            for (int i = FIRST_INDEX; i < size_; i++)
            {
                if (match(get(i), _exp))
                {
                    list_.Add(i);
                }
            }
            return list_;
        }
        public void replaceRegExpInStrings(String _replacedRegExp, String _replacing)
        {
            //setModified();
            int size_ = size();
            for (int i = FIRST_INDEX; i < size_; i++)
            {
                Regex rgx_ = new Regex(_replacedRegExp);
                set(i, rgx_.Replace(get(i), _replacing));
            }
        }

        public StringList filterByMultiWords(String _exp)
        {
            StringList list_ = new StringList();
            foreach (String s in this)
            {
                if (!match(s, _exp))
                {
                    continue;
                }
                list_.Add(s);
            }
            return list_;
        }
        public StringList filter(String _regExp)
        {
            StringList list_ = new StringList();
            Regex patt_ = new Regex(_regExp);
            foreach (String s in this)
            {
                if (!patt_.Match(s).Success)
                {
                    continue;
                }
                list_.Add(s);
            }
            return list_;
        }

        public StringList filterIgnoreCase(String _regExp)
        {
            StringList list_ = new StringList();
            Regex patt_ = new Regex(_regExp.ToUpper());
            foreach (String s in this)
            {
                if (!patt_.Match(s.ToUpper()).Success)
                {
                    continue;
                }
                list_.Add(s);
            }
            return list_;
        }

        public void removeString(String _string)
        {
            base.Remove(_string);
        }

        public static StringList getTokensSeparators(String _string, String _regExpToken)
        {
            int index_ = FIRST_INDEX;
            Regex patt_ = new Regex(_regExpToken);
            StringList list_ = new StringList();
            while (index_ < _string.Count())
            {
                String sub_ = _string.Substring(index_);
                Match m_ = patt_.Match(sub_);
                if (m_.Success)
                {
                    String token_ = m_.Value;
                    int next_ = sub_.IndexOf(token_);
                    list_.Add(sub_.Substring(FIRST_INDEX, next_));
                    list_.Add(token_);
                    index_ += next_ + token_.Count();
                }
                else {
                    list_.Add(sub_);
                    break;
                }
            }
            return list_;
        }

        public static bool match(String _string, String _filter)
        {
            if (_filter.isEmpty())
            {
                return true;
            }
            Pair<Pair<StringList, StringList>, Pair<Boolean, Boolean>> wordsAndSeparators_
                = wordsAndSeparators(_filter);
            Console.WriteLine(wordsAndSeparators_);
            StringList words_ = wordsAndSeparators_.getFirst().getSecond();
            StringList separators_ = wordsAndSeparators_.getFirst().getFirst();
            String lastSep_;
            int nbPts_ = SIZE_EMPTY;
            int nbZeroOne_ = SIZE_EMPTY;
            int index_ = FIRST_INDEX;
            if (words_.isEmpty())
            {
                lastSep_ = separators_.last();
                nbPts_ = 0;
                nbZeroOne_ = 0;
                index_ = FIRST_INDEX;
                foreach (char c in lastSep_.ToCharArray())
                {
                    if (c == CHARACTER)
                    {
                        nbPts_++;
                    }
                    if (c == POSSIBLE_CHAR)
                    {
                        nbZeroOne_++;
                    }
                }
                index_ += nbPts_;
                if (index_ == _string.Count())
                {
                    return true;
                }
                if (index_ < _string.Count())
                {
                    if (lastSep_.Contains(char.ToString(STRING)))
                    {
                        return true;
                    }
                    if (_string.Count() <= index_ + nbZeroOne_)
                    {
                        return true;
                    }
                }
                return false;
            }
            if (wordsAndSeparators_.getSecond().getFirst())
            {
                separators_.Insert(FIRST_INDEX, EMPTY_STRING);
            }
            //BEGIN MODIF
            /*if (separators_.isEmpty())
            {
                if (wordsAndSeparators_.getSecond().getSecond())
                {
                    separators_.Add(EMPTY_STRING);
                }
            }*/
            //END MODIF
            if (wordsAndSeparators_.getSecond().getSecond())
            {
                separators_.Add(EMPTY_STRING);
            }
            int i_ = FIRST_INDEX;
            index_ = FIRST_INDEX;
            int indiceRDecalePt_ = 0;
            int indiceNext_ = 0;
            foreach (String e in words_)
            {
                String sep_ = separators_.get(i_);
                nbPts_ = 0;
                nbZeroOne_ = 0;
                foreach (char c in sep_.ToCharArray())
                {
                    if (c == CHARACTER)
                    {
                        nbPts_++;
                    }
                    if (c == POSSIBLE_CHAR)
                    {
                        nbZeroOne_++;
                    }
                }
                indiceRDecalePt_ = index_ + nbPts_;
                //indiceNext_ = _string.IndexOf(e, indiceRDecalePt_);
                if (separators_.get(i_).Contains(char.ToString(STRING)))
                {
                    if (words_.isValidIndex(i_ + 1)) {
                        indiceNext_ = _string.IndexOf(e, indiceRDecalePt_);
                    //indiceNext_ = greatestIndex(_string, e, indiceRDecalePt_);
                        if (indiceNext_ == INDEX_NOT_FOUND_ELT)
                        {
                            return false;
                        }
                    } else {
                        indiceNext_ = greatestIndex(_string, e, indiceRDecalePt_);
                        if (indiceNext_ == INDEX_NOT_FOUND_ELT)
                        {
                            return false;
                        }
                    }
                    
                }
                else {
                    indiceNext_ = _string.IndexOf(e, indiceRDecalePt_);
                    if (indiceRDecalePt_ > indiceNext_ || indiceRDecalePt_ < indiceNext_ - nbZeroOne_)
                    {
                        return false;
                    }
                }
                index_ = indiceNext_ + e.Count();
                i_++;
            }
            Console.WriteLine(separators_);
            lastSep_ = separators_.last();
            Console.WriteLine(lastSep_+"%"+_string+"%"+_filter);
            nbPts_ = 0;
            nbZeroOne_ = 0;
            foreach (char c in lastSep_.ToCharArray())
            {
                if (c == CHARACTER)
                {
                    nbPts_++;
                }
                if (c == POSSIBLE_CHAR)
                {
                    nbZeroOne_++;
                }
            }
            index_ += nbPts_;
            if (index_ == _string.Count())
            {
                return true;
            }
            if (index_ < _string.Count())
            {
                if (lastSep_.Contains(char.ToString(STRING)))
                {
                    return true;
                }
                if (_string.Count() <= index_ + nbZeroOne_)
                {
                    return true;
                }
            }
            return false;
        }
        static int greatestIndex(String _string, String _substring, int _offset)
        {
            String start_ = _string.Substring(_offset);
            if (!start_.Contains(_substring))
            {
                return INDEX_NOT_FOUND_ELT;
            }
            int index_ = FIRST_INDEX;
            int return_ = FIRST_INDEX;
            while (true)
            {
                return_ = index_;
                return_--;
                int ind_ = start_.IndexOf(_substring, index_);
                if (ind_ != INDEX_NOT_FOUND_ELT)
                {
                    index_ = ind_ + 1;
                }
                else {
                    break;
                }
            }
            return return_ + _offset;
        }
        private static Pair<Pair<StringList, StringList>, Pair<Boolean, Boolean>> wordsAndSeparators(String _string)
        {
            Pair<Pair<StringList, StringList>, Pair<Boolean, Boolean>> wordsSepBeginEnd_;
            wordsSepBeginEnd_ = new Pair<Pair<StringList, StringList>, Pair<Boolean, Boolean>>();
            wordsSepBeginEnd_.setSecond(new Pair<Boolean, Boolean>(false, false));
            Pair<StringList, StringList> wordsAndSeparators_ = new Pair<StringList, StringList>();
            StringList words_ = new StringList();
            StringList separators_ = new StringList();
            MyList<char> metas_ = getMetaCharacters();
            int begin_ = FIRST_INDEX;
            while (true)
            {
                int minIndex_ = lowestIndexOfMetaChar(_string, begin_, metas_);
                Console.WriteLine(minIndex_+"%%%%");
                if (minIndex_ == INDEX_NOT_FOUND_ELT)
                {
                    if (begin_ < _string.Count())
                    {
                        words_.Add(_string.Substring(begin_));
                    }
                    if (begin_ == FIRST_INDEX)
                    {
                        wordsSepBeginEnd_.getSecond().setFirst(true);
                    }
                    wordsSepBeginEnd_.getSecond().setSecond(begin_ < _string.Count());
                    break;
                }
                if (minIndex_ > begin_)
                {
                    words_.Add(_string.Substring(begin_, minIndex_ - begin_));
                    if (begin_ == FIRST_INDEX)
                    {
                        wordsSepBeginEnd_.getSecond().setFirst(true);
                    }
                }
                int ind_ = lowestIndexOfWordChar(_string, minIndex_, metas_);
                //ind_ < _string.length() ==> all character after or at minIndex_ are meta characters
                //so if ind_ is lower than the length of the string _string,
                //then this string does not end with a character of word
                if (ind_ > minIndex_)
                {
                    separators_.Add(_string.Substring(minIndex_, ind_ - minIndex_));
                }
                begin_ = ind_;
            }
            wordsAndSeparators_.setFirst(separators_);
            wordsAndSeparators_.setSecond(words_);
            int nbWords_ = wordsAndSeparators_.getSecond().size();
            for (int i = FIRST_INDEX; i < nbWords_; i++)
            {
                String escapedString_ = escape(wordsAndSeparators_.getSecond().get(i));
                wordsAndSeparators_.getSecond().set(i, escapedString_);
            }
            wordsSepBeginEnd_.setFirst(wordsAndSeparators_);
            return wordsSepBeginEnd_;
        }

        static int lowestIndexOfMetaChar(String _string,
                int _begin,
                List<char> _metas)
        {
            int minIndex_ = INDEX_NOT_FOUND_ELT;
            foreach (char s in _metas)
            {
                int index_ = indexOf(_string, _begin, s);
                if (index_ == INDEX_NOT_FOUND_ELT)
                {
                    continue;
                }
                if (minIndex_ == INDEX_NOT_FOUND_ELT)
                {
                    minIndex_ = index_;
                }
                else {
                    minIndex_ = Math.Min(minIndex_, index_);
                }
            }
            return minIndex_;
        }

        static int lowestIndexOfWordChar(String _string,
                int _minIndex,
                MyList<char> _metas)
        {
            int ind_ = _minIndex;
            while (ind_ < _string.Count())
            {
                if (!_metas.containsObj(_string.ElementAt(ind_)))
                {
                    break;
                }
                ind_++;
            }
            return ind_;
        }

        private static int indexOf(String _input, int _begin, char _meta)
        {
            int index_ = _input.IndexOf(_meta, _begin);
            if (index_ == FIRST_INDEX || index_ == INDEX_NOT_FOUND_ELT)
            {
                return index_;
            }
            while (true)
            {
                int i_ = index_ - 1;
                int nbSl_ = 0;
                while (i_ >= _begin)
                {
                    if (_input.ElementAt(i_) != ESCAPING_CHAR)
                    {
                        break;
                    }
                    nbSl_++;
                    i_--;
                }
                if (nbSl_ % 2 == 0)
                {
                    break;
                }
                int ind_ = _input.IndexOf(_meta, index_ + 1);
                if (ind_ == INDEX_NOT_FOUND_ELT)
                {
                    index_ = INDEX_NOT_FOUND_ELT;
                    break;
                }
                index_ = ind_;
            }
            return index_;
        }

        public static StringList getTypes(String _type)
        {
            StringList types_ = new StringList();
            int i_ = _type.IndexOf(char.ToString(LT));
            if (i_ == INDEX_NOT_FOUND_ELT)
            {
                return types_;
            }
            i_++;
            int nbGt_ = 0;
            int nbLt_ = 0;
            int first_ = i_;
            while (true)
            {
                if (i_ >= _type.Count() - 1)
                {
                    types_.Add(_type.Substring(first_, i_ - first_));
                    break;
                }
                if (_type.ElementAt(i_) == COMMA)
                {
                    if (nbGt_ == nbLt_)
                    {
                        types_.Add(_type.Substring(first_, i_ - first_));
                        first_ = i_ + 1;
                    }
                }
                if (_type.ElementAt(i_) == LT)
                {
                    nbGt_++;
                }
                if (_type.ElementAt(i_) == GT)
                {
                    nbLt_++;
                }
                i_++;
            }
            return types_;
        }

        public static MyList<char> getMetaCharacters()
        {
            MyList<char> list_ = new MyList<char>();
            list_.Add(CHARACTER);
            list_.Add(STRING);
            list_.Add(POSSIBLE_CHAR);
            return list_;
        }

        public MyList<StringList> catchRegExp(String _regExp)
        {
            MyList<StringList> list_ = new MyList<StringList>();
            foreach (String s in this)
            {
                list_.Add(matchingRegExp(s, _regExp));
            }
            return list_;
        }

        public static StringList matchingRegExp(String _string, String _regExp)
        {
            Match m_ = new Regex(_regExp).Match(_string);
            StringList list_ = new StringList();
            while (m_.Success)
            {
                list_.Add(m_.Value);
                m_ = m_.NextMatch();
            }
            return list_;
        }

        public bool containsStr(String _string)
        {
            return Contains(_string);
        }

        public StringList stringsEqualsIgnoreCase(String _string)
        {
            StringList list_ = new StringList();
            foreach (String s in this)
            {
                if (s == null)
                {
                    continue;
                }
                if (string.Equals(s, _string, StringComparison.OrdinalIgnoreCase))
                {
                    list_.Add(s);
                }
            }
            return list_;
        }

        public static bool disjoint(MyList<StringList> _list)
        {
            int size_ = _list.size();
            for (int i = MyList<object>.FIRST_INDEX; i < size_; i++)
            {
                for (int j = MyList<object>.FIRST_INDEX; j < size_; j++)
                {
                    if (i == j)
                    {
                        continue;
                    }
                    if (!_list.get(i).disjoint(_list.get(j)))
                    {
                        return false;
                    }
                }
            }
            return true;
        }

        public bool disjoint(StringList _list)
        {
            foreach (String s in _list)
            {
                if (containsObj(s))
                {
                    return false;
                }
            }
            return true;
        }

        public static String escape(String _input)
        {
            int length_ = _input.Count();
            char[] newArray_ = new char[length_];
            int i_ = FIRST_INDEX;
            int j_ = FIRST_INDEX;
            int newLength_ = length_;
            while (i_ < length_)
            {
                char c_ = _input.ElementAt(i_);
                if (c_ == ESCAPING_CHAR)
                {
                    int next_ = i_;
                    next_++;
                    if (next_ < length_)
                    {
                        switch (_input.ElementAt(next_))
                        {
                            case CHARACTER:
                            case STRING:
                            case POSSIBLE_CHAR:
                            case ESCAPING_CHAR:
                                i_++;
                                c_ = _input.ElementAt(i_);
                                newLength_--;
                                break;
                            default:
                                break;
                        }
                    }
                }
                newArray_[j_] = c_;
                j_++;
                i_++;
            }
            return new String(newArray_, FIRST_INDEX, newLength_);
        }

        public static char getCharacter()
        {
            return CHARACTER;
        }

        public static char getString()
        {
            return STRING;
        }

        public static char getPossibleChar()
        {
            return POSSIBLE_CHAR;
        }

        public static char getEscapingChar()
        {
            return ESCAPING_CHAR;
        }

        public override void removeDuplicates()
        {
            //setModified();
            int i_ = FIRST_INDEX;
            while (true)
            {
                if (i_ >= size())
                {
                    break;
                }
                int j_ = i_ + 1;
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
                        continue;
                    }
                    if (eq(get(i_), get(j_)))
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
    }
    public static class Extensions
    {
        public static bool isEmpty(this string _str)
        {
            return _str.Count() == 0;
        }
    }
}
