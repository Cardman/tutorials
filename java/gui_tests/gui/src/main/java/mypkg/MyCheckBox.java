package mypkg;

import javax.swing.*;

public class MyCheckBox extends MyComponent implements IntLabel {

	JCheckBox button;
	public MyCheckBox(String label){
		button = new JCheckBox(label);
	}
	public boolean isSelected(){
		return button.isSelected();
	}
	JComponent component(){
		return button;
	}
}