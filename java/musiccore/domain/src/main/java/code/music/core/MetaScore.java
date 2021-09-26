package code.music.core;

import code.util.CustList;

public final class MetaScore {

    private static final String STRING = "";

    private CustList<MetaPart> parts = new CustList<MetaPart>();

    private String name = STRING;

    public CustList<MetaPart> getParts() {
        return parts;
    }
    public String display(boolean _db) {
        StringBuilder str_ = new StringBuilder(name);
        for (MetaPart e: parts) {
            str_.append(",");
            str_.append(e.display(_db));
        }
        return str_.toString();
    }

    public void setParts(CustList<MetaPart> _parts) {
        this.parts = _parts;
    }

    public String getName() {
        return name;
    }

    public void setName(String _name) {
        name = _name;
    }
}
