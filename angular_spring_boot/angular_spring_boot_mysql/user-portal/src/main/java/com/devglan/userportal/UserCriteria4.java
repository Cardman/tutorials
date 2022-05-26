package com.devglan.userportal;

import java.time.LocalDateTime;
import java.time.ZoneId;
import java.util.Date;
import java.text.SimpleDateFormat;

public class UserCriteria4 {

    private String begin;
    private String end;
    private boolean onlyNull;

    public int getBeginFlag() {
        return flag(getBegin());
    }


    public String getBegin() {
        return begin;
    }

    public Date getBeginConverted() {
        return convert(begin);
    }

    public void setBegin(String begin) {
        this.begin = begin;
    }

    public int getEndFlag() {
        return flag(end);
    }

    public String getEnd() {
        return end;
    }

    public Date getEndConverted() {
        return convert(getEnd());
    }

    public void setEnd(String end) {
        this.end = end;
    }

    public int getOnlyNullFlag(){
        return Boolean.compare(onlyNull,false);
    }

    public void setOnlyNullFlag(boolean onlyNull) {
        this.onlyNull = onlyNull;
    }

    private static Date convert(String value){
        try {
            SimpleDateFormat format = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
            return format.parse(value);
        } catch (Exception e){
            return null;
        }
    }
    private static int flag(String value){
        String val;
        if (value == null){
            val = "";
        } else {
            val = value;
        }
        if (val.trim().isEmpty()){
            return 1;
        }
        return 0;
    }
}
