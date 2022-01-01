package code.finder.core;

import code.util.CustList;
import code.util.StringList;
import code.util.core.StringUtil;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

public final class FinderCore {

    private FinderCore(){
    }
    public static int nbMatches(StringList _contents, String _input, ValidPatt _regExp) {
        if (_regExp == null) {
            return 0;
        }
        Pattern pattern_ = _regExp.getPattern();
        int index_ = 0;
        int nb_ = 0;
        while (true) {
            CustList<RegExpPart> contentParts_ = extrContentString(_contents, _input, index_);
            int content_;
            if (contentParts_.isEmpty()) {
                if (!_contents.isEmpty()) {
                    return nb_;
                }
                content_ = nextRow(_input, index_);
            } else {
                content_ = contentParts_.last().getEnd()+1;
            }
            CustList<RegExpPart> regExpParts_ = extrRegExpString(pattern_, _input, index_);
            if (regExpParts_.isEmpty() && pattern_ != null) {
                return nb_;
            }
            nb_ += contentParts_.size() + regExpParts_.size();
            int regExp_ = nextIndexRegExp(regExpParts_, _input, index_);
            int next_ = Math.max(content_,regExp_);
            if (next_ >= _input.length()) {
                return nb_;
            }
            index_ = next_;
        }
    }


    public static ValidPatt patternOrNull(String _regExp) {
        if (_regExp.isEmpty()) {
            return new ValidPatt(null);
        }
        try {
            return new ValidPatt(Pattern.compile(_regExp));
        } catch (Exception e) {
            return null;
        }
    }

    private static CustList<RegExpPart> extrContentString(StringList _contents, String _input, int _from) {
        CustList<RegExpPart> res_ = new CustList<RegExpPart>();
        int indexContent_ = 0;
        int index_ = 0;
        while (true) {
            RegExpPart regExpPart_ = tryRegExpPart(_contents, _input, _from, index_, indexContent_);
            if (regExpPart_ == null) {
                if (_contents.isValidIndex(indexContent_)) {
                    return new CustList<RegExpPart>();
                }
                break;
            }
            res_.add(regExpPart_);
            indexContent_++;
            index_ = regExpPart_.getEnd()-_from+1;
        }
        return res_;
    }
    private static RegExpPart tryRegExpPart(StringList _contents, String _input, int _from, int _index, int _indexContent) {
        int next_ = _input.indexOf('\n', _index+_from);
        String curr_;
        if (next_ < 0) {
            curr_ = _input.substring(_index+_from);
        } else {
            curr_ = _input.substring(_index+_from,next_);
        }
        if (!_contents.isValidIndex(_indexContent)) {
            return null;
        }
        if (!StringUtil.match(curr_,_contents.get(_indexContent))) {
            return null;
        }
        return new RegExpPart(curr_,_from+_index,next_);
    }
    private static int nextIndexRegExp(CustList<RegExpPart> _res, String _input, int _from) {
        if (_res.isEmpty()) {
            return nextRow(_input,_from);
        }
        return _res.last().getEnd()+1;
    }

    private static int nextRow(String _input, int _index) {
        int nex_ = _input.indexOf('\n', _index);
        if (nex_ > -1) {
            return nex_ +1;
        }
        return _input.length();
    }
    private static CustList<RegExpPart> extrRegExpString(Pattern _patt, String _input, int _from) {
        CustList<RegExpPart> res_ = new CustList<RegExpPart>();
        if (_patt == null) {
            return res_;
        }
        Matcher matcher_ = _patt.matcher(_input.substring(_from));
        while (matcher_.find()) {
            String group_ = matcher_.group();
            res_.add(new RegExpPart(group_,matcher_.start(),matcher_.end()));
        }
        return res_;
    }

    public static StringList filterList(String _filter) {
        StringList out_ = new StringList();
        if (_filter.isEmpty()) {
            return out_;
        }
        StringBuilder str_ = new StringBuilder();
        boolean esc_ = false;
        int i = 0;
        int len_ = _filter.length();
        while (i < len_) {
            char ch_ = _filter.charAt(i);
            if (esc_) {
                esc_ = false;
                if (ch_ == 'n') {
                    out_.add(str_.toString());
                    str_.delete(0,str_.length());
                } else {
                    str_.append(ch_);
                }
                i++;
                continue;
            }
            if (ch_ == '\\') {
                esc_ = true;
            } else {
                str_.append(ch_);
            }
            i++;
        }
        out_.add(str_.toString());
        return out_;
    }
}
