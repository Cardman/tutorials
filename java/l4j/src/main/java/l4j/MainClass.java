package l4j;

import javax.swing.*;

public class MainClass{
	public static void main(String...args){
		JFrame fr = new JFrame();
		fr.setContentPane(new JLabel(System.getProperty("java.version")));
		fr.pack();
		fr.setVisible(true);
		fr.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	}
}