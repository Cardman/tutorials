package mypkg;

import javax.swing.*;

public class MyButton extends MyComponent implements IntButton{

	JButton button;
	public MyButton(String label){
		button = new JButton(label);
	}
	public MyButton(ButtonContent label){
		button = new JButton(label.text);
	}
	public void addAction(EcAction action){
		AdapterAction aa = new AdapterAction();
		aa.ea = action;
		button.addActionListener(aa);
	}
	JComponent component(){
		return button;
	}
}