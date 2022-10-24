package sample;

import javax.swing.*;

public final class Real implements AbsCompo {
    private final JLabel label;

    public Real(JLabel l) {
        this.label = l;
    }

    @Override
    public String getValue() {
        return label.getText();
    }

    @Override
    public void setValue(String _v) {
        label.setText(_v);
    }

    public JLabel getLabel() {
        return label;
    }
}
