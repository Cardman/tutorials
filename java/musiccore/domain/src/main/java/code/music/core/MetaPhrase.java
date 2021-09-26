package code.music.core;

import code.util.CustList;

public final class MetaPhrase {

    private static final String SEP_TWO = "/";

    private static final String SEP_ONE = ":";

    private CustList<MetaNote> notes = new CustList<MetaNote>();

    private int numerator = 4;

    private int denominator = 4;

    public CustList<MetaNote> getNotes() {
        return notes;
    }
    public String display(boolean _db) {
        StringBuilder str_ = new StringBuilder();
        for (MetaNote e: notes) {
            str_.append(e.display(_db));
            str_.append(SEP_ONE);
        }
        str_.append(SEP_ONE);
        str_.append(numerator);
        str_.append(SEP_TWO);
        str_.append(denominator);
        return str_.toString();
    }

    public int getNumerator() {
        return numerator;
    }

    public int getDenominator() {
        return denominator;
    }

    public void setNumerator(int _numerator) {
        numerator = _numerator;
    }

    public void setDenominator(int _denominator) {
        denominator = _denominator;
    }

    public void setNotes(CustList<MetaNote> _notes) {
        notes = _notes;
    }
}
