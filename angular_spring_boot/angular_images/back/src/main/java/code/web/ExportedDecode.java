package code.web;

import code.util.NonIterableBytes;

public class ExportedDecode {
    private Exported exported;
    private NonIterableBytes decode;

    public Exported getExported() {
        return exported;
    }

    public void setExported(Exported exported) {
        this.exported = exported;
    }

    public NonIterableBytes getDecode() {
        return decode;
    }

    public void setDecode(NonIterableBytes decode) {
        this.decode = decode;
    }
}
