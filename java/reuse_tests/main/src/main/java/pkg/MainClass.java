package pkg;

import javax.swing.*;

public class MainClass{
	public static void main(String[] a){
		JFrame fr = new JFrame();
		fr.setContentPane(new JLabel(System.getProperty("java.version")+",1"));
		fr.pack();
		fr.setVisible(true);
		fr.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	}
	public static String[] calledTest(String...args){
		return args;
	}
}