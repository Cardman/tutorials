package sample;

import javax.sound.sampled.LineEvent;
import javax.sound.sampled.LineListener;

public final class Speak implements LineListener {

    private final SoundList window;

    public Speak(SoundList _window) {
        window = _window;
    }

    @Override
    public void update(LineEvent _event) {
        window.update(_event.getType().toString(), _event.getFramePosition());
    }

}
