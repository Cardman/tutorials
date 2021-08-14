package com.devglan.userportal;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.transaction.annotation.Transactional;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class UserServiceImpl implements UserService {

    @Autowired
    private UserRepository repository;

    @Override
    public User createTwo(User user) {
        repository.saveTwo(user);
        return user;
    }

    @Override
    public User create(User user) {
        return repository.save(user);
    }

    @Override
    public User delete(int id) {
        User user = findById(id);
        if(user != null){
            repository.delete(user);
        }
        return user;
    }

    @Override
    public void deleteWhere(User user){
        repository.deleteWhere(user);
    }
    @Override
    public List<User> findAll() {
        return repository.findAll();
    }

    @Override
    public List<User> findByCriteria(UserCriteria criteria) {
        if (criteria.getLast() == null){
            return repository.findByCriteria(criteria);
        }
        return repository.findByCriteriaDateRange(criteria);
    }

    @Override
    public List<User> findByCriteria(UserCriteria2 criteria) {
        return repository.findByCriteria(criteria);
    }

    @Override
    public List<CountName> groupFirst(Long count) {
        return repository.groupFirst(count);
    }

    @Override
    public List<CountName> groupLast(Long count) {
        return repository.groupLast(count);
    }

    @Override
    public User findById(int id) {
        return repository.findOne(id);
    }

    @Override
    public User update(User user) {
		repository.save(user);
        return null;
    }
	@Transactional(readOnly=false)
	public void updateUser(int newId, int oldId){
		repository.updateUser(newId,oldId);
	}

}
