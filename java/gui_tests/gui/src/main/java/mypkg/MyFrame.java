package mypkg;

import java.awt.*;
import javax.swing.*;

public class MyFrame {

	JFrame frame;

	public MyFrame(){
		frame = new JFrame();
        frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
	}

	public void setContentPane(MyComponent myCompo){
		frame.setContentPane(myCompo.component());
	}
	public void setVisible(boolean visible){
		frame.setVisible(visible);
	}
	public void pack(){
		frame.pack();
	}
	public void popupFirst(){
		JOptionPane.showMessageDialog(frame,"1");
	}
	public void popupSecond(){
		JOptionPane.showMessageDialog(frame,"2");
	}
}
