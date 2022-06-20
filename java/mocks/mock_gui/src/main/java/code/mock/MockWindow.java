package code.mock;

import code.gui.*;
import code.gui.events.AbsWindowListener;
import code.gui.events.AbsWindowListenerClosing;
import code.gui.images.AbstractImage;
import code.gui.images.MetaPoint;
import code.gui.initialize.AbstractProgramInfos;
import code.util.CustList;
import code.util.IdList;

public abstract class MockWindow implements WithListener{
    private final IdList<AbsWindowListenerClosing> windowClosListeners = new IdList<AbsWindowListenerClosing>();
    private final IdList<AbsWindowListener> windowListeners = new IdList<AbsWindowListener>();
    private String title;
    private AbsPanel pane;
    private String accessFile;
    private String languageKey;
    private boolean visible;
    private boolean mainFrame;
    private AbsMenuBar menu;
    private final AbstractProgramInfos frames;
    private AbstractImage imageIconFrame;
    private Ownable owner;
    private int locationFirst;
    private int locationSecond;

    private MetaPoint locationOnScreen = new MetaPoint(0,0);

    protected MockWindow(AbstractProgramInfos frames) {
        this.frames = frames;
        pane = frames.getCompoFactory().newLineBox();
        menu = frames.getCompoFactory().newMenuBar();
    }

    public void addWindowListener(AbsWindowListener absWindowListener) {
        windowListeners.add(absWindowListener);
    }

    public void removeWindowListener(AbsWindowListener absWindowListener) {
        windowListeners.removeObj(absWindowListener);
    }

    public CustList<AbsWindowListener> getWindowListeners() {
        return windowListeners;
    }

    public AbsWindowListenerClosing addWindowListener(AbsWindowListenerClosing absWindowListenerClosing) {
        windowClosListeners.add(absWindowListenerClosing);
        return absWindowListenerClosing;
    }

    public AbsWindowListenerClosing removeWindowListener(AbsWindowListenerClosing absWindowListenerClosing) {
        windowClosListeners.removeObj(absWindowListenerClosing);
        return absWindowListenerClosing;
    }
    public CustList<AbsWindowListenerClosing> getWindowListenersDef() {
        return windowClosListeners;
    }

    public AbstractProgramInfos getFrames() {
        return frames;
    }

    public String getLanguageKey() {
        return languageKey;
    }

    public void setLanguageKey(String s) {
        languageKey = s;
    }

    public void setImageIconFrame(AbstractImage abstractImage) {
        imageIconFrame = abstractImage;
    }

    public void dispose() {
        setVisible(false);
    }

    public void requestFocus() {
        setVisible(isVisible());
    }

    public int getLocationFirst() {
        return locationFirst;
    }

    public int getLocationSecond() {
        return locationSecond;
    }

    public void setLocation(int i, int i1) {
        locationFirst = i;
        locationSecond = i1;
    }

    public int getWidth() {
        return pane.getWidth();
    }

    public int getHeight() {
        return pane.getHeight();
    }

    public String getAccessFile() {
        return accessFile;
    }

    public void setAccessFile(String s) {
        accessFile = s;
    }

    public void setContentPane(AbsPanel absPanel) {
        pane = absPanel;
    }

    public void setContentPane(AbsScrollPane _contentPane) {
        AbsPanel p_ = frames.getCompoFactory().newLineBox();
        p_.add(_contentPane);
        setContentPane(p_);
    }

    public AbsPanel getPane() {
        return pane;
    }

    public AbsMenuBar getJMenuBar() {
        return menu;
    }

    public void setJMenuBar(AbsMenuBar absMenuBar) {
        menu = absMenuBar;
    }

    public boolean isMainFrame() {
        return mainFrame;
    }

    public void setMainFrame(boolean b) {
        mainFrame = b;
    }

    public void setVisible(boolean b) {
        visible = b;
    }

    public void setLocationRelativeTo(AbsDialog absDialog) {
        locationFirst = absDialog.getLocationOnScreen().getXcoord()+((MockDialog)absDialog).getWidth()/2;
        locationSecond = absDialog.getLocationOnScreen().getYcoord()+((MockDialog)absDialog).getHeight()/2;
    }

    public void setLocationRelativeToWindow(Iconifiable iconifiable) {
        if (iconifiable instanceof MockDialog) {
            setLocationRelativeTo((MockDialog)iconifiable);
        } else if (iconifiable instanceof AbsGroupFrame) {
            setLocationRelativeTo((AbsGroupFrame)iconifiable);
        } else {
            setLocationRelativeToNull();
        }
    }

    public void setLocationRelativeTo(AbsCustComponent absCustComponent) {
        locationFirst = absCustComponent.getXcoords()+absCustComponent.getWidth()/2;
        locationSecond = absCustComponent.getYcoords()+absCustComponent.getHeight()/2;
    }

    public void setLocationRelativeTo(AbsGroupFrame absGroupFrame) {
        locationFirst = absGroupFrame.getLocationOnScreen().getXcoord()+absGroupFrame.getCommonFrame().getWidth()/2;
        locationSecond = absGroupFrame.getLocationOnScreen().getYcoord()+absGroupFrame.getCommonFrame().getHeight()/2;
    }

    public void setLocationRelativeToNull() {
        locationFirst = frames.getScreenWidth()/2;
        locationSecond = frames.getScreenHeight()/2;
    }

    public String getTitle() {
        return title;
    }

    public void setTitle(String s) {
        title = s;
    }

    public MetaPoint getLocationOnScreen() {
        return locationOnScreen;
    }

    public void setLocationOnScreen(MetaPoint locationOnScreen) {
        this.locationOnScreen = locationOnScreen;
    }

    public AbstractImage getImageIconFrame() {
        return imageIconFrame;
    }

    public boolean isVisible() {
        return visible;
    }

    public void pack() {
        recalculate(pane);
    }

    public static void recalculate(AbsCustComponent _compo) {
        _compo.setSize(_compo.getPreferredSizeValue());
        AbsCustComponent curr_ = _compo;
        while(curr_ != null) {
            curr_.recalculate();
            if (curr_ instanceof AbsScrollPane) {
                ((AbsScrollPane)curr_).recalculateViewport();
            }

            AbsCustComponent child_ = childAt(curr_, 0);
            if (child_ != null) {
                curr_ = child_;
            } else {
                while(curr_ != null) {
                    AbsCustComponent par_ = curr_.getParent();
                    int index_ = indexOf(par_, curr_);
                    AbsCustComponent next_ = childAt(par_, index_ + 1);
                    if (next_ != null) {
                        curr_ = next_;
                        break;
                    }

                    curr_ = par_;
                }
            }
        }
    }

    private static AbsCustComponent childAt(AbsCustComponent _elt, int _index) {
        if (_elt == null) {
            return null;
        }
        CustList<AbsCustComponent> children_ = _elt.getChildren();
        if (!children_.isValidIndex(_index)) {
            return null;
        }
        return children_.get(_index);
    }

    private static int indexOf(AbsCustComponent _par, AbsCustComponent _elt) {
        if ( _par == null) {
            return -1;
        }
        return indexOf(_par.getChildren(), _elt);
    }

    public static int indexOf(CustList<AbsCustComponent> _list, AbsCustComponent _elt) {
        int len_ = _list.size();

        for(int i = 0; i < len_; i++) {
            AbsCustComponent c = _list.get(i);
            if (c == _elt) {
                return i;
            }
        }

        return -1;
    }
    public Ownable getOwner() {
        return owner;
    }

    public void setOwner(Ownable ownable) {
        owner = ownable;
    }

    public AbsPanel getContentPane() {
        return getPane();
    }

    public void setDefaultCloseOperation(int _i) {
        setVisible(isVisible());
    }

    public void setIconImage(AbstractImage abstractImage) {
        setImageIconFrame(abstractImage);
    }
}
