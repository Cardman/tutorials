package code.mock;

import code.threads.AbstractAtomicInteger;

public class MockAtomicInteger implements AbstractAtomicInteger {
    private int integer;
    public MockAtomicInteger() {
        this(0);
    }

    public MockAtomicInteger(int _i) {
        integer = _i;
    }

    @Override
    public int get() {
        return integer;
    }

    @Override
    public void set(int i) {
        integer = i;
    }

    @Override
    public boolean compareAndSet(int i, int i1) {
        if (integer == i) {
            integer = i1;
            return true;
        }
        return false;
    }

    @Override
    public int getAndSet(int i) {
        int old_ = integer;
        integer = i;
        return old_;
    }

    @Override
    public int getAndAdd(int i) {
        int old_ = integer;
        integer+=i;
        return old_;
    }

    @Override
    public int addAndGet(int i) {
        integer+=i;
        return integer;
    }

    @Override
    public int getAndIncrement() {
        int old_ = integer;
        integer++;
        return old_;
    }

    @Override
    public int incrementAndGet() {
        integer++;
        return integer;
    }

    @Override
    public int getAndDecrement() {
        int old_ = integer;
        integer--;
        return old_;
    }

    @Override
    public int decrementAndGet() {
        integer--;
        return integer;
    }

    @Override
    public void lazySet(int i) {
        integer = i;
    }
}
