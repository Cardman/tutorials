package code.mock;

import code.gui.AbsCustComponent;
import code.gui.GraphicComboGrInt;
import code.gui.ListSelection;
import code.gui.SelectionInfo;
import code.util.CustList;
import code.util.IdList;
import code.util.Ints;
import code.util.StringList;

public class MockComboBox extends MockInput implements GraphicComboGrInt {

    private final IdList<ListSelection> listSelections = new IdList<ListSelection>();
    private int selectedIndex;
    private final StringList items = new StringList();
    private boolean popuped;
    public MockComboBox(StringList _list) {
        this(_list,0);
    }

    public MockComboBox(StringList _list, int _selectedIndex) {
        items.addAllElts(_list);
        selectItem(_selectedIndex);
    }

    @Override
    public AbsCustComponent getCurrentSelected() {
        return this;
    }

    @Override
    public void simpleSelectItem(int _index) {
        int index_ = Math.min(getItemCount()-1,_index);
        index_ = Math.max(index_,-1);
        selectedIndex = index_;
        fireEvent();
    }


    @Override
    public String getSelectedItem() {
        int selectedIndex_ = getSelectedIndex();
        if (!items.isValidIndex(selectedIndex_)) {
            return null;
        }
        return items.get(selectedIndex_);
    }

    @Override
    public void simpleRemoveAllItems() {
        clearFire();
    }

    @Override
    public void simpleRemoveItem(int i) {
        remFire(i);
    }

    private void remFire(int _i) {
        items.remove(_i);
        if (_i == selectedIndex) {
            if (selectedIndex == items.size()) {
                selectedIndex--;
            }
            fireEvent();
        }
    }

    @Override
    public AbsCustComponent self() {
        return this;
    }

    @Override
    public int getSelectedIndex() {
        return selectedIndex;
    }

    @Override
    public int getItemCount() {
        return items.size();
    }

    @Override
    public void removeItem(int i) {
        remFire(i);
    }

    @Override
    public void selectItem(int _index) {
        simpleSelectItem(_index);
    }

    @Override
    public void removeAllItems() {
        clearFire();
    }

    private void clearFire() {
        items.clear();
        fireEvent();
    }

    @Override
    public void addItem(String s) {
        items.add(s);
        if (items.size() == 1) {
            selectedIndex = 0;
            fireEvent();
        }
    }

    @Override
    public void setListener(ListSelection listSelection) {
        listSelections.clear();
        listSelections.add(listSelection);
    }

    @Override
    public CustList<ListSelection> getListeners() {
        return listSelections;
    }

    @Override
    public void addListener(ListSelection listSelection) {
        listSelections.add(listSelection);
    }

    @Override
    public void removeListener(ListSelection listSelection) {
        listSelections.removeObj(listSelection);
    }

    @Override
    public AbsCustComponent getGlobal() {
        return this;
    }

    @Override
    public Ints getSelectedIndexes() {
        return Ints.singleOrEmpty(getSelectedIndex());
    }

    private void fireEvent() {
        for (ListSelection l: getListeners()) {
            l.valueChanged(new SelectionInfo(selectedIndex, selectedIndex,true));
        }
    }
    @Override
    public void popup() {
        popuped = true;
    }

    public boolean isPopuped() {
        return popuped;
    }
}
