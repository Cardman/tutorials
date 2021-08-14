package com.devglan.userportal;

import java.util.List;

public interface UserService {

    User create(User user);
    //User createTwo(User user);

    User delete(int id);

    List<User> findAll();
    List<User> findByCriteria(UserCriteria criteria);
    List<User> findByCriteria(UserCriteria2 criteria);
    List<CountName> groupFirst(Long count);
    List<CountName> groupLast(Long count);

    User findById(int id);

    User update(User user);
	void updateUser(int newId, int oldId);
}
