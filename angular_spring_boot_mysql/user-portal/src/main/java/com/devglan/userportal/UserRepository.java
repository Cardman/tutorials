package com.devglan.userportal;

import org.springframework.data.repository.Repository;
import org.springframework.transaction.annotation.Transactional;
//import org.springframework.data.jpa.repository.Transactional;
import org.springframework.data.jpa.repository.Modifying;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.query.Param;
import java.util.List;

public interface UserRepository extends Repository<User, Integer> {

    @Transactional
    @Modifying
    @Query(value = "delete from User u where u.id =:#{#c.id}")
    void deleteWhere(@Param("c") User user);

    void delete(User user);

    List<User> findAll();

    User findOne(int id);

    @Query(value = "select u from User u where u.id>=:#{#c.id} and u.firstName like %:#{#c.firstName}% and u.lastName like %:#{#c.lastName}% and u.email like %:#{#c.email}%")
    List<User> findByCriteria(@Param("c") UserCriteria criteria);

    @Query(value = "select u from User u where u.id>=:#{#c.id} and u.firstName like %:#{#c.firstName}% and u.lastName like %:#{#c.lastName}% and u.email like %:#{#c.email}% and u.last = :#{#c.last}")
    List<User> findByCriteriaDate(@Param("c") UserCriteria criteria);

    @Query(value = "select u from User u where u.id>=:#{#c.id} and u.firstName like %:#{#c.firstName}% and u.lastName like %:#{#c.lastName}% and u.email like %:#{#c.email}% and u.last between :#{#c.last} and :#{#c.lastPlusOneDay}")
    List<User> findByCriteriaDateRange(@Param("c") UserCriteria criteria);

    @Query(value = "select u from User u where u.id in (:#{#c.id}) and u.firstName in (:#{#c.firstName}) and u.lastName in (:#{#c.lastName}) and u.email in (:#{#c.email})")
    List<User> findByCriteria(@Param("c") UserCriteria2 criteria);

    @Query(value = "select new com.devglan.userportal.CountName(u.firstName,count(u)) from User u group by u.firstName having count(u)>=:#{#c} order by u.firstName asc")
    List<CountName> groupFirst(@Param("c") long count);

    @Query(value = "select new com.devglan.userportal.CountName(u.lastName,count(u)) from User u group by u.lastName having count(u)>=:#{#c}")
    List<CountName> groupLast(@Param("c") long count);

    User save(User user);

    @Transactional
    @Modifying
    @Query(value = "insert into user (first_name,last_name,email) values(:#{#c.firstName},:#{#c.lastName},:#{#c.email})",
            nativeQuery = true)
    void saveTwo(@Param("c") User user);
	
	//@Transactional
    @Modifying
    @Query(value = "UPDATE user u set id =:newId where u.id = :oldId",
            nativeQuery = true)
    void updateUser(@Param("newId") int newId, @Param("oldId") int oldId);

}
