package code.mock;

import code.gui.AbsCustComponent;
import code.gui.AbsTabbedPane;
import code.util.StringList;

public class MockTabbedPane extends MockCustComponent implements AbsTabbedPane {
    private int selectedIndex;
    private final StringList titles = new StringList();
    @Override
    public int getComponentCount() {
        return getChildren().size();
    }

    @Override
    public int getSelectedIndex() {
        return selectedIndex;
    }

    @Override
    public void setSelectedIndex(int i) {
        if (getChildren().isValidIndex(i)) {
            selectIndex(i);
        }
    }

    @Override
    public void selectIndex(int i) {
        selectedIndex = i;
    }

    @Override
    public void add(String s, AbsCustComponent absCustComponent) {
        if (absCustComponent.getParent() == null) {
            addIntTab(s, absCustComponent);
        }
    }

    @Override
    public void addIntTab(String s, AbsCustComponent absCustComponent) {
        absCustComponent.setParent(this);
        getChildren().add(absCustComponent);
        titles.add(s);
    }

    @Override
    public void setTab(int i, AbsCustComponent absCustComponent) {
        if (getChildren().isValidIndex(i) && absCustComponent.getParent() == null) {
            setTabComponentAt(i, absCustComponent);
        }
    }

    @Override
    public void setTabComponentAt(int i, AbsCustComponent absCustComponent) {
        getChildren().get(i).setParent(null);
        absCustComponent.setParent(this);
        getChildren().set(i, absCustComponent);
    }

    @Override
    public String getTitle(int i) {
        if (!titles.isValidIndex(i)) {
            return "";
        }
        return getTitleAt(i);
    }

    @Override
    public String getTitleAt(int i) {
        return titles.get(i);
    }

    @Override
    public void setTitle(int i, String s) {
        if (getChildren().isValidIndex(i)) {
            setTitleAt(i, s);
        }
    }

    @Override
    public void setTitleAt(int i, String s) {
        titles.set(i,s);
    }

    @Override
    public void remove(int i) {
        getChildren().get(i).setParent(null);
        getChildren().remove(i);
        titles.remove(i);
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
        titles.clear();
        getChildren().clear();
    }
}
