package code.web;

import code.util.NonIterableBytes;

public class ExpFile {
    private String fileName;
    private NonIterableBytes bytes;

    public NonIterableBytes getBytes() {
        return bytes;
    }

    public void setBytes(NonIterableBytes bytes) {
        this.bytes = bytes;
    }

    public String getFileName() {
        return fileName;
    }

    public void setFileName(String fileName) {
        this.fileName = fileName;
    }
}
