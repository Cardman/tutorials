package code.mock;

import code.gui.AbsCustComponent;
import code.gui.events.*;
import code.gui.images.MetaDimension;
import code.gui.images.MetaFont;
import code.util.CustList;
import code.util.IdList;

public class MockCustComponent implements AbsCustComponent {
    private String toolTipText = "";
    private MockPosition vertical = MockPosition.CENTER;
    private MockPosition horizontal = MockPosition.CENTER;
    private AbsCustComponent parent;
    private MetaFont metaFont;
    private boolean autoscrolls;
    private boolean visible;
    private boolean accessible = true;
    private boolean focusable = true;
    private int width;
    private int height;
    private boolean prefSizeSet;
    private MetaDimension prefSize;
    private final CustList<AbsCustComponent> children = new CustList<AbsCustComponent>();
    private final IdList<AbsMouseListener> mouseListeners = new IdList<AbsMouseListener>();
    @Override
    public boolean isAutoscrolls() {
        return autoscrolls;
    }

    @Override
    public void setAutoscrolls(boolean b) {
        autoscrolls = b;
    }

    @Override
    public void addMouseListener(AbsMouseListener absMouseListener) {
        mouseListeners.add(absMouseListener);
    }

    @Override
    public void addMouseListener(AbsMouseListenerPresRel absMouseListenerPresRel) {
    }

    @Override
    public void addMouseListener(AbsMouseListenerIntRel absMouseListenerIntRel) {

    }

    @Override
    public void addMouseListener(AbsMouseListenerEnt absMouseListenerEnt) {

    }

    @Override
    public void addMouseListener(AbsMouseListenerCl absMouseListenerCl) {

    }

    @Override
    public void addMouseListener(AbsMouseListenerWithoutClick absMouseListenerWithoutClick) {

    }

    @Override
    public void addMouseListener(AbsMouseListenerWithoutClickPr absMouseListenerWithoutClickPr) {

    }

    @Override
    public void addMouseListener(AbsMouseListenerEer absMouseListenerEer) {

    }

    @Override
    public void addMouseMotionListener(AbsMouseMotionListener absMouseMotionListener) {

    }

    @Override
    public void addMouseWheelListener(AbsMouseWheelListener absMouseWheelListener) {

    }

    @Override
    public void addKeyListener(AbsKeyListener absKeyListener) {

    }

    @Override
    public void addKeyListener(AbsKeyListenerPress absKeyListenerPress) {

    }

    @Override
    public void addKeyListener(AbsKeyListenerReleased absKeyListenerReleased) {

    }

    @Override
    public void removeMouseListener(AbsMouseListener absMouseListener) {
        mouseListeners.removeObj(absMouseListener);
    }

    @Override
    public void removeMouseMotionListener(AbsMouseMotionListener absMouseMotionListener) {

    }

    @Override
    public void removeMouseWheelListener(AbsMouseWheelListener absMouseWheelListener) {

    }

    @Override
    public void removeKeyListener(AbsKeyListener absKeyListener) {

    }

    @Override
    public CustList<AbsMouseListener> getMouseListeners() {
        return mouseListeners;
    }

    @Override
    public CustList<AbsMouseMotionListener> getMouseMotionListeners() {
        return null;
    }

    @Override
    public CustList<AbsMouseWheelListener> getMouseWheelListeners() {
        return null;
    }

    @Override
    public CustList<AbsKeyListener> getKeyListeners() {
        return null;
    }

    @Override
    public void requestFocus() {
        if (isFocusable()) {
            accessible = true;
        }
    }

    @Override
    public boolean isVisible() {
        return visible;
    }

    @Override
    public void setVisible(boolean b) {
        visible = b;
    }
    public CustList<MockCustComponent> getAccessible() {
        CustList<MockCustComponent> acc_ = new CustList<MockCustComponent>();
        if (!isDeepAccessible()) {
            return acc_;
        }
        for (AbsCustComponent m: getChildren()) {
            if (((MockCustComponent)m).isAccessible()) {
                acc_.add((MockCustComponent) m);
            }
        }
        return acc_;
    }
    public CustList<MockCustComponent> getVisible() {
        CustList<MockCustComponent> acc_ = new CustList<MockCustComponent>();
        if (!isDeepVisible()) {
            return acc_;
        }
        for (AbsCustComponent m: getChildren()) {
            if (m.isVisible()) {
                acc_.add((MockCustComponent) m);
            }
        }
        return acc_;
    }
    public boolean isDeepAccessible() {
        AbsCustComponent current_ = this;
        while (current_ instanceof MockCustComponent) {
            if (!((MockCustComponent)current_).isAccessible()) {
                return false;
            }
            current_ = current_.getParent();
        }
        return true;
    }
    public boolean isDeepVisible() {
        AbsCustComponent current_ = this;
        while (current_ != null) {
            if (!current_.isVisible()) {
                return false;
            }
            current_ = current_.getParent();
        }
        return true;
    }

    public boolean isAccessible() {
        if (getHeight() * getWidth() == 0) {
            return false;
        }
        if (!isVisible()) {
            return false;
        }
        return accessible;
    }

    @Override
    public int getWidth() {
        return width;
    }

    @Override
    public int getHeight() {
        return height;
    }

    @Override
    public int heightFont() {
        return heightFont(metaFont);
    }

    @Override
    public int heightFont(MetaFont _font) {
        if (_font == null) {
            return 1;
        }
        return _font.getRealSize();
    }

    @Override
    public int stringWidth(String s) {
        return stringWidth(metaFont,s);
    }

    @Override
    public int stringWidth(MetaFont _font, String s) {
        if (_font == null) {
            return s.length();
        }
        return s.length()*_font.getRealSize();
    }

    @Override
    public MetaFont getMetaFont() {
        return metaFont;
    }

    @Override
    public void setNullFont() {
        metaFont = null;
    }

    @Override
    public void setFont(MetaFont _f) {
        metaFont = _f;
    }

    @Override
    public void setFont(String s, int i, int i1) {
        setFont(new MetaFont(s,i,i1));
    }

    @Override
    public AbsCustComponent getParent() {
        return parent;
    }

    @Override
    public CustList<AbsCustComponent> getChildren() {
        return children;
    }

    @Override
    public void setParent(AbsCustComponent absCustComponent) {
        parent = absCustComponent;
    }

    @Override
    public void setLineBorder(int i) {

    }

    @Override
    public void setLineBorder(int i, int i1) {

    }

    @Override
    public void setTitledBorder(String s) {

    }

    @Override
    public void setLoweredBorder() {

    }

    @Override
    public void setRaisedBorder() {

    }

    @Override
    public void setToolTipText(String s) {
        toolTipText = s;
    }

    @Override
    public void setHandCursor() {

    }

    @Override
    public void setSize(MetaDimension metaDimension) {
        height = metaDimension.getHeight();
        width = metaDimension.getWidth();
    }

    @Override
    public MetaDimension getPreferredSizeValue() {
        if (prefSizeSet) {
            return prefSize;
        }
        if (!isDeepVisible()) {
            MetaDimension metaDimension_ = new MetaDimension(0, 0);
            prefSize = metaDimension_;
            prefSizeSet = true;
            return metaDimension_;
        }
        MetaDimension metaDimension_ = new MetaDimension(Math.max(1, width), Math.max(1, height));
        prefSize = metaDimension_;
        prefSizeSet = true;
        return metaDimension_;
    }

    @Override
    public void setPreferredSize(MetaDimension metaDimension) {
        if (metaDimension == null) {
            prefSizeSet = false;
        } else {
            prefSize = metaDimension;
            prefSizeSet = true;
        }
    }

    @Override
    public boolean isFocusable() {
        return focusable;
    }

    @Override
    public void setFocusable(boolean b) {
        focusable = b;
        if (!b) {
            accessible = false;
        }
    }

    @Override
    public boolean isOpaque() {
        return false;
    }

    @Override
    public void setOpaque(boolean b) {

    }

    @Override
    public int getXcoords() {
        return 0;
    }

    @Override
    public int getYcoords() {
        return 0;
    }

    @Override
    public void setLocation(int i, int i1) {

    }

    @Override
    public void setBackground(int i) {

    }

    @Override
    public void setBackground(AbsCustComponent absCustComponent) {

    }

    @Override
    public int getBackgroundValue() {
        return 0;
    }

    @Override
    public void setForeground(int i) {

    }

    @Override
    public void setForeground(AbsCustComponent absCustComponent) {

    }

    @Override
    public int getForegroundValue() {
        return 0;
    }

    @Override
    public String getToolTipText() {
        return toolTipText;
    }

    @Override
    public void validate() {

    }

    @Override
    public void revalidate() {

    }

    @Override
    public void recalculate() {
        AbsCustComponent parent_ = getParent();
        if (parent_ instanceof MockCustComponent) {
            setSize(new MetaDimension(parent_.getWidth(), parent_.getHeight()));
        } else {
            setSize(getPreferredSizeValue());
        }
    }

    @Override
    public void top() {
        vertical = MockPosition.LEFT;
    }

    @Override
    public void bottom() {
        vertical = MockPosition.RIGHT;
    }

    @Override
    public void centerVert() {
        vertical = MockPosition.CENTER;
    }

    @Override
    public void left() {
        horizontal = MockPosition.LEFT;
    }

    @Override
    public void right() {
        horizontal = MockPosition.RIGHT;
    }

    @Override
    public void centerHoriz() {
        horizontal = MockPosition.CENTER;
    }

    public MockPosition getHorizontal() {
        return horizontal;
    }

    public MockPosition getVertical() {
        return vertical;
    }
}
