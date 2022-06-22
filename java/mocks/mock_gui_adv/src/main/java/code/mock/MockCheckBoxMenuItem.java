package code.mock;

import code.gui.AbsCheckBoxMenuItem;
import code.gui.AbsMenu;
import code.gui.events.AbsActionListener;
import code.gui.events.AbsAdvActionListener;
import code.util.CustList;

public class MockCheckBoxMenuItem extends MockInput implements AbsCheckBoxMenuItem {

    private AbsMenu parentMenu;
    private final CustList<AbsActionListener> actionListeners = new CustList<AbsActionListener>();
    private final CustList<AbsAdvActionListener> advActionListeners = new CustList<AbsAdvActionListener>();
    private String text;
    private boolean selected;
    public MockCheckBoxMenuItem() {
        this("");
    }
    public MockCheckBoxMenuItem(String s) {
        this(s,false);
    }
    public MockCheckBoxMenuItem(String s, boolean b) {
        text=s;
        selected = b;
    }
    @Override
    public boolean isSelected() {
        return selected;
    }

    @Override
    public void setSelected(boolean b) {
        selected = b;
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
