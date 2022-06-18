package code.mock;

import code.threads.AbstractDate;
import code.threads.AbstractDateFactory;

public class MockDate implements AbstractDate {
    private final long millis;

    public MockDate(long _m) {
        this.millis = _m;
    }

    @Override
    public String format(AbstractDateFactory _fact, String s) {
        return Long.toString(millis);
    }

    @Override
    public String format(long l, String s) {
        return Long.toString(millis);
    }


}
