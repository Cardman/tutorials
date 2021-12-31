package code.finder.gui.events;

import code.finder.gui.WindowFinder;
import code.gui.events.AbsActionListener;

public final class ResultSystem implements AbsActionListener {
    private final WindowFinder windowFinder;

    public ResultSystem(WindowFinder _windowFinder) {
        this.windowFinder = _windowFinder;
    }

    @Override
    public void action() {
        windowFinder.resultSystem();
    }
}
