package mypkg;

import java.awt.*;
import javax.swing.*;

public class MyPanel extends MyComponent {

	JPanel panel = new JPanel(new GridLayout(0,1));

	public void add(MyComponent myCompo){
		panel.add(myCompo.component());
	}
	JComponent component(){
		return panel;
	}
}
