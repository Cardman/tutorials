package code.mock;

import code.gui.AbsCloseableDialog;
import code.gui.AbsDialog;
import code.gui.AbsOtherDialog;
import code.gui.Iconifiable;
import code.gui.images.AbstractImageFactory;
import code.gui.initialize.AbstractProgramInfos;

public abstract class MockAbsDialog extends MockWindow implements AbsDialog, AbsOtherDialog {

    private boolean modal;
    private boolean resizable;
    private AbsCloseableDialog event;

    protected MockAbsDialog(AbstractProgramInfos frames) {
        super(frames);
    }

    protected MockAbsDialog(AbsCloseableDialog _cl, AbstractProgramInfos frames) {
        super(frames);
        event = _cl;
    }

    public boolean isResizable() {
        return resizable;
    }

    @Override
    public void setResizable(boolean b) {
        resizable = b;
    }

    @Override
    public void setDialogIcon(AbstractImageFactory abstractImageFactory, Iconifiable _group) {
        setImageIconFrame(_group.getImageIconFrame());
    }

    @Override
    public void setModal(boolean b) {
        modal = b;
    }

    @Override
    public boolean isModal() {
        return modal;
    }

    @Override
    public void closeWindow() {
        if (event != null) {
            event.closeWindow();
            return;
        }
        setVisible(false);
        getContentPane().removeAll();
    }

}
