package com.devglan.userportal;

import java.time.LocalDateTime;
import java.time.ZoneId;
import java.util.Date;

public class UserCriteria3 {

    private Date begin;
    private Date end;
    private boolean onlyNull;

    public int getBeginFlag() {
        return flag(begin);
    }


    public Date getBegin() {
        return begin;
    }

    public void setBegin(Date begin) {
        this.begin = begin;
    }

    public int getEndFlag() {
        return flag(end);
    }

    public Date getEnd() {
        return end;
    }

    public void setEnd(Date end) {
        this.end = end;
    }

    public int getOnlyNullFlag(){
        return Boolean.compare(onlyNull,false);
    }

    public void setOnlyNullFlag(boolean onlyNull) {
        this.onlyNull = onlyNull;
    }

    private static int flag(Date value){
        if (value == null){
            return 1;
        }
        return 0;
    }
}
