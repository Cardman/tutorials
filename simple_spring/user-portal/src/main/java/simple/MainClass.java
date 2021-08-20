package simple;

import java.awt.*;
import javax.swing.*;

public final class MainClass{
	public static void main(String...args){
		SwingUtilities.invokeLater(new MyFrame());
	}
}

final class MyFrame implements Runnable{
	@Override
	public void run(){
		JFrame fr = new JFrame(Integer.toString(MyClass.db(1)));
		fr.setVisible(true);
		fr.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
	}
}