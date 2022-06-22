package code.mock;

import code.gui.*;
import code.util.IdList;

public class MockMenu extends MockInput implements AbsMenu {

    private AbsMenu parentMenu;
    private final IdList<EnabledMenu> subs = new IdList<EnabledMenu>();
    private String text;

    public MockMenu() {
        this("");
    }

    public MockMenu(String _s) {
        text = _s;
    }

    @Override
    public int getSubCount() {
        return subs.size();
    }

    @Override
    public EnabledMenu getItem(int i) {
        return GuiBaseUtil.get(subs,i);
    }

    @Override
    public void addMenuItem(AbsMenuItem _menuItem) {
        _menuItem.setParentMenu(this);
        subs.add(_menuItem);
    }

    @Override
    public void addSeparator() {
        getItemCount();
    }

    @Override
    public void addMenuItem(AbsCheckBoxMenuItem _menuItem) {
        _menuItem.setParentMenu(this);
        subs.add(_menuItem);
    }

    @Override
    public void addMenuItem(AbsMenu _menuItem) {
        _menuItem.setParentMenu(this);
        subs.add(_menuItem);
    }

    @Override
    public void removeMenuItem(AbsMenu _menuItem) {
        _menuItem.setParentMenu(null);
        subs.removeObj(_menuItem);
    }

    @Override
    public void removeMenuItem(AbsMenuItem _menuItem) {
        _menuItem.setParentMenu(null);
        subs.removeObj(_menuItem);
    }

    @Override
    public void removeMenuItem(AbsCheckBoxMenuItem _menuItem) {
        _menuItem.setParentMenu(null);
        subs.removeObj(_menuItem);
    }

    @Override
    public int getItemCount() {
        return getSubCount();
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
