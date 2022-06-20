package code.mock;

import code.gui.AbsMetaLabel;
import code.gui.images.AbstractImage;
import code.gui.images.AbstractImageFactory;

public class MockPaintableLabel extends MockPaintableLabelAbs{

    private final AbsMetaLabel metaLabel;
    public MockPaintableLabel(AbsMetaLabel _meta) {
        metaLabel = _meta;
    }

    @Override
    public void repaintLabel(AbstractImageFactory abstractImageFactory) {
        int w_ = getWidth();
        int h_ = getHeight();
        if (w_ <= 0 || h_ <= 0) {
            setEmptyIcon();
            return;
        }
        AbstractImage img_ = abstractImageFactory.newImageArgb(w_, h_);
        img_.setFont(metaLabel);
        metaLabel.paintComponent(img_);
        setIcon(abstractImageFactory,img_);
    }
}
