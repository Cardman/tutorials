package code.mock;

import code.gui.AbsTableGui;
import code.gui.events.AbsListSelectionListener;
import code.gui.events.AbsMouseListener;
import code.gui.events.AbsMouseListenerCl;
import code.util.CustList;
import code.util.Ints;
import code.util.StringList;

public class MockTableGui extends MockCustComponent implements AbsTableGui {
    private final CustList<AbsMouseListener> headers = new CustList<AbsMouseListener>();
    private final CustList<AbsMouseListenerCl> headersCl = new CustList<AbsMouseListenerCl>();
    private final CustList<AbsListSelectionListener> selection = new CustList<AbsListSelectionListener>();
    private boolean multiSelect = true;
    private boolean reorderingAllowed;
    private final StringList columnNames = new StringList();
    private final CustList<StringList> rows = new CustList<StringList>();
    private final Ints selected = new Ints();

    public MockTableGui(String... _cols) {
        setColumnIdentifiers(_cols);
    }
    @Override
    public int[] getSelectedRows() {
        int nb_ = selected.size();
        int[] s_ = new int[nb_];
        for (int i = 0; i < nb_; i++) {
            s_[i] = selected.get(i);
        }
        return s_;
    }

    @Override
    public int getSelectedRow() {
        if (selected.size() != 1) {
            return -1;
        }
        return selected.first();
    }

    @Override
    public int getSelectedRowCount() {
        return selected.size();
    }

    @Override
    public int getRowCount() {
        return rows.size();
    }

    @Override
    public int getColumnCount() {
        return columnNames.size();
    }

    @Override
    public void addSelectInterval(int i, int i1) {
        int m_ = Math.max(0, Math.min(i,i1));
        int p_ = Math.min(rows.size()-1, Math.max(i,i1));
        for (int j = m_;j <= p_;j++) {
            selected.add(j);
        }
        selected.sort();
    }

    @Override
    public void removeSelectInterval(int i, int i1) {
        int m_ = Math.max(0, Math.min(i,i1));
        int p_ = Math.min(rows.size()-1, Math.max(i,i1));
        for (int j = m_;j <= p_;j++) {
            selected.removeAllLong(j);
        }
    }

    @Override
    public void setRowCount(int i) {
        int rc_ = rows.size();
        if (i > rc_) {
            int nbCols_ = columnNames.size();
            for (int j = rc_; j < i; j++) {
                StringList row_ = new StringList();
                for (int k = 0; k < nbCols_; k++) {
                    row_.add("");
                }
                rows.add(row_);
            }
        } else {
            int j_ = rc_ -1;
            while (j_ >= Math.max(i,0)) {
                rows.remove(j_);
                j_--;
            }
        }
    }

    @Override
    public String getColumnName(int i) {
        return columnNames.get(i);
    }

    @Override
    public String getValueAt(int i, int i1) {
        return rows.get(i).get(i1);
    }

    @Override
    public void setValueAt(String s, int i, int i1) {
        rows.get(i).set(i1,s);
    }

    @Override
    public void moveColumn(int i, int i1) {
        if (i == i1) {
            return;
        }
        String old_ = columnNames.get(i);
        int rc_ = rows.size();
        if (i < i1) {
            for (int k = i; k < i1; k++) {
                columnNames.set(k,columnNames.get(k+1));
            }
            for (int r = 0; r < rc_; r++) {
                String oldc_ = rows.get(r).get(i);
                for (int k = i; k < i1; k++) {
                    rows.get(r).set(k,rows.get(r).get(k+1));
                }
                rows.get(r).set(i1,oldc_);
            }
            columnNames.set(i1,old_);
            return;
        }
        for (int k = i; k > i1; k--) {
            columnNames.set(k,columnNames.get(k-1));
        }
        for (int r = 0; r < rc_; r++) {
            String oldc_ = rows.get(r).get(i);
            for (int k = i; k > i1; k--) {
                rows.get(r).set(k,rows.get(r).get(k-1));
            }
            rows.get(r).set(i1,oldc_);
        }
        columnNames.set(i1,old_);
    }

    @Override
    public int columnAtPoint(int i, int i1) {
        return i;
    }

    @Override
    public int rowAtPoint(int i, int i1) {
        return i1;
    }

    @Override
    public boolean isMultiSelect() {
        return multiSelect;
    }

    @Override
    public void setMultiSelect(boolean b) {
        if (b) {
            setMultiSelect();
        } else {
            setSingleSelect();
        }
    }

    @Override
    public void setMultiSelect() {
        multiSelect = true;
    }

    @Override
    public void setSingleSelect() {
        multiSelect = false;
    }

    @Override
    public boolean isReorderingAllowed() {
        return reorderingAllowed;
    }

    @Override
    public void setReorderingAllowed(boolean b) {
        reorderingAllowed = b;
    }

    @Override
    public void applyChanges() {
        getSelectedRowCount();
    }

    @Override
    public void addHeaderListener(AbsMouseListener absMouseListener) {
        headers.add(absMouseListener);
    }

    public CustList<AbsMouseListener> getHeaders() {
        return headers;
    }

    @Override
    public void addHeaderListener(AbsMouseListenerCl absMouseListenerCl) {
        headersCl.add(absMouseListenerCl);
    }

    public CustList<AbsMouseListenerCl> getHeadersCl() {
        return headersCl;
    }

    @Override
    public void addListSelectionListener(AbsListSelectionListener absListSelectionListener) {
        selection.add(absListSelectionListener);
    }

    public CustList<AbsListSelectionListener> getSelection() {
        return selection;
    }

    @Override
    public void setColumnIdentifiers(String[] strings) {
        columnNames.clear();
        for (String c: strings) {
            columnNames.add(c);
        }
    }
}
