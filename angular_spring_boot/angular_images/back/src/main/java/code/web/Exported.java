package code.web;

import code.util.NonIterableBytes;

public class Exported {
    private String img;
    private NonIterableBytes bytes;

    public String getImg() {
        return img;
    }

    public void setImg(String img) {
        this.img = img;
    }

    public NonIterableBytes getBytes() {
        return bytes;
    }

    public void setBytes(NonIterableBytes bytes) {
        this.bytes = bytes;
    }
}
