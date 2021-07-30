package gltuto.gui;

import java.awt.Point;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;
import java.awt.event.MouseWheelEvent;
import java.awt.event.MouseWheelListener;

import javax.swing.JFrame;

import com.jogamp.opengl.GLCapabilities;
import com.jogamp.opengl.GLProfile;
import com.jogamp.opengl.awt.GLCanvas;
import com.jogamp.opengl.util.FPSAnimator;

public final class MainFrame extends JFrame implements KeyListener, MouseWheelListener, MouseMotionListener, MouseListener {
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
        glListener.move(320, 240);
        glCanvas_.addGLEventListener(glListener);
        add(glCanvas_);

        animator = new FPSAnimator(glCanvas_, 60);

        addWindowListener(new CloseWindow(animator));

        animator.start();
        glCanvas_.addKeyListener(this);
        glCanvas_.addMouseMotionListener(this);
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

    @Override
    public void mouseDragged(MouseEvent _e) {
    }

    @Override
    public void mouseMoved(MouseEvent _e) {
        Point pt_ = _e.getPoint();
        glListener.move(pt_.x, pt_.y);
    }

    @Override
    public void mouseClicked(MouseEvent _e) {
    }

    @Override
    public void mousePressed(MouseEvent _e) {
    }

    @Override
    public void mouseReleased(MouseEvent _e) {
        requestFocus(false);
    }

    @Override
    public void mouseEntered(MouseEvent _e) {
    }

    @Override
    public void mouseExited(MouseEvent _e) {
    }
}
