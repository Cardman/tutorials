package code.mock;

import code.threads.AbstractAtomicBoolean;

public class MockAtomicBoolean implements AbstractAtomicBoolean {
    private boolean value;
    public MockAtomicBoolean() {
        this(false);
    }
    public MockAtomicBoolean(boolean _v) {
        value = _v;
    }
    @Override
    public boolean get() {
        return value;
    }

    @Override
    public void set(boolean b) {
        value = b;
    }

    @Override
    public boolean compareAndSet(boolean b, boolean b1) {
        if (value == b) {
            value = b1;
            return true;
        }
        return false;
    }

    @Override
    public boolean getAndSet(boolean b) {
        boolean old_ = value;
        value = b;
        return old_;
    }

    @Override
    public void lazySet(boolean b) {
        value = b;
    }
}
