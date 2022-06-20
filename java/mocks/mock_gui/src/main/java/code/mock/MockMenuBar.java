package code.mock;

import code.gui.AbsMenu;
import code.gui.AbsMenuBar;
import code.util.IdList;

public class MockMenuBar extends MockCustComponent implements AbsMenuBar {
    private final IdList<AbsMenu> menus = new IdList<AbsMenu>();
    @Override
    public int getMenuCount() {
        return menus.size();
    }

    @Override
    public void add(AbsMenu absMenu) {
        menus.add(absMenu);
    }

    @Override
    public void remove(AbsMenu absMenu) {
        menus.removeObj(absMenu);
    }
}
