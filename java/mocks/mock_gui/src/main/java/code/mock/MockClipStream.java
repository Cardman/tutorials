package code.mock;

import code.maths.montecarlo.AbstractGenerator;
import code.stream.AbsClipStream;
import code.stream.LineShortListenable;
import code.util.CustList;

public class MockClipStream implements AbsClipStream {

    private boolean running;
    private final long microsecondLength;
    private final boolean wave;
    private final CustList<LineShortListenable> listeners = new CustList<LineShortListenable>();
    private long position;
    private final MockRand mockRand;
    public MockClipStream(AbstractGenerator _gen, long _length, boolean _wav) {
        mockRand = new MockRand(_gen);
        microsecondLength = _length;
        wave = _wav;
    }
    @Override
    public long getMicrosecondLength() {
        return microsecondLength;
    }

    @Override
    public boolean isRunning() {
        return running;
    }

    @Override
    public void addLineListener(LineShortListenable _lineShortListenable) {
        running = true;
        listeners.add(_lineShortListenable);
    }

    @Override
    public void resume() {
        running = true;
        for (LineShortListenable l: listeners) {
            if (wave) {
                l.update("start",position);
            } else {
                l.updateMp3("start",position);
            }
        }
    }

    @Override
    public void stop(long _l) {
        position = _l;
        running = false;
        for (LineShortListenable l: listeners) {
            if (wave) {
                l.update("stop",position);
            } else {
                l.updateMp3("stop",position);
            }
        }
    }

    @Override
    public boolean closeClipStream() {
        for (LineShortListenable l: listeners) {
            if (wave) {
                l.update("close",position);
            } else {
                l.updateMp3("close",position);
            }
        }
        return mockRand.edit();
    }

    public void setPosition(long _pos) {
        this.position = Math.max(_pos,0);
        if (position >= getMicrosecondLength()) {
            stop(position);
        }
    }
}
