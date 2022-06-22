package code.mock;

import code.gui.AbsMenu;
import code.gui.AbsMenuItem;
import code.gui.events.AbsActionListener;
import code.gui.events.AbsAdvActionListener;
import code.util.CustList;

public class MockMenuItem extends MockInput implements AbsMenuItem {

    private AbsMenu parentMenu;
    private final CustList<AbsActionListener> actionListeners = new CustList<AbsActionListener>();
    private final CustList<AbsAdvActionListener> advActionListeners = new CustList<AbsAdvActionListener>();
    private String text;
    public MockMenuItem() {
        this("");
    }
    public MockMenuItem(String s) {
        text=s;
    }

    @Override
    public void setAccelerator(char c) {
        setEnabled(isEnabled());
    }

    @Override
    public void setAccelerator(String s) {
        setAccelerator(' ');
    }

    @Override
    public void setAccelerator(int i, int i1) {
        setAccelerator(' ');
    }

    @Override
    public void addActionListener(AbsActionListener absActionListener) {
        actionListeners.add(absActionListener);
    }

    public CustList<AbsActionListener> getActionListeners() {
        return actionListeners;
    }

    @Override
    public void addActionListener(AbsAdvActionListener absAdvActionListener) {
        advActionListeners.add(absAdvActionListener);
    }

    public CustList<AbsAdvActionListener> getAdvActionListeners() {
        return advActionListeners;
    }

    @Override
    public void setEnabledMenu(boolean _b) {
        setEnabled(_b);
    }

    @Override
    public String getText() {
        return text;
    }

    @Override
    public void setText(String s) {
        text = s;
    }

    @Override
    public AbsMenu getParentMenu() {
        return parentMenu;
    }

    @Override
    public void setParentMenu(AbsMenu absMenu) {
        parentMenu = absMenu;
    }
}
