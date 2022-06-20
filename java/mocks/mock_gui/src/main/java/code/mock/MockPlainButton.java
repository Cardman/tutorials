package code.mock;

import code.gui.AbsPlainButton;
import code.gui.events.AbsActionListener;
import code.gui.events.AbsAdvActionListener;
import code.util.IdList;

public class MockPlainButton extends MockInput implements AbsPlainButton {
    private final IdList<AbsActionListener> actionListeners = new IdList<AbsActionListener>();
    private final IdList<AbsAdvActionListener> advActionListeners = new IdList<AbsAdvActionListener>();
    private String text;
    public MockPlainButton() {
        this("");
    }
    public MockPlainButton(String s) {
        text=s;
    }
    @Override
    public void addActionListener(AbsActionListener absActionListener) {
        actionListeners.add(absActionListener);
    }

    @Override
    public void addActionListener(AbsAdvActionListener absAdvActionListener) {
        advActionListeners.add(absAdvActionListener);
    }

    public IdList<AbsActionListener> getActionListeners() {
        return actionListeners;
    }

    public IdList<AbsAdvActionListener> getAdvActionListeners() {
        return advActionListeners;
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
