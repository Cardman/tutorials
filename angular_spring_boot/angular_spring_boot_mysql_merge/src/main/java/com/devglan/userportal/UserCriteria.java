package com.devglan.userportal;

import java.time.LocalDateTime;
import java.time.ZoneId;
import java.util.Date;

public class UserCriteria {

    private int id;

    private String firstName="";

    private String lastName="";

    private String email="";

    private Date last;

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getFirstName() {
        return firstName;
    }

    public void setFirstName(String firstName) {
        this.firstName = firstName;
    }

    public String getLastName() {
        return lastName;
    }

    public void setLastName(String lastName) {
        this.lastName = lastName;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public Date getLast() {
        return last;
    }

    public Date getLastPlusOneDay() {
        //LocalDateTime ldt = LocalDateTime.ofInstant(last.toInstant(), ZoneId.systemDefault()).plusDays(1);
        //return Date.from(ldt.atZone(ZoneId.systemDefault()).toInstant());
        return new Date(last.getTime()+24L*60L*60L*1000L);
        //return Date.from(LocalDateTime.from(last.toInstant()).plusDays(1).toInstant());
    }

    public void setLast(Date last) {
        this.last = last;
    }
}
