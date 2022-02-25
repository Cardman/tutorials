package mypkg;

public class MyWindow implements IntWindow {

	MyFrame frame = new MyFrame();
	MyButton button;
	MyButton buttonTitle;
	MyLabel label = new MyLabel("before");
	MyCheckBox check;
	AddEventsImpl adding = new AddEventsImpl();
	MyPanel panel;
	IntManagerThread intManager = new ManagerThreadImpl();

	public void init(){
		button = new MyButton("Add");
		buttonTitle = new MyButton("Change Text");
		check = new MyCheckBox("First");
		panel = new MyPanel();
		EcActionCreator eac = new EcActionCreator();
		eac.w = this;
		button.addAction(eac);
		EcActionResult ear = new EcActionResult();
		ear.w = label;
		ear.intManager = intManager;
		buttonTitle.addAction(ear);
		panel.add(label);
		panel.add(check);
		panel.add(button);
		panel.add(buttonTitle);
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
