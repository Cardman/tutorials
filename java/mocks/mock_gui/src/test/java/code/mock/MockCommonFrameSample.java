package code.mock;

import code.gui.initialize.AbstractProgramInfos;

public class MockCommonFrameSample extends MockAbsCommonFrame{
    public MockCommonFrameSample(AbstractProgramInfos frames) {
        super(frames, "");
    }

    @Override
    public void pack() {
        setVisible(isVisible());
    }
}
