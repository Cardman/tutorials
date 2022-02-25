package mypkg;

import org.junit.*;
import java.util.*;

public class AddEventsUtilTest {
	@Test
	public void createTest(){
		EcActionCreator eac = new EcActionCreator();
		SampleWindow w = new SampleWindow();
		eac.w=w;
		eac.act();
		Assert.assertEquals(1,w.events.size());
		Assert.assertEquals("added",w.events.get(0));
	}
	@Test
	public void firstTest(){
		EcActionPopupFirst eac = new EcActionPopupFirst();
		SampleWindow w = new SampleWindow();
		eac.w=w;
		eac.act();
		Assert.assertEquals(1,w.events.size());
		Assert.assertEquals("first",w.events.get(0));
	}
	@Test
	public void secondTest(){
		EcActionPopupSecond eac = new EcActionPopupSecond();
		SampleWindow w = new SampleWindow();
		eac.w=w;
		eac.act();
		Assert.assertEquals(1,w.events.size());
		Assert.assertEquals("second",w.events.get(0));
	}
	@Test
	public void createButton1Test(){
		SampleButton s = new SampleButton(AddEventsUtil.createButtonContent(new SampleCheck1(),new AddEventsImpl(),"first","second"));
		Assert.assertEquals("first",s.button);
		Assert.assertNull(s.action);
	}
	@Test
	public void createButton2Test(){
		SampleButton s = new SampleButton(AddEventsUtil.createButtonContent(new SampleCheck2(),new AddEventsImpl(),"first","second"));
		Assert.assertEquals("second",s.button);
		Assert.assertNull(s.action);
	}
	@Test
	public void process1Test(){
		AddEventsImpl add = new AddEventsImpl();
		SampleCheck1 ch = new SampleCheck1();
		SampleButton b = new SampleButton(AddEventsUtil.createButtonContent(ch,add,"first","second"));
		AddEventsUtil.process(b,new SampleWindow(),ch,add);
		Assert.assertEquals("first",b.button);
		Assert.assertTrue(b.action instanceof EcActionPopupFirst);
	}
	@Test
	public void process2Test(){
		AddEventsImpl add = new AddEventsImpl();
		SampleCheck2 ch = new SampleCheck2();
		SampleButton b = new SampleButton(AddEventsUtil.createButtonContent(ch,add,"first","second"));
		AddEventsUtil.process(b,new SampleWindow(),ch,add);
		Assert.assertEquals("second",b.button);
		Assert.assertTrue(b.action instanceof EcActionPopupSecond);
	}
	@Test
	public void thread(){
		IntManagerThread man = new SampleManagerThread();
		CustRunnableImpl i_ = new CustRunnableImpl();
		SampleRes res_ = new SampleRes();
		i_.res = res_;
		CustRunnable th = i_;
		man.directLaunch(th);
		Assert.assertEquals("done",res_.text);
	}
	@Test
	public void changeTitle(){
		IntManagerThread man = new SampleManagerThread();
		CustRunnableImpl i_ = new CustRunnableImpl();
		SampleRes res_ = new SampleRes();
		i_.res = res_;
		EcActionResult ear = new EcActionResult();
		ear.w = res_;
		ear.intManager = man;
		ear.act();
		Assert.assertEquals("done",res_.text);
	}
}

class SampleCheck1 implements IntLabel{
	public boolean isSelected(){
		return true;
	}
}
class SampleCheck2 implements IntLabel{
	public boolean isSelected(){
		return false;
	}
}
class SampleRes implements IntDisplayLabel{
	String text;
	public void setText(String _text){
		text = _text;
	}
}
class SampleButton implements IntButton{
	String button;
	Object action;
	public SampleButton(String label){
		button = label;
	}
	public SampleButton(ButtonContent label){
		button = label.text;
	}
	public void addAction(EcAction act){
		action = act;
	}
}

class SampleWindow implements IntWindow {
	List<String> events = new ArrayList<String>();
	public void addButton(){
		events.add("added");
	}
	public void popupFirst(){
		events.add("first");
	}
	public void popupSecond(){
		events.add("second");
	}
}