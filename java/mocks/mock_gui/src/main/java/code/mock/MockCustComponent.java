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
    private boolean opaque;
    private int xcoords;
    private int ycoords;
    private int width;
    private int height;
    private boolean prefSizeSet;
    private MetaDimension prefSize;
    private int foreground;
    private int background;
    private String border="";
    private final CustList<AbsCustComponent> children = new CustList<AbsCustComponent>();
    private final IdList<AbsMouseListener> mouseListeners = new IdList<AbsMouseListener>();
    private final IdList<AbsMouseListenerPresRel> mousePresRelListeners = new IdList<AbsMouseListenerPresRel>();
    private final IdList<AbsMouseListenerIntRel> mouseIntRelListeners = new IdList<AbsMouseListenerIntRel>();
    private final IdList<AbsMouseListenerEnt> mouseEntListeners = new IdList<AbsMouseListenerEnt>();
    private final IdList<AbsMouseListenerCl> mouseClListeners = new IdList<AbsMouseListenerCl>();
    private final IdList<AbsMouseListenerWithoutClick> mouseWithoutClickListeners = new IdList<AbsMouseListenerWithoutClick>();
    private final IdList<AbsMouseListenerWithoutClickPr> mouseWithoutClickPrListeners = new IdList<AbsMouseListenerWithoutClickPr>();
    private final IdList<AbsMouseListenerEer> mouseEerListeners = new IdList<AbsMouseListenerEer>();
    private final IdList<AbsMouseMotionListener> mouseMotionListeners = new IdList<AbsMouseMotionListener>();
    private final IdList<AbsMouseWheelListener> mouseWheelListeners = new IdList<AbsMouseWheelListener>();
    private final IdList<AbsKeyListener> keyListeners = new IdList<AbsKeyListener>();
    private final IdList<AbsKeyListenerPress> keyPressListeners = new IdList<AbsKeyListenerPress>();
    private final IdList<AbsKeyListenerReleased> keyReleasedListeners = new IdList<AbsKeyListenerReleased>();
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
        mousePresRelListeners.add(absMouseListenerPresRel);
    }

    @Override
    public void addMouseListener(AbsMouseListenerIntRel absMouseListenerIntRel) {
        mouseIntRelListeners.add(absMouseListenerIntRel);
    }

    @Override
    public void addMouseListener(AbsMouseListenerEnt absMouseListenerEnt) {
        mouseEntListeners.add(absMouseListenerEnt);
    }

    @Override
    public void addMouseListener(AbsMouseListenerCl absMouseListenerCl) {
        mouseClListeners.add(absMouseListenerCl);
    }

    @Override
    public void addMouseListener(AbsMouseListenerWithoutClick absMouseListenerWithoutClick) {
        mouseWithoutClickListeners.add(absMouseListenerWithoutClick);
    }

    @Override
    public void addMouseListener(AbsMouseListenerWithoutClickPr absMouseListenerWithoutClickPr) {
        mouseWithoutClickPrListeners.add(absMouseListenerWithoutClickPr);
    }

    @Override
    public void addMouseListener(AbsMouseListenerEer absMouseListenerEer) {
        mouseEerListeners.add(absMouseListenerEer);
    }

    @Override
    public void addMouseMotionListener(AbsMouseMotionListener absMouseMotionListener) {
        mouseMotionListeners.add(absMouseMotionListener);
    }

    @Override
    public void addMouseWheelListener(AbsMouseWheelListener absMouseWheelListener) {
        mouseWheelListeners.add(absMouseWheelListener);
    }

    @Override
    public void addKeyListener(AbsKeyListener absKeyListener) {
        keyListeners.add(absKeyListener);
    }

    @Override
    public void addKeyListener(AbsKeyListenerPress absKeyListenerPress) {
        keyPressListeners.add(absKeyListenerPress);
    }

    @Override
    public void addKeyListener(AbsKeyListenerReleased absKeyListenerReleased) {
        keyReleasedListeners.add(absKeyListenerReleased);
    }

    @Override
    public void removeMouseListener(AbsMouseListener absMouseListener) {
        mouseListeners.removeObj(absMouseListener);
    }

    @Override
    public void removeMouseMotionListener(AbsMouseMotionListener absMouseMotionListener) {
        mouseMotionListeners.removeObj(absMouseMotionListener);
    }

    @Override
    public void removeMouseWheelListener(AbsMouseWheelListener absMouseWheelListener) {
        mouseWheelListeners.removeObj(absMouseWheelListener);
    }

    @Override
    public void removeKeyListener(AbsKeyListener absKeyListener) {
        keyListeners.removeObj(absKeyListener);
    }

    public IdList<AbsMouseListenerEer> getMouseEerListeners() {
        return mouseEerListeners;
    }

    public IdList<AbsMouseListenerWithoutClick> getMouseWithoutClickListeners() {
        return mouseWithoutClickListeners;
    }

    public IdList<AbsMouseListenerWithoutClickPr> getMouseWithoutClickPrListeners() {
        return mouseWithoutClickPrListeners;
    }

    public IdList<AbsMouseListenerCl> getMouseClListeners() {
        return mouseClListeners;
    }

    public IdList<AbsMouseListenerEnt> getMouseEntListeners() {
        return mouseEntListeners;
    }

    public IdList<AbsMouseListenerPresRel> getMousePresRelListeners() {
        return mousePresRelListeners;
    }

    public IdList<AbsMouseListenerIntRel> getMouseIntRelListeners() {
        return mouseIntRelListeners;
    }

    public IdList<AbsKeyListenerPress> getKeyPressListeners() {
        return keyPressListeners;
    }

    public IdList<AbsKeyListenerReleased> getKeyReleasedListeners() {
        return keyReleasedListeners;
    }

    @Override
    public CustList<AbsMouseListener> getMouseListeners() {
        return mouseListeners;
    }

    @Override
    public CustList<AbsMouseMotionListener> getMouseMotionListeners() {
        return mouseMotionListeners;
    }

    @Override
    public CustList<AbsMouseWheelListener> getMouseWheelListeners() {
        return mouseWheelListeners;
    }

    @Override
    public CustList<AbsKeyListener> getKeyListeners() {
        return keyListeners;
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
        border = "line "+i;
    }

    @Override
    public void setLineBorder(int i, int i1) {
        border = "line "+i+" "+i1;
    }

    @Override
    public void setTitledBorder(String s) {
        border = "title "+s;
    }

    @Override
    public void setLoweredBorder() {
        border = "lower";
    }

    @Override
    public void setRaisedBorder() {
        border = "raised";
    }

    @Override
    public void setToolTipText(String s) {
        toolTipText = s;
    }

    @Override
    public void setHandCursor() {
        setFont(getMetaFont());
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
        return opaque;
    }

    @Override
    public void setOpaque(boolean b) {
        opaque = b;
    }

    @Override
    public int getXcoords() {
        return xcoords;
    }

    @Override
    public int getYcoords() {
        return ycoords;
    }

    @Override
    public void setLocation(int i, int i1) {
        xcoords = i;
        ycoords = i1;
    }

    @Override
    public void setBackground(int i) {
        background = i;
    }

    @Override
    public void setBackground(AbsCustComponent absCustComponent) {
        setBackground(absCustComponent.getBackgroundValue());
    }

    @Override
    public int getBackgroundValue() {
        return background;
    }

    @Override
    public void setForeground(int i) {
        foreground = i;
    }

    @Override
    public void setForeground(AbsCustComponent absCustComponent) {
        setForeground(absCustComponent.getForegroundValue());
    }

    @Override
    public int getForegroundValue() {
        return foreground;
    }

    @Override
    public String getToolTipText() {
        return toolTipText;
    }

    @Override
    public void validate() {
        setPreferredSize(getPreferredSizeValue());
    }

    @Override
    public void revalidate() {
        setPreferredSize(getPreferredSizeValue());
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

    public String getBorder() {
        return border;
    }

    public MockPosition getHorizontal() {
        return horizontal;
    }

    public MockPosition getVertical() {
        return vertical;
    }
}
