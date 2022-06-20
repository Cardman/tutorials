package code.mock;

import code.gui.AbsSlider;
import code.gui.events.AbsChangeListener;
import code.util.CustList;

public class MockSlider extends MockInput implements AbsSlider {
    private int orientation;
    private int value;
    private final CustList<AbsChangeListener> changeListeners = new CustList<AbsChangeListener>();
    private int minimum;
    private int maximum;
    public MockSlider() {
        this(0,100);
    }
    public MockSlider(int _o) {
        this(0,100);
        setOrientation(_o);
    }
    public MockSlider(int _min,int _max) {
        this(_min,_max,(_min+_max)/2);
    }
    public MockSlider(int _min,int _max,int _v) {
        minimum = _min;
        maximum = _max;
        value = _v;
    }
    public MockSlider(int _o,int _min,int _max,int _v) {
        minimum = _min;
        maximum = _max;
        value = _v;
        setOrientation(_o);
    }

    @Override
    public int getOrientation() {
        return orientation;
    }

    @Override
    public void setOrientation(int orientation) {
        if (orientation == 0) {
            setHorizontal();
        } else {
            setVertical();
        }
    }

    @Override
    public void setHorizontal() {
        orientation = 0;
    }

    @Override
    public void setVertical() {
        orientation = 1;
    }

    public int getMaximum() {
        return maximum;
    }

    public void setMaximum(int maximum) {
        this.maximum = maximum;
        fireEvent();
    }

    @Override
    public void addChangeListener(AbsChangeListener absChangeListener) {
        changeListeners.add(absChangeListener);
    }

    public int getMinimum() {
        return minimum;
    }

    public void setMinimum(int minimum) {
        this.minimum = minimum;
        fireEvent();
    }

    public CustList<AbsChangeListener> getChangeListeners() {
        return changeListeners;
    }

    public int getValue() {
        return value;
    }

    public void setValue(int value) {
        this.value = value;
        fireEvent();
    }

    private void fireEvent() {
        for (AbsChangeListener a: getChangeListeners()) {
            a.stateChanged();
        }
    }
}
