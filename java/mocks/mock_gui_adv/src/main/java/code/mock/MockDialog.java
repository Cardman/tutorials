package code.mock;

import code.gui.AbsCloseableDialog;
import code.gui.GuiBaseUtil;
import code.gui.initialize.AbstractProgramInfos;

public class MockDialog extends MockAbsDialog{
    public MockDialog(AbstractProgramInfos frames) {
        super(frames);
    }

    public MockDialog(AbsCloseableDialog _cl, AbstractProgramInfos frames) {
        super(_cl, frames);
    }

    public void pack() {
        GuiBaseUtil.recalculate(getPane());
    }

}
