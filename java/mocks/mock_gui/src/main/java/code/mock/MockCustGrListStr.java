package code.mock;

import code.expressionlanguage.structs.Struct;
import code.gui.AbsGraphicListStr;
import code.gui.AbsPreparedLabel;
import code.gui.SpecSelectionCtx;
import code.gui.SpecSelectionStruct;

public class MockCustGrListStr extends MockCustGrList<Struct> implements AbsGraphicListStr {
    private boolean cust;

    public MockCustGrListStr(boolean _c) {
        this.cust = _c;
    }

    @Override
    public void setCustCell(Struct struct, AbsPreparedLabel absPreparedLabel, Struct struct1, SpecSelectionStruct specSelectionStruct) {
        cust = isCust();
    }

    @Override
    public void setDefCell(Struct struct, SpecSelectionCtx specSelectionCtx) {
        cust = isCust();
    }

    @Override
    public void updateGraphics() {
        cust = isCust();
    }

    @Override
    public boolean isCust() {
        return cust;
    }
}
