package code.mock;

import code.gui.*;
import code.gui.images.AbstractImage;
import code.gui.initialize.AbsFrameFactory;
import code.gui.initialize.AbsLightFrameFactory;
import code.gui.initialize.AbstractProgramInfos;

public class MockFrameFactory implements AbsFrameFactory, AbsLightFrameFactory {
    @Override
    public AbsCommonFrame newCommonFrame(String s, AbstractProgramInfos abstractProgramInfos, AbstractImage abstractImage) {
        return null;
    }

    @Override
    public AbsDialog newDialog(AbsCloseableDialog absCloseableDialog) {
        return null;
    }

    @Override
    public AbsDialog newDialog() {
        return null;
    }

    @Override
    public void setCursor(AbsCustComponent absCustComponent, int i, int i1, int[] ints) {
        absCustComponent.setHandCursor();
    }

    @Override
    public AbsOtherDialog newOtherDialog() {
        return null;
    }

    @Override
    public AbsOtherFrame newOtherFrame() {
        return null;
    }
}
