package code.mock;

import code.threads.AbstractFuture;
import code.threads.AbstractScheduledExecutorService;

public class MockScheduledExecutorService implements AbstractScheduledExecutorService {
    private boolean cancel;
    @Override
    public AbstractFuture scheduleAtFixedRate(Runnable runnable, long l, long l1) {
        return new MockFuture(cancel);
    }

    @Override
    public AbstractFuture scheduleAtFixedRateNanos(Runnable runnable, long l, long l1) {
        return new MockFuture(cancel);
    }

    @Override
    public void shutdown() {
        cancel = true;
    }
}
