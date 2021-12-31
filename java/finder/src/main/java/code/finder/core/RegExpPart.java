package code.finder.core;

public final class RegExpPart {
    private final String part;
    private final int start;
    private final int end;

    public RegExpPart(String _part, int _start, int _end) {
        this.part = _part;
        this.start = _start;
        this.end = _end;
    }

    public String getPart() {
        return part;
    }

    public int getStart() {
        return start;
    }

    public int getEnd() {
        return end;
    }
}
