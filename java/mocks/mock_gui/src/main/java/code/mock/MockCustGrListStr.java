package code.mock;

import code.expressionlanguage.structs.Struct;
import code.gui.AbsGraphicListStr;
import code.gui.AbsPreparedLabel;
import code.gui.SpecSelectionCtx;
import code.gui.SpecSelectionStruct;

public class MockCustGrListStr extends MockCustGrList<Struct> implements AbsGraphicListStr {
    @Override
    public void setCustCell(Struct struct, AbsPreparedLabel absPreparedLabel, Struct struct1, SpecSelectionStruct specSelectionStruct) {
        isCust();
    }

    @Override
    public void setDefCell(Struct struct, SpecSelectionCtx specSelectionCtx) {
        isCust();
    }

    @Override
    public void updateGraphics() {
        isCust();
    }

    @Override
    public boolean isCust() {
        return true;
    }
}
