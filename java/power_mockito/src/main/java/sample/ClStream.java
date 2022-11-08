package sample;

public interface ClStream {
    long getMicrosecondLength();

    boolean isRunning();
    void resume();
    void addLineListener(SoundList _line);

    void stop(long _lastPosition);

    boolean closeClipStream();

}
