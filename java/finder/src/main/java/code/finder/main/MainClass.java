package code.finder.main;

import code.finder.gui.WindowFinder;
import code.vi.sys.impl.variant.DefOtherProgramInfos;

import javax.swing.*;

public final class MainClass implements Runnable {
    public static void main(String..._args) {
        SwingUtilities.invokeLater(new MainClass());
    }

    @Override
    public void run() {
        new WindowFinder(new DefOtherProgramInfos());
    }
}
