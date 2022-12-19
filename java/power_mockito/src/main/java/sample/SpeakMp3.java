package sample;

import javazoom.jl.player.advanced.*;

public final class SpeakMp3 extends PlaybackListener {
    private static final String START_MP_3 = "start_mp3";
    private static final String STOP_MP_3 = "stop_mp3";
    private final SoundList window;

    public SpeakMp3(SoundList _window) {
        window = _window;
    }

    @Override
    public void playbackStarted(PlaybackEvent _event) {
        window.updateMp3(START_MP_3, _event.getFrame());
    }

    @Override
    public void playbackFinished(PlaybackEvent _event) {
        window.updateMp3(STOP_MP_3, _event.getFrame());
    }
}