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
public class UserPortalApplicationTests {

	@Autowired
	private UserService userService;
	private int idOne;
	private int idTwo;
	@Before
	public void initDb() {
		User newUser = new User();
		newUser.setFirstName("testUser");
		newUser.setLastName("123456");
		newUser.setEmail("testUser@mail.com");
		idOne = userService.create(newUser).getId(); 
		newUser = new User();
		newUser.setFirstName("testAdmin");
		newUser.setLastName("123456");
		newUser.setEmail("testAdmin@mail.com");
		idTwo = userService.create(newUser).getId(); 

    }
	@Test
	public void findById1Test() {
		User user=userService.findById(idOne);
        assertNotNull(user);
	}
	@Test
	public void findById2Test() {
        User admin=userService.findById(idTwo);
        assertEquals(admin.getEmail(),"testAdmin@mail.com");
        assertEquals(admin.getFirstName(),"testAdmin");
        assertEquals(admin.getLastName(),"123456");
	}
	@Test
	public void findAllTest() {
        assertEquals(2,userService.findAll().size());
	}
	@Test
	public void delete1Test() {
        assertEquals(2,userService.findAll().size());
        User admin=userService.delete(idOne);
		assertEquals(1,userService.findAll().size());
        assertEquals(admin.getEmail(),"testUser@mail.com");
	}
	@Test
	public void delete2Test() {
        assertEquals(2,userService.findAll().size());
        User admin=userService.delete(Math.max(idOne,idTwo)+1);
		assertEquals(2,userService.findAll().size());
        assertNull(admin);
	}
	@Test
	public void update1Test() {
        User admin=userService.findById(idTwo);
		admin.setEmail("testAdmin2@mail.com");
		userService.update(admin);
        User adminMod=userService.findById(admin.getId());
		assertEquals(adminMod.getEmail(),"testAdmin2@mail.com");
		assertEquals(2,userService.findAll().size());
	}
	@Test
	public void update2Test() {
        User admin=userService.findById(idTwo);
		admin.setId(3);
		userService.update(admin);
        User adminMod=userService.findById(admin.getId());
		assertEquals(adminMod.getId(),3);
		assertEquals(3,userService.findAll().size());
	}
	@Test
	public void updateIdTest() {
		int newId = Math.max(idTwo,idOne)+1;
        userService.updateUser(newId,idTwo);
		User adminMod=userService.findById(newId);
		assertEquals(adminMod.getId(),newId);
		assertEquals(2,userService.findAll().size());
		User user=userService.findById(idOne);
        assertNotNull(user);
	}
}
