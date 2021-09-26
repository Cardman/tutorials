package code.music.core;

import code.util.CustList;

public final class MetaPart {

    private static final String SEP_TWO = "/";

    private static final String SEP_ONE = ":";

    private static final String STRING = "";

    private CustList<MetaPhrase> phrases = new CustList<MetaPhrase>();

    private int instrument;

    private int channel;

    private String name = STRING;

    private int numerator = Integer.MIN_VALUE;

    private int denominator = Integer.MIN_VALUE;

    public CustList<MetaPhrase> getPhrases() {
        return phrases;
    }
    public String display(boolean _db) {
        StringBuilder str_ = new StringBuilder();
        str_.append(name);
        str_.append(SEP_ONE);
        for (MetaPhrase e: phrases) {
            str_.append(e.display(_db));
            str_.append(SEP_ONE);
        }
        str_.append(SEP_ONE);
        str_.append(instrument);
        str_.append(SEP_ONE);
        str_.append(channel);
        str_.append(SEP_ONE);
        str_.append(numerator);
        str_.append(SEP_TWO);
        str_.append(denominator);
        return str_.toString();
    }

    public void setPhrases(CustList<MetaPhrase> _phrases) {
        this.phrases = _phrases;
    }

    public int getInstrument() {
        return instrument;
    }

    public int getChannel() {
        return channel;
    }

    public String getName() {
        return name;
    }

    public int getNumerator() {
        return numerator;
    }

    public int getDenominator() {
        return denominator;
    }

    public void setInstrument(int _instrument) {
        instrument = _instrument;
    }

    public void setChannel(int _channel) {
        channel = _channel;
    }

    public void setName(String _name) {
        name = _name;
    }

    public void setNumerator(int _numerator) {
        numerator = _numerator;
    }

    public void setDenominator(int _denominator) {
        denominator = _denominator;
    }

}
