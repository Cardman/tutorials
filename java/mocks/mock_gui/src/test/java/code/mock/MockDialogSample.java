package code.mock;

import code.gui.AbsCloseableDialog;
import code.gui.initialize.AbstractProgramInfos;

public class MockDialogSample extends MockAbsDialog{
    public MockDialogSample(AbstractProgramInfos frames) {
        super(frames);
    }

    public MockDialogSample(AbsCloseableDialog _cl, AbstractProgramInfos frames) {
        super(_cl, frames);
    }

    @Override
    public void pack() {
        setVisible(isVisible());
    }
}
