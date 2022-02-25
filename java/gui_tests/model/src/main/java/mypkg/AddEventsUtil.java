package mypkg;

public class AddEventsUtil {
	private AddEventsUtil(){}

	static ButtonContent createButtonContent(IntLabel check,AddEvents adds, String first,String second){
		if (check.isSelected()){
			return adds.createButtonContent(first);
		} else {
			return adds.createButtonContent(second);
		}
	}
	static void process(IntButton button,IntWindow instance, IntLabel check,AddEvents adds){
		if (check.isSelected()){
			adds.addFirst(instance,button);
		} else {
			adds.addSecond(instance,button);
		}
	}
}