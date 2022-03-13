package sample;

import javax.swing.*;

public class MainClass1{
	public static void main(String...args){
		JFrame fr = new JFrame();
		fr.setContentPane(new JLabel(System.getProperty("java.version")+",1"));
		fr.pack();
		fr.setVisible(true);
		fr.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	}
}