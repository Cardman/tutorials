package mypkg;

public class AdapterRunnable implements Runnable {

    CustRunnable cr;

    public void run() {
        cr.work();
    }
}