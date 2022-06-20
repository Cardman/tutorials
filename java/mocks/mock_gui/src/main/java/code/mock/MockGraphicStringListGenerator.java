package code.mock;

import code.gui.AbsGraphicList;
import code.gui.Input;
import code.gui.images.AbstractImageFactory;
import code.gui.initialize.AbsCompoFactory;
import code.gui.initialize.AbstractGraphicStringListGenerator;
import code.util.Ints;
import code.util.StringList;

public class MockGraphicStringListGenerator implements AbstractGraphicStringListGenerator {
    @Override
    public AbsGraphicList<String> createStrList(AbstractImageFactory abstractImageFactory, StringList stringList, AbsCompoFactory absCompoFactory) {
        MockCustGrList<String> stringMockCustGrList = new MockCustGrList<String>();
        for (String s: stringList) {
            stringMockCustGrList.add(s);
        }
        return stringMockCustGrList;
    }

    @Override
    public Input createMultStrList(AbstractImageFactory abstractImageFactory, StringList stringList, Ints ints, int i) {
        MockCustGrMultList mockCustGrMultList = new MockCustGrMultList();
        for (String s: stringList) {
            mockCustGrMultList.add(s);
        }
        return mockCustGrMultList;
    }
}
