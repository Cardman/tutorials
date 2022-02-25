package code;

public final class ProdBean implements IntBean {
    public int oper(int a, int b){
        return a * b;
    }

    @Override
    public int oper(int a) {
        return a*2;
    }
}