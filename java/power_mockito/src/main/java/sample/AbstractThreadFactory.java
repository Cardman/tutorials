package sample;

public interface AbstractThreadFactory {
    AbstractThread newThread(Runnable _run);
}
