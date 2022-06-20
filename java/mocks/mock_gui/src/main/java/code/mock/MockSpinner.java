package code.mock;

import code.gui.AbsSpinner;
import code.gui.events.AbsChangeListener;
import code.util.CustList;

public class MockSpinner extends MockInput implements AbsSpinner {
    private int min;
    private int max;
    private final CustList<AbsChangeListener> changeListeners = new CustList<AbsChangeListener>();
    private int value;
    private int step;

    public MockSpinner(int _value,int _min, int _max, int _step) {
        min = _min;
        max = _max;
        step = _step;
        model(_value, _min, _max, _step);
    }

    private void model(int _value, int _min, int _max, int _step) {
        if (invalidSpinner(_value, _min, _max)) {
            defValues();
        } else {
            mod(_value, _min, _max, _step);
        }
    }

    public static boolean invalidSpinner(int _value, int _min, int _max) {
        if (_value < _min) {
            return true;
        } else {
            return _value > _max;
        }
    }
    @Override
    public void updateModel() {
        mod(getValue(), min, max, step);
    }
    @Override
    public void updateModel(int _value) {
        mod(_value, min, max, step);
    }

    public CustList<AbsChangeListener> getChangeListeners() {
        return changeListeners;
    }

    @Override
    public void addChangeListener(AbsChangeListener absChangeListener) {
        changeListeners.add(absChangeListener);
    }

    @Override
    public void setRange(int _min, int _max) {
        if (!invalidSpinner(getValue(), _min, _max)) {
            range(_min, _max);
        }
    }

    @Override
    public void range(int _min, int _max) {
        max = _max;
        min = _min;
    }

    @Override
    public void defValues() {
        min = Integer.MIN_VALUE;
        max = Integer.MAX_VALUE;
        step = 1;
    }

    @Override
    public void mod(int _value, int _min, int _max, int _step) {
        value = _value;
        max = _max;
        min = _min;
        step = _step;
    }

    @Override
    public void setRangeValue(int _value,int _min, int _max) {
        if (!invalidSpinner(_value, _min, _max)) {
            rangeValue(_value, _min, _max);
        }
    }

    @Override
    public void rangeValue(int _value, int _min, int _max) {
        max = _max;
        min = _min;
    }

    @Override
    public void min(int i) {
        if (i != min) {
            min = i;
            fireEvent();
        }
    }

    @Override
    public void max(int i) {
        if (i != max) {
            max = i;
            fireEvent();
        }
    }

    @Override
    public int getMin() {
        return min;
    }

    @Override
    public void setMin(int i) {
        if (!invalidSpinner(getValue(), i, getMax())) {
            min(i);
        }
    }

    @Override
    public int getMax() {
        return max;
    }

    @Override
    public void setMax(int i) {
        if (!invalidSpinner(getValue(), getMin(), i)) {
            max(i);
        }
    }

    @Override
    public int getStep() {
        return step;
    }

    @Override
    public void setStep(int i) {
        if (i != step) {
            step = i;
            fireEvent();
        }
    }

    @Override
    public int getValue() {
        return value;
    }

    @Override
    public void setValue(int i) {
        if (!invalidSpinner(i, getMin(), getMax()) && i != value) {
            value = i;
            fireEvent();
        }

    }

    private void fireEvent() {
        for (AbsChangeListener a: getChangeListeners()) {
            a.stateChanged();
        }
    }
}
