package code.mock;

import code.gui.*;
import code.gui.images.AbstractImage;
import code.gui.initialize.AbsFrameFactory;
import code.gui.initialize.AbsLightFrameFactory;
import code.gui.initialize.AbstractProgramInfos;

public class MockFrameFactory implements AbsFrameFactory, AbsLightFrameFactory {
    private final AbstractProgramInfos programInfos;

    public MockFrameFactory(AbstractProgramInfos programInfos) {
        this.programInfos = programInfos;
    }

    @Override
    public AbsCommonFrame newCommonFrame(String s, AbstractProgramInfos abstractProgramInfos, AbstractImage abstractImage) {
        return new MockCommonFrame(abstractProgramInfos);
    }

    @Override
    public AbsDialog newDialog(AbsCloseableDialog absCloseableDialog) {
        return new MockDialog(absCloseableDialog,programInfos);
    }

    @Override
    public AbsDialog newDialog() {
        return new MockDialog(programInfos);
    }

    @Override
    public void setCursor(AbsCustComponent absCustComponent, int i, int i1, int[] ints) {
        absCustComponent.setHandCursor();
    }

    @Override
    public AbsOtherDialog newOtherDialog() {
        return new MockDialog(programInfos);
    }

    @Override
    public AbsOtherFrame newOtherFrame() {
        return new MockCommonFrame(programInfos);
    }
}
