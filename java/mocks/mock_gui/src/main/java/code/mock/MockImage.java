package code.mock;

import code.gui.AbsCustComponent;
import code.gui.AbsMetaLabelInt;
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
        return pixels[_j][_i];
    }

    @Override
    public void setRGB(int _i, int _j, int _c) {
        pixels[_j][_i] = _c;
    }

    @Override
    public void drawImage(AbstractImage _img, int _x, int _y) {
        int l_ = Math.max(0,-_x);
        int t_ = Math.max(0,-_y);
        int r_ = Math.max(l_,Math.min(getWidth(),_img.getWidth())-Math.max(0,_x));
        int b_ = Math.max(t_,Math.min(getHeight(),_img.getHeight())-Math.max(0,_y));
        for(int i = l_; i < r_; i++) {
            for (int j = t_; j < b_; j++) {
                setRGB(i+_x,j+_y,_img.getRGB(i,j));
            }
        }
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
        setFont(new MetaFont(_name,_style,_size));
    }

    @Override
    public void setFont(MetaFont metaFont) {
        setMetaFont(metaFont);
    }

    @Override
    public void setFont(AbsCustComponent absCustComponent) {
        setFont(absCustComponent.getMetaFont());
    }

    @Override
    public void setFont(AbsMetaLabelInt _font) {
        setFont(_font.getPaintableLabel().getMetaFont());
    }

    public void setMetaFont(MetaFont metaFont) {
        this.metaFont = metaFont;
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
