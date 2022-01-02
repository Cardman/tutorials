package code.finder.core;

import java.util.regex.Pattern;

public final class ValidPatt {

    private final int index;
    private final String patt;
    private final Pattern pattern;
    private final boolean valid;

    public ValidPatt(Pattern _pattern) {
        this.pattern = _pattern;
        index = -1;
        patt = "";
        valid = true;
    }

    public ValidPatt(int _index, String _patt) {
        this.pattern = null;
        index = _index;
        patt = _patt;
        valid = false;
    }

    public Pattern getPattern() {
        return pattern;
    }

    public int getIndex() {
        return index;
    }

    public String getPatt() {
        return patt;
    }

    public boolean isValid() {
        return valid;
    }
}
