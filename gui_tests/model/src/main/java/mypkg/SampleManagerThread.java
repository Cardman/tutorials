package mypkg;

public class SampleManagerThread implements IntManagerThread {
    public void directLaunch(CustRunnable _thread){
        _thread.work();
    }
}
