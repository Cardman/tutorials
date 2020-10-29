package mypkg;

public class EcActionResult implements EcAction {
	IntDisplayLabel w;
	IntManagerThread intManager;
	public void act(){
		CustRunnableImpl cr = new CustRunnableImpl();
		cr.res = w;
		intManager.directLaunch(cr);
	}
}