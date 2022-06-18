package code.mock;

import code.threads.AbstractDate;
import code.threads.AbstractDateFactory;

public class MockDateFactory implements AbstractDateFactory {
    @Override
    public AbstractDate newDate(long _l) {
        return new MockDate(_l);
    }

    @Override
    public long timeZone(long l) {
        return 0;
    }
}
