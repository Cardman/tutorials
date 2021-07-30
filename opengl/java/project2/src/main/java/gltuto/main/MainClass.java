package gltuto.main;

import gltuto.gui.MainFrame;

import javax.imageio.ImageIO;

public final class MainClass {

    private MainClass(){
    }
    public static void main(String[] _args) {
        ImageIO.setUseCache(false);
        new MainFrame().setVisible(true);
    }

}
