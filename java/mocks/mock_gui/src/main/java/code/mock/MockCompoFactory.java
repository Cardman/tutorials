package code.mock;

import code.gui.*;
import code.gui.images.AbstractImage;
import code.gui.initialize.AbsCompoFactory;

public class MockCompoFactory implements AbsCompoFactory {
    @Override
    public AbsTreeGui newTreeGui(AbstractMutableTreeNode abstractMutableTreeNode) {
        return null;
    }

    @Override
    public AbstractMutableTreeNode newMutableTreeNode(String s) {
        return null;
    }

    @Override
    public AbsPaintableLabel newAbsPaintableLabel(AbsMetaLabel absMetaLabel) {
        return null;
    }

    @Override
    public AbsPaintableLabel newAbsPaintableLabel() {
        return null;
    }

    @Override
    public AbsPreparedLabel newPreparedLabel(AbstractImage abstractImage) {
        return new MockPreparedLabel();
    }

    @Override
    public AbsPreparedLabel newPreparedLabel(String s) {
        return new MockPreparedLabel();
    }

    @Override
    public AbsImgButton newImgButton(AbstractImage abstractImage) {
        return null;
    }

    @Override
    public void invokeLater(Runnable _runnable) {
        //boolean to include for immediate or not
        //sample immediate true for autocomplete
    }

    @Override
    public AbsPanel newAbsolute() {
        return null;
    }

    @Override
    public AbsPanel newBorder() {
        return null;
    }

    @Override
    public AbsPanel newGrid(int i, int i1) {
        return null;
    }

    @Override
    public AbsPanel newGrid(int i, int i1, int i2, int i3) {
        return null;
    }

    @Override
    public AbsPanel newPageBox() {
        return null;
    }

    @Override
    public AbsPanel newLineBox() {
        return null;
    }

    @Override
    public AbsScrollPane newAbsScrollPane() {
        return null;
    }

    @Override
    public AbsScrollPane newAbsScrollPane(AbsCustComponent absCustComponent) {
        return null;
    }

    @Override
    public AbsScrollPane newAbsScrollPane(AbsMetaLabel absMetaLabel) {
        return null;
    }

    @Override
    public AbsTabbedPane newAbsTabbedPane() {
        return null;
    }

    @Override
    public AbsSplitPane newVerticalSplitPane(AbsCustComponent absCustComponent, AbsCustComponent absCustComponent1) {
        return null;
    }

    @Override
    public AbsSplitPane newHorizontalSplitPane(AbsCustComponent absCustComponent, AbsCustComponent absCustComponent1) {
        return null;
    }

    @Override
    public AbsPopupMenu newAbsPopupMenu() {
        return null;
    }

    @Override
    public AbsSlider newAbsSlider() {
        return null;
    }

    @Override
    public AbsSlider newAbsSlider(int i) {
        return null;
    }

    @Override
    public AbsSlider newAbsSlider(int i, int i1) {
        return null;
    }

    @Override
    public AbsSlider newAbsSlider(int i, int i1, int i2) {
        return null;
    }

    @Override
    public AbsSlider newAbsSlider(int i, int i1, int i2, int i3) {
        return null;
    }

    @Override
    public AbsProgressBar newAbsProgressBar() {
        return null;
    }

    @Override
    public AbsSpinner newSpinner(int i, int i1, int i2, int i3) {
        return null;
    }

    @Override
    public AbsTextArea newTextArea() {
        return null;
    }

    @Override
    public AbsTextArea newTextArea(int i, int i1) {
        return null;
    }

    @Override
    public AbsTextArea newTextArea(String s) {
        return null;
    }

    @Override
    public AbsTextArea newTextArea(String s, int i, int i1) {
        return null;
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
        return null;
    }

    @Override
    public AbsCustCheckBox newCustCheckBox(String s) {
        return null;
    }

    @Override
    public AbsCustCheckBox newCustCheckBox(String s, boolean b) {
        return null;
    }

    @Override
    public AbsPlainButton newPlainButton() {
        return null;
    }

    @Override
    public AbsPlainButton newPlainButton(String s) {
        return null;
    }

    @Override
    public AbsRadioButton newRadioButton() {
        return null;
    }

    @Override
    public AbsRadioButton newRadioButton(String s) {
        return null;
    }

    @Override
    public AbsRadioButton newRadioButton(String s, boolean b) {
        return null;
    }

    @Override
    public AbsPlainLabel newPlainLabel(String s) {
        return null;
    }

    @Override
    public AbsTableGui newTableGui(String... strings) {
        return null;
    }

    @Override
    public AbsWrappedTextArea newWrappedTextArea(int i, int i1) {
        return null;
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
