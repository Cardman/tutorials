package com.devglan.userportal;

import java.util.List;

public interface UserService {

    User create(User user);
    int createTwo(User user);

    User delete(int id);
    void deleteWhere(User user);

    List<User> findAll();
    List<User> findByCriteriaBet(UserCriteria3 criteria);
    List<User> findByCriteria(UserCriteria criteria);
    List<User> findByCriteria(UserCriteria2 criteria);
    List<CountName> groupFirst(Long count);
    List<CountName> groupLast(Long count);

    User findById(int id);

    User update(User user);
	void updateUser(int newId, int oldId);
}
