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
        locationFirst = absDialog.getLocationOnScreen().getXcoord()+((MockAbsDialog)absDialog).getWidth()/2;
        locationSecond = absDialog.getLocationOnScreen().getYcoord()+((MockAbsDialog)absDialog).getHeight()/2;
    }

    public void setLocationRelativeToWindow(Iconifiable iconifiable) {
        if (iconifiable instanceof MockAbsDialog) {
            setLocationRelativeTo((MockAbsDialog)iconifiable);
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
