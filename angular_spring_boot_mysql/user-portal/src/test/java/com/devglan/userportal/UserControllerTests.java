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
import org.springframework.test.context.jdbc.Sql;
import org.springframework.test.context.TestPropertySource;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.assertNull;

@RunWith(SpringRunner.class)
@SpringBootTest
@TestPropertySource(locations = "classpath:application-test.properties")
@Sql(scripts={"/drop_schema.sql","/create_schema.sql"})
@Sql(scripts={"/insert_data.sql"})
public class UserControllerTests {

	@Autowired
	private UserController userController;
	private int idOne;
	private int idTwo;
	@Before
	public void initDb() {
		idOne = 1; 
		idTwo = 2; 

    }
	@Test
	public void findById1Test() {
		User user=userController.findOne(idOne);
        assertNotNull(user);
		assertEquals(2,userController.findAll().size());
	}
	@Test
	public void findByCriteria() {
		assertEquals(2,userController.findByCriteria(new UserCriteria()).size());
		assertEquals(2,userController.findAll().size());
	}
	@Test
	public void create() {
		User newUser = new User();
		newUser.setId(3);
		newUser.setFirstName("testAdmin2");
		newUser.setLastName("123456");
		newUser.setEmail("testAdmin2@mail.com");
		userController.create(newUser); 
		assertEquals(3,userController.findAll().size());
		assertEquals(3,newUser.getId());
	}
	@Test
	public void findById2Test() {
        User admin=userController.findOne(idTwo);
        assertEquals(admin.getEmail(),"testAdmin@mail.com");
		assertEquals(2,userController.findAll().size());
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
