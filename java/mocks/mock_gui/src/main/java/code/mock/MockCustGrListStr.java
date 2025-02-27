package code.mock;

import code.expressionlanguage.structs.NullStruct;
import code.expressionlanguage.structs.Struct;
import code.gui.AbsGraphicListStr;
import code.gui.AbsPreparedLabel;
import code.gui.SpecSelectionCtx;
import code.gui.SpecSelectionStruct;

public class MockCustGrListStr extends MockCustGrList<Struct> implements AbsGraphicListStr {
    private final boolean cust;

    public MockCustGrListStr(boolean _c) {
        this.cust = _c;
    }

    @Override
    public void setCustCell(Struct struct, AbsPreparedLabel absPreparedLabel, Struct struct1, SpecSelectionStruct specSelectionStruct) {
        code();
    }

    @Override
    public void setDefCell(Struct struct, SpecSelectionCtx specSelectionCtx) {
        code();
    }

    @Override
    public void updateGraphics() {
        code();
    }

    private void code() {
        NullStruct.NULL_VALUE.sameReference(NullStruct.NULL_VALUE);
    }

    @Override
    public boolean isCust() {
        return cust;
    }
}
