package code.mock;

import code.gui.AbsClock;
import code.gui.AbsCustComponent;
import code.gui.AbsMetaLabelInt;
import code.gui.AbsPanel;
import code.gui.images.AbstractImageFactory;
import code.util.CustList;

public class MockPanel extends MockCustComponent implements AbsPanel {
    private final MockLayout layout;

    public MockPanel(MockLayout _l) {
        this.layout = _l;
    }

    public MockLayout getLayout() {
        return layout;
    }

    @Override
    public int getComponentCount() {
        return getChildren().size();
    }

    @Override
    public AbsCustComponent getComponent(int i) {
        return getChildren().get(i);
    }

    @Override
    public void add(AbsClock clock) {
        add(clock.getComponent());
    }

    @Override
    public void add(AbsMetaLabelInt absMetaLabel) {
        add(absMetaLabel.getPaintableLabel());
    }

    @Override
    public void add(AbsCustComponent absCustComponent) {
        if (absCustComponent.getParent() == null) {
            innerAdd(absCustComponent);
        }
    }

    @Override
    public void innerAdd(AbsCustComponent absCustComponent) {
        absCustComponent.setParent(this);
        innAdd(absCustComponent);
    }

    @Override
    public void add(AbsMetaLabelInt absMetaLabel, int i) {
        add(absMetaLabel.getPaintableLabel(),i);
    }

    @Override
    public void add(AbsCustComponent absCustComponent, int i) {
        if (absCustComponent.getParent() == null) {
            innerAdd(absCustComponent, i);
        }
    }

    @Override
    public void innerAdd(AbsCustComponent absCustComponent, int i) {
        absCustComponent.setParent(this);
        getChildren().add(i, absCustComponent);
    }

    @Override
    public void add(AbsMetaLabelInt absMetaLabel, String s) {
        add(absMetaLabel.getPaintableLabel(),s);
    }

    @Override
    public void add(AbsCustComponent absCustComponent, String s) {
        if (absCustComponent.getParent() == null) {
            innerAdd(absCustComponent, s);
        }
    }

    @Override
    public void innerAdd(AbsCustComponent absCustComponent, String s) {
        absCustComponent.setParent(this);
        getChildren().add(absCustComponent);
    }

    @Override
    public void remove(int i) {
        CustList<AbsCustComponent> ch_ = getChildren();
        ch_.get(i).setParent(null);
        ch_.remove(i);
    }

    @Override
    public int remove(AbsCustComponent absCustComponent) {
        CustList<AbsCustComponent> ch_ = getChildren();
        int len_ = ch_.size();
        for (int i = 0; i < len_; i++) {
            if (ch_.get(i) == absCustComponent) {
                absCustComponent.setParent(null);
                return i;
            }
        }
        return -1;
    }

    @Override
    public void innAdd(AbsCustComponent absCustComponent) {
        getChildren().add(absCustComponent);
    }

    @Override
    public void removeAll() {
        for (AbsCustComponent a: getChildren()) {
            a.setParent(null);
        }
        innerRemoveAll();
    }

    @Override
    public void innerRemoveAll() {
        getChildren().clear();
    }

    @Override
    public void repaintSecondChildren(AbstractImageFactory abstractImageFactory) {
        for (AbsCustComponent c: getChildren()) {
            if (c instanceof MockPaintableLabel) {
                ((MockPaintableLabel) c).repaintLabel(abstractImageFactory);
            }
            if (c instanceof MockPanel) {
                for (AbsCustComponent d: c.getChildren()) {
                    if (d instanceof MockPaintableLabel) {
                        ((MockPaintableLabel) d).repaintLabel(abstractImageFactory);
                    }
                }
            }
        }
    }

    @Override
    public void repaintChildren(AbstractImageFactory abstractImageFactory) {
        for (AbsCustComponent c: getChildren()) {
            if (c instanceof MockPaintableLabel) {
                ((MockPaintableLabel) c).repaintLabel(abstractImageFactory);
            }
        }
    }
}
