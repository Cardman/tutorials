package sample;

public final class DefThread implements AbstractThread {
    private final Thread thread;

    public DefThread(Runnable _run) {
        thread = new Thread(_run);
    }

    @Override
    public boolean isAlive() {
        return thread.isAlive();
    }

    @Override
    public void start() {
        thread.start();
    }
}
