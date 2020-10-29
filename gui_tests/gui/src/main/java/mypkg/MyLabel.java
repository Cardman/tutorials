package mypkg;

import java.awt.event.ActionListener;
import javax.swing.*;

public class MyLabel extends MyComponent implements IntDisplayLabel{

	JLabel button;
	public MyLabel(String label){
		button = new JLabel(label);
	}
	public void setText(String label){
		button.setText(label);
	}
	JComponent component(){
		return button;
	}
}