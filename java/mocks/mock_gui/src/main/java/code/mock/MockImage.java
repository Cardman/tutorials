package code.mock;

import code.gui.AbsCustComponent;
import code.gui.AbsMetaLabel;
import code.gui.AbsPreparedLabel;
import code.gui.images.AbstractImage;
import code.gui.images.MetaFont;
import code.images.BaseSixtyFourUtil;
import code.util.StringList;
import code.util.core.StringUtil;

public class MockImage implements AbstractImage {
    private final int[][] pixels;
    private final StringList strings = new StringList();
    private MetaFont metaFont = new MetaFont("",0,0);
    private final StringList trans = new StringList();
    private int color;
    private final int width;

    public MockImage(int[][] _p) {
        width = _p[0].length;
        this.pixels = _p;
        color = getRGB(0,0);
    }

    @Override
    public AbsPreparedLabel newAbsPreparedLabel() {
        return new MockPreparedLabel();
    }

    @Override
    public void translate(int i, int i1) {
        trans.add("");
    }

    @Override
    public byte[] toBytes() {
        return StringUtil.encode(BaseSixtyFourUtil.getStringByImage(pixels));
    }

    @Override
    public int getHeight() {
        return pixels.length;
    }

    @Override
    public int getWidth() {
        return width;
    }

    @Override
    public int getRGB(int _i, int _j) {
        return pixels[_i][_j];
    }

    @Override
    public void setRGB(int _i, int _j, int _c) {
        pixels[_i][_j] = _c;
    }

    @Override
    public void drawImage(AbstractImage _img, int i, int i1) {
        BaseSixtyFourUtil.clipSixtyFour(((MockImage)_img).pixels,i,i1,_img.getWidth(),_img.getHeight());
    }

    @Override
    public void setColorBg(AbsCustComponent absCustComponent) {
        setColor(absCustComponent.getBackgroundValue());
    }

    @Override
    public void setColorFg(AbsCustComponent absCustComponent) {
        setColor(absCustComponent.getForegroundValue());
    }

    @Override
    public void setColor(int _i) {
        color = _i;
    }

    @Override
    public void fillRect(int i, int i1, int i2, int i3) {
        trans.add("");
    }

    @Override
    public void drawString(String s, int i, int i1) {
        getStrings().add(s);
    }

    @Override
    public void drawRect(int i, int i1, int i2, int i3) {
        trans.add("");
    }

    @Override
    public void fillPolygon(int[] ints, int[] ints1, int i) {
        trans.add("");
    }

    @Override
    public void fillOval(int i, int i1, int i2, int i3) {
        trans.add("");
    }

    @Override
    public void drawLine(int i, int i1, int i2, int i3) {
        trans.add("");
    }

    @Override
    public int getColorValue() {
        return color;
    }

    @Override
    public MetaFont getMetaFont() {
        return metaFont;
    }

    @Override
    public void setFont(String _name, int _style, int _size) {
        metaFont = new MetaFont(_name,_style,_size);
    }

    @Override
    public void setFont(MetaFont metaFont) {
        setFont(metaFont.getFontFamily(), metaFont.getFont(), metaFont.getRealSize());
    }

    @Override
    public void setFont(AbsCustComponent absCustComponent) {
        setFont(absCustComponent.getMetaFont());
    }

    @Override
    public void setFont(AbsMetaLabel absMetaLabel) {
        setFont(absMetaLabel.getMetaFont());
    }

    @Override
    public void drawPolygon(int[] ints, int[] ints1, int i) {
        trans.add("");
    }

    @Override
    public void drawOval(int i, int i1, int i2, int i3) {
        trans.add("");
    }

    @Override
    public void dispose() {
        getStrings().clear();
    }

    @Override
    public byte[] writeImg(String s) {
        return StringUtil.encode(BaseSixtyFourUtil.getStringByImage(pixels));
    }

    public StringList getStrings() {
        return strings;
    }
}