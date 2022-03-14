package sample;

import pkg.*;
import org.junit.*;
public class MainTest{
	@Test
	public void m(){
		String[] arr = Sample.m();
		Assert.assertSame(arr, MainClass.calledTest(arr));
	}
}