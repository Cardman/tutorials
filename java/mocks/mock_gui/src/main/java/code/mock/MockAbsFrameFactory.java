package code.mock;

import code.gui.AbsCustComponent;
import code.gui.initialize.AbsFrameFactory;
import code.gui.initialize.AbsLightFrameFactory;
import code.gui.initialize.AbstractProgramInfos;

public abstract class MockAbsFrameFactory implements AbsFrameFactory, AbsLightFrameFactory {
    private final AbstractProgramInfos programInfos;

    protected MockAbsFrameFactory(AbstractProgramInfos programInfos) {
        this.programInfos = programInfos;
    }

    public AbstractProgramInfos getProgramInfos() {
        return programInfos;
    }

    @Override
    public void setCursor(AbsCustComponent absCustComponent, int i, int i1, int[] ints) {
        absCustComponent.setHandCursor();
    }
}
