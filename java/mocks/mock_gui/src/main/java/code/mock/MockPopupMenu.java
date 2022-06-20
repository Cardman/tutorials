package code.mock;

import code.gui.*;
import code.util.IdList;

public class MockPopupMenu extends MockCustComponent implements AbsPopupMenu {

    private final IdList<AbsCustComponent> items = new IdList<AbsCustComponent>();
    private final IdList<EnabledMenu> itemsMenu = new IdList<EnabledMenu>();
    @Override
    public void show(AbsCustComponent absCustComponent, int i, int i1) {
        setVisible(true);
    }

    @Override
    public void show(int i, int i1) {
        setVisible(true);
    }

    @Override
    public void add(AbsCustComponent absCustComponent) {
        items.add(absCustComponent);
    }

    @Override
    public void add(AbsMenu absMenu) {
        itemsMenu.add(absMenu);
    }

    @Override
    public void add(AbsMenuItem absMenuItem) {
        itemsMenu.add(absMenuItem);
    }

    @Override
    public void add(AbsCheckBoxMenuItem absCheckBoxMenuItem) {
        itemsMenu.add(absCheckBoxMenuItem);
    }

    @Override
    public void remove(AbsCustComponent absCustComponent) {
        items.removeObj(absCustComponent);
    }

    @Override
    public void remove(AbsMenu absMenu) {
        itemsMenu.removeObj(absMenu);
    }

    @Override
    public void remove(AbsMenuItem absMenuItem) {
        itemsMenu.removeObj(absMenuItem);
    }

    @Override
    public void remove(AbsCheckBoxMenuItem absCheckBoxMenuItem) {
        itemsMenu.removeObj(absCheckBoxMenuItem);
    }
}
