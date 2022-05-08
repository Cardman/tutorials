package code.web;

import java.util.List;

public class ExpFile {
    private String fileName;
    private List<Byte> bytes;

    public List<Byte> getBytes() {
        return bytes;
    }

    public void setBytes(List<Byte> bytes) {
        this.bytes = bytes;
    }

    public String getFileName() {
        return fileName;
    }

    public void setFileName(String fileName) {
        this.fileName = fileName;
    }
}
