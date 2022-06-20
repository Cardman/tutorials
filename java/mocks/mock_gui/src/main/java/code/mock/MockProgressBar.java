package code.mock;

import code.gui.AbsProgressBar;

public class MockProgressBar extends MockCustComponent implements AbsProgressBar {
    private boolean horizontal;
    private int value;
    private int minimum;
    private int maximum;

    public boolean isHorizontal() {
        return horizontal;
    }

    public void setHorizontal(boolean horizontal) {
        if (horizontal) {
            setHorizontal();
        } else {
            setVertical();
        }
    }

    @Override
    public void setHorizontal() {
        horizontal = true;
    }

    @Override
    public void setVertical() {
        horizontal = false;
    }

    public int getMaximum() {
        return maximum;
    }

    public void setMaximum(int maximum) {
        this.maximum = maximum;
    }

    public int getMinimum() {
        return minimum;
    }

    public void setMinimum(int minimum) {
        this.minimum = minimum;
    }

    public int getValue() {
        return value;
    }

    public void setValue(int value) {
        this.value = value;
    }
}
