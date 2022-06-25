package code.mock;

import code.gui.*;
import code.gui.images.AbstractImage;
import code.gui.initialize.AbstractProgramInfos;

public class MockFrameFactory extends MockAbsFrameFactory {

    public MockFrameFactory(AbstractProgramInfos programInfos) {
        super(programInfos);
    }

    @Override
    public AbsCommonFrame newCommonFrame(String s, AbstractProgramInfos abstractProgramInfos, AbstractImage abstractImage) {
        return new MockCommonFrame(abstractProgramInfos, s);
    }

    @Override
    public AbsDialog newDialog(AbsCloseableDialog absCloseableDialog) {
        return new MockDialog(absCloseableDialog, getProgramInfos());
    }

    @Override
    public AbsDialog newDialog() {
        return new MockDialog(getProgramInfos());
    }

    @Override
    public AbsOtherDialog newOtherDialog() {
        return new MockDialog(getProgramInfos());
    }

    @Override
    public AbsOtherFrame newOtherFrame() {
        return new MockCommonFrame(getProgramInfos(), "");
    }
}
