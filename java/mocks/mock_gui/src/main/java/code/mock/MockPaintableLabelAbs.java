package code.mock;

import code.gui.AbsPaintableLabel;
import code.gui.images.AbstractImage;
import code.gui.images.AbstractImageFactory;

public abstract class MockPaintableLabelAbs extends MockCustComponent implements AbsPaintableLabel {
    private boolean empty = true;
    private int verticalAlignment;
    private int horizontalAlignment;

    @Override
    public void requestFocusInWindow() {
        requestFocus();
    }

    @Override
    public void setEmptyIcon() {
        empty = true;
    }

    @Override
    public void setIcon(AbstractImageFactory abstractImageFactory, AbstractImage abstractImage) {
        empty = false;
    }

    @Override
    public void setVerticalAlignment(int i) {
        verticalAlignment = i;
    }

    @Override
    public void setHorizontalAlignment(int i) {
        horizontalAlignment = i;
    }

    public int getVerticalAlignment() {
        return verticalAlignment;
    }

    public int getHorizontalAlignment() {
        return horizontalAlignment;
    }

    public boolean isEmpty() {
        return empty;
    }
}
