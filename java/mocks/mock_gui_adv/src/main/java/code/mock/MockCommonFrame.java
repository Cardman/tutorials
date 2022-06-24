package code.mock;

import code.gui.GuiBaseUtil;
import code.gui.initialize.AbstractProgramInfos;

public class MockCommonFrame extends MockAbsCommonFrame{
    public MockCommonFrame(AbstractProgramInfos frames) {
        super(frames);
    }

    public void pack() {
        GuiBaseUtil.recalculate(getPane());
    }

}
