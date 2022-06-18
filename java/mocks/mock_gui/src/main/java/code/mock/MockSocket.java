package code.mock;

import code.gui.initialize.AbstractBufferedReader;
import code.gui.initialize.AbstractSocket;

public class MockSocket implements AbstractSocket {
    private boolean cl;
    @Override
    public AbstractBufferedReader getInput() {
        return null;
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
        return false;
    }
}
