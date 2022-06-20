package code.mock;

import code.gui.AbsCustButtonGroup;
import code.gui.AbsRadioButton;
import code.gui.events.AbsActionListener;
import code.gui.events.AbsChangeListener;
import code.util.CustList;
import code.util.IdList;

public class MockRadioButton extends MockInput implements AbsRadioButton {
    private final IdList<AbsActionListener> actionListeners = new IdList<AbsActionListener>();
    private final IdList<AbsChangeListener> changeListeners = new IdList<AbsChangeListener>();
    private boolean selected;
    private String text;
    private AbsCustButtonGroup buttonGroup;
    public MockRadioButton() {
        this("");
    }
    public MockRadioButton(String s) {
        this(s,false);
    }
    public MockRadioButton(String s, boolean b) {
        text=s;
        selected = b;
    }
    @Override
    public void addActionListener(AbsActionListener absActionListener) {
        actionListeners.add(absActionListener);
    }

    @Override
    public void addChangeListener(AbsChangeListener absChangeListener) {
        changeListeners.add(absChangeListener);
    }

    public IdList<AbsChangeListener> getChangeListeners() {
        return changeListeners;
    }

    public CustList<AbsActionListener> getActionListeners() {
        return actionListeners;
    }

    @Override
    public void setSelected(boolean b) {
        selected = b;
        for (AbsChangeListener a: getChangeListeners()) {
            a.stateChanged();
        }
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

    @Override
    public AbsCustButtonGroup getButtonGroup() {
        return buttonGroup;
    }

    @Override
    public void setButtonGroup(AbsCustButtonGroup _b) {
        this.buttonGroup = _b;
    }
}
