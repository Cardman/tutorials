package sample;

public final class DefThreadFactory implements AbstractThreadFactory {
    @Override
    public AbstractThread newThread(Runnable _run) {
        return new DefThread(_run);
    }
}
