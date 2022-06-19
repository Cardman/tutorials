package code.mock;

import code.gui.AbsGraphicListPainter;
import code.gui.AbsGraphicListStr;
import code.gui.SpecSelectionCtx;
import code.gui.initialize.AbstractAdvGraphicListGenerator;

public class MockAdvGraphicListGenerator implements AbstractAdvGraphicListGenerator {
    private final boolean cust;

    public MockAdvGraphicListGenerator(boolean cust) {
        this.cust = cust;
    }

    @Override
    public AbsGraphicListStr createSimple(AbsGraphicListPainter absGraphicListPainter, SpecSelectionCtx specSelectionCtx) {
        return new MockCustGrListStr(cust);
    }

    @Override
    public AbsGraphicListStr createMult(AbsGraphicListPainter absGraphicListPainter, SpecSelectionCtx specSelectionCtx) {
        return new MockCustGrListStr(cust);
    }

    @Override
    public boolean isCust() {
        return cust;
    }
}
