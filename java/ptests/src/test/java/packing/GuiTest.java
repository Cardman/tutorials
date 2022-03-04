package packing;

import org.junit.*;
import javax.swing.*;

public class GuiTest{
	@Test
	public void _1(){
		try {
			JPanel p = new JPanel();
			p.add(new JLabel());
		} catch (Throwable t){
			System.out.println("KO panel");
		}
	}
	@Test
	public void _2(){
		try {
			JFrame p = new JFrame();
		} catch (Throwable t){
			System.out.println("KO frame");
		}
	}
}