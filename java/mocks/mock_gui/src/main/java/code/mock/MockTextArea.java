package code.mock;

import code.gui.AbsTextArea;
import code.gui.images.MetaPoint;

public class MockTextArea extends MockInput implements AbsTextArea {
    private final StringBuilder builder = new StringBuilder();
    private String selected = "";
    private int selectionStart;
    private int selectionEnd;
    private int tabSize;
    private int rows;
    private int cols;

    public MockTextArea() {
        this("");
    }
    public MockTextArea(int _r,int _c) {
        this("",_r,_c);
    }
    public MockTextArea(String _txt) {
        builder.append(_txt);
    }
    public MockTextArea(String _txt,int _r,int _c) {
        builder.append(_txt);
        rows = _r;
        cols = _c;
    }
    @Override
    public void insert(String s, int i) {
        builder.insert(i,s);
    }

    @Override
    public void forceInsert(String s, int i) {
        builder.insert(i,s);
    }

    @Override
    public void replaceRange(String s, int i, int i1) {
        builder.replace(i,i1,s);
    }

    @Override
    public void forceReplaceRange(String s, int i, int i1) {
        builder.replace(i,i1,s);
    }

    @Override
    public void replaceSelection(String s) {
        builder.replace(selectionStart,selectionEnd,s);
        selected = "";
    }

    @Override
    public void append(String s) {
        builder.append(s);
    }

    @Override
    public void setText(String s) {
        builder.delete(0,builder.length());
        builder.append(s);
    }

    @Override
    public String getText() {
        return builder.toString();
    }

    @Override
    public String getSelectedText() {
        return selected;
    }

    @Override
    public void setSelectionStart(int i) {
        select(i,selectionEnd);
    }

    @Override
    public void setSelectionEnd(int i) {
        select(selectionStart,i);
    }

    @Override
    public void setTabSize(int i) {
        tabSize = i;
    }

    @Override
    public int getTabSize() {
        return tabSize;
    }

    @Override
    public void select(int i, int i1) {
        selectionStart = i;
        selectionEnd = i1;
        if (i < 0 || i1 >= builder.length() || i1 < i) {
            selected = "";
            selectionStart = 0;
            selectionEnd = 0;
        } else {
            selected = builder.substring(i, i1);
        }
    }

    @Override
    public void selectAll() {
        selected = getText();
    }

    @Override
    public void setEditable(boolean b) {
        setEnabled(b);
    }

    @Override
    public int viewToModel(MetaPoint metaPoint) {
        return 0;
    }

    public int getCols() {
        return cols;
    }

    public int getRows() {
        return rows;
    }
}
