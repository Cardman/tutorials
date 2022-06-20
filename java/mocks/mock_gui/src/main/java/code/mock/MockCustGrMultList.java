package code.mock;

import code.gui.*;
import code.util.CustList;
import code.util.Ints;

public class MockCustGrMultList extends MockInput implements Input, AbsGraphicList<String> {

    private final MockCustGrList<String> compo = new MockCustGrList<String>();

    @Override
    public void add(String s) {
        compo.add(s);
    }

    @Override
    public void add(int i, AbsPreparedLabel absPreparedLabel, String s) {
        compo.add(i,s);
    }

    @Override
    public void add(int i, String s) {
        compo.add(i,s);
    }

    @Override
    public void set(int i, String s) {
        compo.set(i,s);
    }

    @Override
    public int set(int i, AbsPreparedLabel absPreparedLabel, String s) {
        compo.set(i,s);
        return i;
    }

    @Override
    public void clear() {
        compo.clear();
    }

    @Override
    public void clearSelection() {
        compo.clearSelection();
    }

    @Override
    public void clearRevalidate() {
        compo.clearRevalidate();
    }

    @Override
    public int size() {
        return compo.size();
    }

    @Override
    public void remove(int i) {
        compo.remove(i);
    }

    @Override
    public void setListener(ListSelection listSelection) {
        compo.setListener(listSelection);
    }

    @Override
    public void clearAllRange() {
        compo.clearAllRange();
    }

    @Override
    public void setSelectedIndice(int i) {
        compo.setSelectedIndice(i);
    }

    @Override
    public void setVisibleRowCount(int i) {
        compo.setVisibleRowCount(i);
    }

    @Override
    public int getSelectedIndex() {
        return compo.getSelectedIndex();
    }

    @Override
    public boolean isSelectionEmpty() {
        return compo.isSelectionEmpty();
    }

    @Override
    public boolean isEmpty() {
        return compo.isEmpty();
    }

    @Override
    public CustList<String> getList() {
        return compo.getList();
    }

    @Override
    public int getSelectedValuesLsLen() {
        return compo.getSelectedValuesLsLen();
    }

    @Override
    public String get(int i) {
        return compo.get(i);
    }

    @Override
    public String last() {
        return compo.last();
    }

    @Override
    public AbsCustComponent self() {
        return compo.self();
    }

    @Override
    public AbsCustComponent scroll() {
        return compo.scroll();
    }

    @Override
    public AbsCustComponent visible() {
        return compo.visible();
    }

    @Override
    public AbsCustComponent getGlobal() {
        return compo.scroll();
    }

    @Override
    public Ints getSelectedIndexes() {
        return compo.getSelectedIndexes();
    }
}
