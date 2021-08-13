package com.devglan.userportal;
import java.util.Arrays;
import java.util.List;

public class UserCriteria2 {

    private List<Integer> id=Arrays.asList();

    private List<String> firstName=Arrays.asList();

    private List<String> lastName=Arrays.asList();

    private List<String> email=Arrays.asList();

    public List<Integer> getId() {
        return id;
    }

    public void setId(List<Integer> id) {
        this.id = id;
    }

    public List<String> getFirstName() {
        return firstName;
    }

    public void setFirstName(List<String> firstName) {
        this.firstName = firstName;
    }

    public List<String> getLastName() {
        return lastName;
    }

    public void setLastName(List<String> lastName) {
        this.lastName = lastName;
    }

    public List<String> getEmail() {
        return email;
    }

    public void setEmail(List<String> email) {
        this.email = email;
    }
}
