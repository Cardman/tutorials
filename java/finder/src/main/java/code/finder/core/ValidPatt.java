package code.finder.core;

import java.util.regex.Pattern;

public final class ValidPatt {
    private final Pattern pattern;

    public ValidPatt(Pattern _pattern) {
        this.pattern = _pattern;
    }

    public Pattern getPattern() {
        return pattern;
    }
}
