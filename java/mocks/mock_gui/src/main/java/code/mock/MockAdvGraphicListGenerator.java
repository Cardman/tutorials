package code.mock;

import code.gui.AbsGraphicListPainter;
import code.gui.AbsGraphicListStr;
import code.gui.SpecSelectionCtx;
import code.gui.initialize.AbstractAdvGraphicListGenerator;

public class MockAdvGraphicListGenerator implements AbstractAdvGraphicListGenerator {
    @Override
    public AbsGraphicListStr createSimple(AbsGraphicListPainter absGraphicListPainter, SpecSelectionCtx specSelectionCtx) {
        return null;
    }

    @Override
    public AbsGraphicListStr createMult(AbsGraphicListPainter absGraphicListPainter, SpecSelectionCtx specSelectionCtx) {
        return null;
    }

    @Override
    public boolean isCust() {
        return false;
    }
}
