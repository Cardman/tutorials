package code.mock;

import code.gui.AbsCustCheckBox;
import code.gui.events.AbsActionListener;
import code.util.CustList;
import code.util.IdList;

public class MockCustCheckBox extends MockInput implements AbsCustCheckBox {
    private final IdList<AbsActionListener> actionListeners = new IdList<AbsActionListener>();
    private boolean selected;
    private String text;
    public MockCustCheckBox() {
        this("");
    }
    public MockCustCheckBox(String s) {
        this(s,false);
    }
    public MockCustCheckBox(String s, boolean b) {
        text=s;
        selected = b;
    }
    @Override
    public void addActionListener(AbsActionListener absActionListener) {
        actionListeners.add(absActionListener);
    }

    @Override
    public void removeActionListener(AbsActionListener absActionListener) {
        actionListeners.removeObj(absActionListener);
    }

    @Override
    public CustList<AbsActionListener> getActionListeners() {
        return actionListeners;
    }

    @Override
    public void setSelected(boolean b) {
        selected = b;
    }

    @Override
    public boolean isSelected() {
        return selected;
    }

    @Override
    public void setText(String s) {
        text = s;
    }

    @Override
    public String getText() {
        return text;
    }
}
