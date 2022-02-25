package mypkg;

public class AddEventsImpl implements AddEvents {

	public ButtonContent createButtonContent(String label){
		ButtonContent b = new ButtonContent();
		b.text = label;
		return b;
	}
	public void addFirst(IntWindow instance, IntButton button){
		EcActionPopupFirst l = new EcActionPopupFirst();
		l.w = instance;
		button.addAction(l);
	}
	public void addSecond(IntWindow instance, IntButton button){
		EcActionPopupSecond l = new EcActionPopupSecond();
		l.w = instance;
		button.addAction(l);
	}
}