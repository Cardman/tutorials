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
        return null;
    }

    @Override
    public Input createMultStrList(AbstractImageFactory abstractImageFactory, StringList stringList, Ints ints, int i) {
        return null;
    }
}
