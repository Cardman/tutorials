package code.finder.gui.events;

import code.finder.gui.WindowFinder;
import code.gui.events.AbsActionListener;

public final class SelectFolder implements AbsActionListener {
    private final WindowFinder windowFinder;

    public SelectFolder(WindowFinder _windowFinder) {
        this.windowFinder = _windowFinder;
    }

    @Override
    public void action() {
        windowFinder.read();
    }
}
