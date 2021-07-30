package myshaders;

import java.awt.BorderLayout;

import javax.swing.JFrame;
import javax.swing.SwingUtilities;

public class MainClass extends Thread {

	public static void main(String[] _args) {
        SwingUtilities.invokeLater(new MainClass());
    }

    @Override
    public void run() {
        JFrame jf_ = new JFrame();
        jf_.setSize(800,600);
        jf_.getContentPane().setLayout(new BorderLayout());
        jf_.getContentPane().add(new MyShaders(), BorderLayout.CENTER);
        jf_.setVisible(true);
        jf_.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }

}
