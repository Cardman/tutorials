package code.mock;

public class MockWithActionSample implements MockWithAction{
    private int nb;
    @Override
    public void action(int _nb) {
        nb = _nb;
    }

    public int getNb() {
        return nb;
    }
}
