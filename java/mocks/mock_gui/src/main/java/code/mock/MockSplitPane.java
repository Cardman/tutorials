package code.mock;

import code.gui.AbsCustComponent;
import code.gui.AbsSplitPane;

public class MockSplitPane extends MockCustComponent implements AbsSplitPane {
    private final boolean horizontal;
    private boolean continuousLayout;
    private boolean oneTouchExpandable;
    private int dividerLocation;
    private int dividerSize;

    public MockSplitPane(boolean _h,AbsCustComponent _left, AbsCustComponent _right) {
        this.horizontal = _h;
        procParents(_left, _right);
    }

    private void procParents(AbsCustComponent _left, AbsCustComponent _right) {
        _left.setParent(this);
        getChildren().add(_left);
        _right.setParent(this);
        getChildren().add(_right);
    }

    public boolean isHorizontal() {
        return horizontal;
    }

    @Override
    public void setLeftComponent(AbsCustComponent absCustComponent) {
        if (absCustComponent.getParent() == null) {
            innerLeft(absCustComponent);
        }
    }

    @Override
    public void innerLeft(AbsCustComponent absCustComponent) {
        getChildren().first().setParent(null);
        absCustComponent.setParent(this);
        getChildren().set(0, absCustComponent);
    }

    @Override
    public void setRightComponent(AbsCustComponent absCustComponent) {
        if (absCustComponent.getParent() == null) {
            innerRight(absCustComponent);
        }
    }

    @Override
    public void innerRight(AbsCustComponent absCustComponent) {
        getChildren().last().setParent(null);
        absCustComponent.setParent(this);
        getChildren().set(1, absCustComponent);
    }

    @Override
    public boolean isContinuousLayout() {
        return continuousLayout;
    }

    @Override
    public void setContinuousLayout(boolean b) {
        continuousLayout = b;
    }

    @Override
    public boolean isOneTouchExpandable() {
        return oneTouchExpandable;
    }

    @Override
    public void setOneTouchExpandable(boolean b) {
        oneTouchExpandable = b;
    }

    @Override
    public int getDividerLocation() {
        return dividerLocation;
    }

    @Override
    public void setDividerLocation(int i) {
        dividerLocation = i;
    }

    @Override
    public int getDividerSize() {
        return dividerSize;
    }

    @Override
    public void setDividerSize(int i) {
        dividerSize = i;
    }
}
