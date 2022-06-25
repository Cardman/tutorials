package code.mock;

import code.gui.GuiBaseUtil;
import code.gui.initialize.AbstractProgramInfos;

public class MockCommonFrame extends MockAbsCommonFrame{
    public MockCommonFrame(AbstractProgramInfos frames, String l_gKey) {
        super(frames, l_gKey);
    }

    public void pack() {
        GuiBaseUtil.recalculate(getPane());
    }

}
