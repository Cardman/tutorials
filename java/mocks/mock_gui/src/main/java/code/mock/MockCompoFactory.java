package code.mock;

import code.gui.*;
import code.gui.images.AbstractImage;
import code.gui.initialize.AbsCompoFactory;

public class MockCompoFactory implements AbsCompoFactory {
    @Override
    public AbsTreeGui newTreeGui(AbstractMutableTreeNode abstractMutableTreeNode) {
        return new MockTreeGui(abstractMutableTreeNode);
    }

    @Override
    public AbstractMutableTreeNode newMutableTreeNode(String s) {
        return new MockMutableTreeNode(s);
    }

    @Override
    public AbsPaintableLabel newAbsPaintableLabel(AbsMetaLabel absMetaLabel) {
        return new MockPaintableLabel(absMetaLabel);
    }

    @Override
    public AbsPaintableLabel newAbsPaintableLabel() {
        return new MockPaintableLabelNo();
    }

    @Override
    public AbsPreparedLabel newPreparedLabel(AbstractImage abstractImage) {
        return new MockPreparedLabel(abstractImage);
    }

    @Override
    public AbsPreparedLabel newPreparedLabel(String s) {
        return new MockPreparedLabel();
    }

    @Override
    public AbsImgButton newImgButton(AbstractImage abstractImage) {
        abstractImage.getWidth();
        return new MockImgButton();
    }

    @Override
    public void invokeLater(Runnable _runnable) {
        //boolean to include for immediate or not
        //sample immediate true for autocomplete
    }

    @Override
    public AbsPanel newAbsolute() {
        return new MockPanel(MockLayout.ABSOLUTE);
    }

    @Override
    public AbsPanel newBorder() {
        return new MockPanel(MockLayout.BORDER);
    }

    @Override
    public AbsPanel newGrid(int i, int i1) {
        return new MockPanel(MockLayout.GRID);
    }

    @Override
    public AbsPanel newGrid(int i, int i1, int i2, int i3) {
        return new MockPanel(MockLayout.GRID);
    }

    @Override
    public AbsPanel newPageBox() {
        return new MockPanel(MockLayout.PAGE);
    }

    @Override
    public AbsPanel newLineBox() {
        return new MockPanel(MockLayout.LINE);
    }

    @Override
    public AbsScrollPane newAbsScrollPane() {
        return new MockScrollPane();
    }

    @Override
    public AbsScrollPane newAbsScrollPane(AbsCustComponent absCustComponent) {
        return new MockScrollPane(absCustComponent);
    }

    @Override
    public AbsScrollPane newAbsScrollPane(AbsMetaLabel absMetaLabel) {
        return new MockScrollPane(absMetaLabel);
    }

    @Override
    public AbsTabbedPane newAbsTabbedPane() {
        return new MockTabbedPane();
    }

    @Override
    public AbsSplitPane newVerticalSplitPane(AbsCustComponent absCustComponent, AbsCustComponent absCustComponent1) {
        return new MockSplitPane(false,absCustComponent,absCustComponent1);
    }

    @Override
    public AbsSplitPane newHorizontalSplitPane(AbsCustComponent absCustComponent, AbsCustComponent absCustComponent1) {
        return new MockSplitPane(true,absCustComponent,absCustComponent1);
    }

    @Override
    public AbsPopupMenu newAbsPopupMenu() {
        return new MockPopupMenu();
    }

    @Override
    public AbsSlider newAbsSlider() {
        return new MockSlider();
    }

    @Override
    public AbsSlider newAbsSlider(int _o) {
        return new MockSlider(_o);
    }

    @Override
    public AbsSlider newAbsSlider(int _min, int _max) {
        return new MockSlider(_min, _max);
    }

    @Override
    public AbsSlider newAbsSlider(int _min, int _max, int _v) {
        return new MockSlider(_min, _max, _v);
    }

    @Override
    public AbsSlider newAbsSlider(int _o, int _min, int _max, int _v) {
        return new MockSlider(_o, _min, _max, _v);
    }

    @Override
    public AbsProgressBar newAbsProgressBar() {
        return new MockProgressBar();
    }

    @Override
    public AbsSpinner newSpinner(int i, int i1, int i2, int i3) {
        return new MockSpinner(i,i1,i2,i3);
    }

    @Override
    public AbsTextArea newTextArea() {
        return new MockTextArea();
    }

    @Override
    public AbsTextArea newTextArea(int i, int i1) {
        return new MockTextArea(i,i1);
    }

    @Override
    public AbsTextArea newTextArea(String s) {
        return new MockTextArea(s);
    }

    @Override
    public AbsTextArea newTextArea(String s, int i, int i1) {
        return new MockTextArea(s,i,i1);
    }

    @Override
    public AbsTextField newTextField() {
        return new MockTextField();
    }

    @Override
    public AbsTextField newTextField(int i) {
        return new MockTextField(i);
    }

    @Override
    public AbsTextField newTextField(String s) {
        return new MockTextField(s);
    }

    @Override
    public AbsTextField newTextField(String s, int i) {
        return new MockTextField(s,i);
    }

    @Override
    public AbsCustCheckBox newCustCheckBox() {
        return new MockCustCheckBox();
    }

    @Override
    public AbsCustCheckBox newCustCheckBox(String s) {
        return new MockCustCheckBox(s);
    }

    @Override
    public AbsCustCheckBox newCustCheckBox(String s, boolean b) {
        return new MockCustCheckBox(s,b);
    }

    @Override
    public AbsPlainButton newPlainButton() {
        return new MockPlainButton();
    }

    @Override
    public AbsPlainButton newPlainButton(String s) {
        return new MockPlainButton(s);
    }

    @Override
    public AbsRadioButton newRadioButton() {
        return new MockRadioButton();
    }

    @Override
    public AbsRadioButton newRadioButton(String s) {
        return new MockRadioButton(s);
    }

    @Override
    public AbsRadioButton newRadioButton(String s, boolean b) {
        return new MockRadioButton(s,b);
    }

    @Override
    public AbsPlainLabel newPlainLabel(String s) {
        return new MockPlainLabel(s);
    }

    @Override
    public AbsTableGui newTableGui(String... strings) {
        return new MockTableGui(strings);
    }

    @Override
    public AbsWrappedTextArea newWrappedTextArea(int i, int i1) {
        return new MockWrappedTextArea(i,i1);
    }

    @Override
    public AbsMenuBar newMenuBar() {
        return null;
    }

    @Override
    public AbsMenu newMenu() {
        return null;
    }

    @Override
    public AbsMenu newMenu(String s) {
        return null;
    }

    @Override
    public AbsCheckBoxMenuItem newCheckBoxMenuItem() {
        return null;
    }

    @Override
    public AbsCheckBoxMenuItem newCheckBoxMenuItem(String s) {
        return null;
    }

    @Override
    public AbsMenuItem newMenuItem() {
        return null;
    }

    @Override
    public AbsMenuItem newMenuItem(String s) {
        return null;
    }
}
