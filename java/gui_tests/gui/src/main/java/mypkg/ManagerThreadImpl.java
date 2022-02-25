package mypkg;

public class ManagerThreadImpl implements IntManagerThread {

    public void directLaunch(CustRunnable _thread){
        AdapterRunnable ar_ = new AdapterRunnable();
        ar_.cr = _thread;
        new Thread(ar_).start();
    }
}