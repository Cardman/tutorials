package com.devglan.userportal;

import javax.persistence.*;
import java.util.Date;

@Entity
@Table(name = "user")
public class User {

    @Id
    @Column
    @GeneratedValue//(strategy = GenerationType.IDENTITY)
    private int id;
    @Column
    private String firstName;
    @Column
    private String lastName;
    @Column
    private String email;
    @Column(name="last_modif")
    @Temporal(TemporalType.TIMESTAMP)
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

    public void setLast(Date last) {
        this.last = last;
    }
}
