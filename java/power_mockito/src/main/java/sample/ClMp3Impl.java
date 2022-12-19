package sample;

import javazoom.jl.player.advanced.*;

import java.io.*;

public final class ClMp3Impl implements ClStream {
    private final byte[] bytes;
    private AdvancedPlayer pl;
    private final AbstractThreadFactory abstractThreadFactory;
    private AbstractThread abstractThread;
    private long frame;
    private final long rat;
    private final long microsecondLength;
    private SpeakMp3 speakingMp3Event;

    public ClMp3Impl(byte[] _bs, AbstractThreadFactory _fact, long _micros, long _ratio) {
        bytes = _bs;
        abstractThreadFactory = _fact;
        rat = _ratio;
        microsecondLength = _micros;
    }

    static AdvancedPlayer player(byte[] _file) {
        try {
            return new AdvancedPlayer(new ByteArrayInputStream(_file));
        } catch (Exception e) {
            return null;
        }
    }

    public long getFramePosition() {
        return frame;
    }

    @Override
    public long getMicrosecondLength() {
        return microsecondLength;
    }

    @Override
    public boolean isRunning() {
        try {
            return abstractThread.isAlive();
        } catch (Exception e) {
            return false;
        }
    }

    @Override
    public void addLineListener(SoundList _line) {
        speakingMp3Event = new SpeakMp3(_line);
        startMp3(0);
    }

    @Override
    public void resume() {
        startMp3((int) getFramePosition());
    }

    public void startMp3(int _framePosition) {
        pl = player(bytes);
        loop(_framePosition);
    }

    private void loop(int _framePosition) {
        pl.setPlayBackListener(speakingMp3Event);
        abstractThread = abstractThreadFactory.newThread(new RunMp3(pl, _framePosition));
        abstractThread.start();
    }

    @Override
    public void stop(long _lastPosition) {
        frame = (_lastPosition / 1000) / Math.max(rat,1);
        pl.stop();
    }

    @Override
    public boolean closeClipStream() {
        try {
            pl.close();
            return true;
        } catch (Exception e) {
            return false;
        }
    }

    static boolean play(AdvancedPlayer _player, int _frames) {
        try {
            return _player.play(_frames, Integer.MAX_VALUE);
        } catch (Exception e) {
            return false;
        }
    }
}
