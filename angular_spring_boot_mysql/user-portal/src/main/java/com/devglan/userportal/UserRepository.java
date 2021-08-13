package com.devglan.userportal;

import org.springframework.data.repository.Repository;
import org.springframework.data.jpa.repository.Modifying;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.query.Param;
import java.util.List;

public interface UserRepository extends Repository<User, Integer> {

    void delete(User user);

    List<User> findAll();

    User findOne(int id);

    @Query(value = "select u from User u where u.id>=:#{#c.id} and u.firstName like %:#{#c.firstName}% and u.lastName like %:#{#c.lastName}% and u.email like %:#{#c.email}%")
    List<User> findByCriteria(@Param("c") UserCriteria criteria);

    User save(User user);
	
	//@Transactional
    @Modifying
    @Query(value = "UPDATE user u set id =:newId where u.id = :oldId",
            nativeQuery = true)
    void updateUser(@Param("newId") int newId, @Param("oldId") int oldId);

}
