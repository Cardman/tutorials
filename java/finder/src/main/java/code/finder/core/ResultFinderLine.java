package code.finder.core;

import code.util.CustList;

public final class ResultFinderLine {
    private final int next;
    private final boolean valid;

    private ResultFinderLine(int _next, boolean _valid) {
        this.next = _next;
        this.valid = _valid;
    }
    public static ResultFinderLine result(CustList<RegExpPart> _res, boolean _emptyFilter, int _index, String _input){
        boolean valid_ = true;
        int content_;
        if (_res.isEmpty()) {
            if (!_emptyFilter) {
                valid_ = false;
            }
            content_ = nextRow(_input, _index);
        } else {
            content_ = _res.last().getEnd()+1;
        }
        return new ResultFinderLine(content_,valid_);
    }

    private static int nextRow(String _input, int _index) {
        int nex_ = _input.indexOf('\n', _index);
        if (nex_ > -1) {
            return nex_ +1;
        }
        return _input.length();
    }
    public int getNext() {
        return next;
    }

    public boolean isValid() {
        return valid;
    }
}
