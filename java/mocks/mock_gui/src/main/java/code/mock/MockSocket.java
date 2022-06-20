package code.mock;

import code.gui.initialize.AbstractBufferedReader;
import code.gui.initialize.AbstractSocket;

public class MockSocket implements AbstractSocket {
    private boolean cl;
    private final boolean ko;

    public MockSocket(boolean _k) {
        this.ko = _k;
    }

    @Override
    public AbstractBufferedReader getInput() {
        return new MockBufferedReader();
    }

    @Override
    public String println(String s) {
        if (cl) {
            return "";
        }
        return s+"\n";
    }

    @Override
    public void close() {
        cl = true;
    }

    @Override
    public boolean isKo() {
        return ko;
    }
}
