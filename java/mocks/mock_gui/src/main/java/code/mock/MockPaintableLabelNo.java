package code.mock;

import code.gui.images.AbstractImageFactory;

public class MockPaintableLabelNo extends MockPaintableLabelAbs{
    @Override
    public void repaintLabel(AbstractImageFactory abstractImageFactory) {
        abstractImageFactory.newImageArgb(1,1);
    }
}
