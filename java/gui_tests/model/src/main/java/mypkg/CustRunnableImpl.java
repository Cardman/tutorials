package mypkg;

public class CustRunnableImpl implements CustRunnable {

    IntDisplayLabel res;
    public void work(){
        res.setText("done");
    }
}