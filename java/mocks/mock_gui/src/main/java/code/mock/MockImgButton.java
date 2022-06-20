package code.mock;

import code.gui.AbsImgButton;
import code.gui.events.AbsActionListener;
import code.util.CustList;

public class MockImgButton extends MockInput implements AbsImgButton {
    private final CustList<AbsActionListener> absActionListeners = new CustList<AbsActionListener>();
    @Override
    public void addMouseList(AbsActionListener absActionListener) {
        absActionListeners.add(absActionListener);
    }

    public CustList<AbsActionListener> getAbsActionListeners() {
        return absActionListeners;
    }
}
