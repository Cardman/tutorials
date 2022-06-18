package code.mock;

import code.threads.AbstractAtomicLong;

public class MockAtomicLong implements AbstractAtomicLong {
    private long lgValue;
    public MockAtomicLong() {
        this(0);
    }

    public MockAtomicLong(long _i) {
        lgValue = _i;
    }

    @Override
    public long get() {
        return lgValue;
    }

    @Override
    public void set(long i) {
        lgValue = i;
    }

    @Override
    public boolean compareAndSet(long i, long i1) {
        if (lgValue == i) {
            lgValue = i1;
            return true;
        }
        return false;
    }

    @Override
    public long getAndSet(long i) {
        long old_ = lgValue;
        lgValue = i;
        return old_;
    }

    @Override
    public long getAndAdd(long i) {
        long old_ = lgValue;
        lgValue +=i;
        return old_;
    }

    @Override
    public long addAndGet(long i) {
        lgValue +=i;
        return lgValue;
    }

    @Override
    public long getAndIncrement() {
        long old_ = lgValue;
        lgValue++;
        return old_;
    }

    @Override
    public long incrementAndGet() {
        lgValue++;
        return lgValue;
    }

    @Override
    public long getAndDecrement() {
        long old_ = lgValue;
        lgValue--;
        return old_;
    }

    @Override
    public long decrementAndGet() {
        lgValue--;
        return lgValue;
    }

    @Override
    public void lazySet(long i) {
        lgValue = i;
    }
}
