package code.mock;

import code.gui.AbsTextField;
import code.gui.events.AbsActionListener;
import code.gui.events.AbsAdvActionListener;
import code.gui.events.AbsAutoCompleteListener;
import code.util.CustList;

public class MockTextField extends MockInput implements AbsTextField {
    private String text;
    private int caretPosition;
    private final CustList<AbsAutoCompleteListener> autoCompleteListeners = new CustList<AbsAutoCompleteListener>();
    private final CustList<AbsActionListener> absActionListeners = new CustList<AbsActionListener>();
    private final CustList<AbsAdvActionListener> absAdvActionListeners = new CustList<AbsAdvActionListener>();
    public MockTextField() {
        this("");
    }
    public MockTextField(String _t) {
        text = _t;
    }
    @Override
    public void setText(String s) {
        text = s;
        for (AbsAutoCompleteListener a: autoCompleteListeners) {
            a.changedUpdate();
        }
    }

    @Override
    public String getText() {
        return text;
    }

    @Override
    public void addActionListener(AbsActionListener absActionListener) {
        absActionListeners.add(absActionListener);
    }

    @Override
    public void addActionListener(AbsAdvActionListener absAdvActionListener) {
        absAdvActionListeners.add(absAdvActionListener);
    }

    public CustList<AbsActionListener> getAbsActionListeners() {
        return absActionListeners;
    }

    public CustList<AbsAdvActionListener> getAbsAdvActionListeners() {
        return absAdvActionListeners;
    }

    @Override
    public void addAutoComplete(AbsAutoCompleteListener absAutoCompleteListener) {
        autoCompleteListeners.add(absAutoCompleteListener);
    }

    public CustList<AbsAutoCompleteListener> getAutoCompleteListeners() {
        return autoCompleteListeners;
    }

    public int getCaretPosition() {
        return caretPosition;
    }

    @Override
    public void setCaretPosition(int i) {
        caretPosition = i;
    }

    @Override
    public void setEditable(boolean b) {
        setEnabled(b);
    }
}
