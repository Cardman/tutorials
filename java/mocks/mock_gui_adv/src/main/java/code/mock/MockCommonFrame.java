package code.mock;

import code.gui.AbsCommonFrame;
import code.gui.AbsOtherFrame;
import code.gui.initialize.AbstractProgramInfos;

public class MockCommonFrame extends MockWindow implements AbsCommonFrame,AbsOtherFrame {

    public MockCommonFrame(AbstractProgramInfos frames) {
        super(frames);
    }

    @Override
    public void setFocusableWindowState(boolean b) {
        setFocusable(b);
    }

    @Override
    public void setFocusable(boolean b) {
        setVisible(isVisible());
    }


    @Override
    public void dispatchExit() {
        dispose();
    }

}
