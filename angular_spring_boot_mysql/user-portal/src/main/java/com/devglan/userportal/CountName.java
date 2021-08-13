package com.devglan.userportal;

public class CountName {

    private long count=0L;

    private String name="";

    public CountName(){
    }
    public CountName(String name, long count){
        setName(name);
        setCount(count);
    }
    public long getCount() {
        return count;
    }

    public void setCount(long count) {
        this.count = count;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

}
