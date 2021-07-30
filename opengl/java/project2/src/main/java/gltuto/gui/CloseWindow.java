package gltuto.gui;

import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

import com.jogamp.opengl.util.FPSAnimator;

public final class CloseWindow extends WindowAdapter {

    private FPSAnimator animator;

    public CloseWindow(FPSAnimator _animator) {
        animator = _animator;
    }

    @Override
    public void windowClosing(WindowEvent _e) {
        animator.stop();
        System.exit(0);
    }

}
