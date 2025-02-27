package com.devglan.userportal;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequestMapping({"/api"})
public class UserController {

    @Autowired
    private UserService userService;

    @PostMapping
    public User create(@RequestBody User user){
        return userService.create(user);
    }
    public int createTwo(User user) {
        return userService.createTwo(user);
    }
    @GetMapping(path = {"/{id}"})
    public User findOne(@PathVariable("id") int id){
        return userService.findById(id);
    }

    @PutMapping
    public User update(@RequestBody User user){
        return userService.update(user);
    }

    @DeleteMapping(path ={"/{id}"})
    public User delete(@PathVariable("id") int id) {
		return userService.delete(id);
    }
    @PostMapping(path={"/filter"})
    public List<User> findByCriteria(@RequestBody UserCriteria criteria) {
        return userService.findByCriteria(criteria);
    }

    @PostMapping(path={"/filter2"})
    public List<User> findByCriteriaBet(@RequestBody UserCriteria3 criteria) {
        return userService.findByCriteriaBet(criteria);
    }
    @GetMapping
    public List<User> findAll(){
        return userService.findAll();
    }
}
