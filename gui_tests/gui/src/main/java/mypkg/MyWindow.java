package mypkg;

public class MyWindow implements IntWindow {

	MyFrame frame = new MyFrame();
	MyButton button;
	MyCheckBox check;
	AddEventsImpl adding = new AddEventsImpl();
	MyPanel panel;

	public void init(){
		button = new MyButton("Add");
		check = new MyCheckBox("First");
		panel = new MyPanel();
		EcActionCreator eac = new EcActionCreator();
		eac.w = this;
		button.addAction(eac);
		panel.add(check);
		panel.add(button);
		frame.setContentPane(panel);
		frame.pack();
        frame.setVisible(true);
	}
	public void addButton(){
		ButtonContent content = AddEventsUtil.createButtonContent(check,adding, "First","Second");
		MyButton b = new MyButton(content);
		AddEventsUtil.process(b,this,check,adding);
		panel.add(b);
		frame.pack();
	}
	public void popupFirst(){
		frame.popupFirst();
	}
	public void popupSecond(){
		frame.popupSecond();
	}
}
