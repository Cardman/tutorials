package gltuto.gui;

import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.MouseWheelEvent;
import java.awt.event.MouseWheelListener;

import javax.swing.JFrame;

import com.jogamp.opengl.GLCapabilities;
import com.jogamp.opengl.GLProfile;
import com.jogamp.opengl.awt.GLCanvas;
import com.jogamp.opengl.util.FPSAnimator;

public final class MainFrame extends JFrame implements KeyListener, MouseWheelListener {
    private MyGLEventListener glListener;
    private FPSAnimator animator;
    public MainFrame(){
        setTitle("Lit Sphere Demo, with JOGL");
        setSize(640, 480);
//        System.setProperty("jogamp.debug", "true");
        GLCapabilities glCapabilities_ = new GLCapabilities(GLProfile.getDefault());
//        System.err.println("");
//        System.err.println("");
//        System.err.println("");
//        System.err.println("");
//        System.err.println("");
//        System.err.println("");
//        System.clearProperty("jogamp.debug");
        GLCanvas glCanvas_ = new GLCanvas(glCapabilities_);
        glListener = new MyGLEventListener();
        glCanvas_.addGLEventListener(glListener);
        add(glCanvas_);

        animator = new FPSAnimator(glCanvas_, 60);

        addWindowListener(new CloseWindow(animator));

        animator.start();
        glCanvas_.addKeyListener(this);
        glCanvas_.addMouseWheelListener(this);
        requestFocus(false);
    }

    @Override
    public void keyTyped(KeyEvent _e) {
    }

    @Override
    public void keyPressed(KeyEvent _e) {
        Direction dir_;
        if (_e.getKeyCode() == KeyEvent.VK_UP) {
            dir_ = Direction.UP;
        } else if (_e.getKeyCode() == KeyEvent.VK_DOWN) {
            dir_ = Direction.DOWN;
        } else if (_e.getKeyCode() == KeyEvent.VK_LEFT) {
            dir_ = Direction.LEFT;
        } else if (_e.getKeyCode() == KeyEvent.VK_RIGHT) {
            dir_ = Direction.RIGHT;
        } else {
            return;
        }
        glListener.setDirection(dir_);
    }

    @Override
    public void keyReleased(KeyEvent _e) {
    }

    @Override
    public void mouseWheelMoved(MouseWheelEvent _e) {
        glListener.setzPt(_e.getUnitsToScroll());
    }
}
