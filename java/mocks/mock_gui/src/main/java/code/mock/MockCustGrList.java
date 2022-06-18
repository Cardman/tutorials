package code.mock;

import code.gui.*;
import code.util.CustList;
import code.util.IdList;
import code.util.Ints;

public class MockCustGrList<T> extends MockInput implements AbsGraphicList<T>, AbsGraphicListDef {
    private final CustList<T> elts = new CustList<T>();
    private final IdList<ListSelection> listSelections = new IdList<ListSelection>();
    private int visibleRowCount = 8;
    private Ints selectedIndexes = new Ints();
    @Override
    public void add(T t) {
        elts.add(elts.size(),t);
    }

    @Override
    public void add(int i, AbsPreparedLabel absPreparedLabel, T t) {
        elts.add(i,t);
    }

    @Override
    public void add(int i, T t) {
        elts.add(i,t);
    }

    @Override
    public void set(int i, T t) {
        elts.set(i,t);
    }

    @Override
    public int set(int i, AbsPreparedLabel absPreparedLabel, T t) {
        elts.set(i,t);
        return i;
    }

    @Override
    public void clear() {
        elts.clear();
    }

    @Override
    public void clearSelection() {
        clearAllRange();
    }

    @Override
    public void clearRevalidate() {
        clear();
        fireEvent();
    }

    @Override
    public int size() {
        return elts.size();
    }

    @Override
    public void remove(int i) {
        elts.remove(i);
    }

    @Override
    public int getVisibleRowCount() {
        return visibleRowCount;
    }

    @Override
    public void setListener(ListSelection listSelection) {
        listSelections.clear();
        listSelections.add(listSelection);
    }

    @Override
    public void clearAllRange() {
        selectedIndexes.clear();
        fireEvent();
    }

    @Override
    public void setSelectedIndice(int i) {
        selectedIndexes.clear();
        if (elts.isValidIndex(i)) {
            selectedIndexes.add(i);
        }
        fireEvent();
    }

    @Override
    public void setVisibleRowCount(int i) {
        visibleRowCount = i;
    }

    @Override
    public int getSelectedIndex() {
        return (int) selectedIndexes.getMinimum(-1);
    }

    @Override
    public boolean isSelectionEmpty() {
        return selectedIndexes.isEmpty();
    }

    @Override
    public boolean isEmpty() {
        return elts.isEmpty();
    }

    @Override
    public CustList<T> getList() {
        return elts;
    }

    @Override
    public int getSelectedValuesLsLen() {
        return getSelectedIndexes().size();
    }

    @Override
    public T get(int i) {
        return elts.get(i);
    }

    @Override
    public T last() {
        return elts.last();
    }

    @Override
    public AbsCustComponent self() {
        return this;
    }

    @Override
    public AbsCustComponent scroll() {
        return this;
    }

    @Override
    public AbsCustComponent visible() {
        return this;
    }

    @Override
    public Ints getSelectedIndexes() {
        return selectedIndexes;
    }

    @Override
    public void setSelectedIndexes(Ints _ints) {
        Ints selected_ = new Ints();
        for (int i: _ints) {
            if (elts.isValidIndex(i)) {
                selected_.add(i);
            }
        }
        selectedIndexes = selected_;
        fireEvent();
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

    private void fireEvent() {
        for (ListSelection l: getListeners()) {
            l.valueChanged(new SelectionInfo((int)selectedIndexes.getMinimum(-1), (int)selectedIndexes.getMaximum(-1),true));
        }
    }
}
