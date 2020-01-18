package com.devglan.userportal;

import org.junit.Before;
import org.junit.Test;
import org.junit.After;
import org.junit.runner.RunWith;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.context.junit4.SpringRunner;
import org.springframework.beans.factory.annotation.Autowired;

import org.springframework.test.annotation.DirtiesContext;
import org.springframework.test.annotation.DirtiesContext.ClassMode;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.assertNull;

@RunWith(SpringRunner.class)
@SpringBootTest
@DirtiesContext(classMode = ClassMode.AFTER_EACH_TEST_METHOD)
public class UserControllerTests {

	@Autowired
	private UserController userController;
	private int idOne;
	private int idTwo;
	@Before
	public void initDb() {
		User newUser = new User();
		newUser.setFirstName("testUser");
		newUser.setLastName("123456");
		newUser.setEmail("testUser@mail.com");
		idOne = userController.create(newUser).getId(); 
		newUser = new User();
		newUser.setFirstName("testAdmin");
		newUser.setLastName("123456");
		newUser.setEmail("testAdmin@mail.com");
		idTwo = userController.create(newUser).getId(); 

    }
	@Test
	public void findById1Test() {
		User user=userController.findOne(idOne);
        assertNotNull(user);
	}
	@Test
	public void findById2Test() {
        User admin=userController.findOne(idTwo);
        assertEquals(admin.getEmail(),"testAdmin@mail.com");
	}
	@Test
	public void findAllTest() {
        assertEquals(2,userController.findAll().size());
	}
	@Test
	public void delete1Test() {
        assertEquals(2,userController.findAll().size());
        User admin=userController.delete(idOne);
		assertEquals(1,userController.findAll().size());
        assertEquals(admin.getEmail(),"testUser@mail.com");
	}
	@Test
	public void delete2Test() {
        assertEquals(2,userController.findAll().size());
        User admin=userController.delete(Math.max(idOne,idTwo)+1);
		assertEquals(2,userController.findAll().size());
        assertNull(admin);
	}
	@Test
	public void update1Test() {
        User admin=userController.findOne(idTwo);
		admin.setEmail("testAdmin2@mail.com");
		userController.update(admin);
        User adminMod=userController.findOne(admin.getId());
		assertEquals(adminMod.getEmail(),"testAdmin2@mail.com");
		assertEquals(2,userController.findAll().size());
	}
}
