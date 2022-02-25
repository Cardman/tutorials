package com.devglan.userportal;

import java.util.Arrays;
import java.util.List;
import org.junit.Test;
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
import static org.junit.Assert.assertSame;

@RunWith(SpringRunner.class)
@SpringBootTest
@TestPropertySource(locations = "classpath:application-test.properties")
@Sql(scripts={"/drop_schema.sql","/create_schema_sec.sql"})
@Sql(scripts={"/insert_data_auto.sql"})
//@Sql(statements = "ALTER TABLE user AUTO_INCREMENT = 3;")
public class UserPortalApplicationSecTests {

	@Autowired
	private UserService userService;

	@Test
	public void create() {
		User newUser = new User();
		newUser.setFirstName("testAdmin2");
		newUser.setLastName("123456");
		newUser.setEmail("testAdmin2@mail.com");
		userService.create(newUser); 
		assertEquals(3,newUser.getId());
		assertEquals(3,userService.findAll().size());
		//assertSame(res,newUser);
		//assertEquals(3,res.getId());
		/*assertEquals("testAdmin2",res.getFirstName());
		assertEquals("123456",res.getLastName());
		assertEquals("testAdmin2@mail.com",res.getEmail());*/
	}

	@Test
	public void create2() {
		User newUser = new User();
		newUser.setFirstName("testAdmin2");
		newUser.setLastName("123456");
		newUser.setEmail("testAdmin2@mail.com");
		userService.create(newUser); 
		assertEquals(3,newUser.getId());
		newUser = new User();
		newUser.setFirstName("testAdmin3");
		newUser.setLastName("123456");
		newUser.setEmail("testAdmin2@mail.com");
		userService.create(newUser); 
		assertEquals(4,newUser.getId());
		assertEquals(4,userService.findAll().size());
		//assertEquals(3,res.getId());
		/*assertEquals("testAdmin2",res.getFirstName());
		assertEquals("123456",res.getLastName());
		assertEquals("testAdmin2@mail.com",res.getEmail());*/
	}
	
	@Test
	public void findAllTest() {
        assertEquals(2,userService.findAll().size());
	}
	
}
