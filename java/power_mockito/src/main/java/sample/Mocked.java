package sample;

public final class Mocked implements AbsCompo {
    private String value;
    @Override
    public String getValue() {
        return value;
    }

    @Override
    public void setValue(String _v) {
        value = _v;
    }
}
