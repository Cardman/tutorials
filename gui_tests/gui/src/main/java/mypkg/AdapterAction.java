package mypkg;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class AdapterAction implements ActionListener {

	EcAction ea;

	public void actionPerformed(ActionEvent e) {
		ea.act();
	}
}