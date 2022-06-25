package code.mock;

import code.gui.AbsCommonFrame;
import code.gui.AbsOtherFrame;
import code.gui.initialize.AbstractProgramInfos;

public abstract class MockAbsCommonFrame extends MockWindow implements AbsCommonFrame,AbsOtherFrame {

    protected MockAbsCommonFrame(AbstractProgramInfos frames, String _lgKey) {
        super(frames);
        setLanguageKey(_lgKey);
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
