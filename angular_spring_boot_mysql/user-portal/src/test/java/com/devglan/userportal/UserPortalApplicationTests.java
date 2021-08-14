package com.devglan.userportal;

import java.util.Arrays;
import java.util.List;
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
public class UserPortalApplicationTests {

	@Autowired
	private UserService userService;
	private int idOne;
	private int idTwo;
	@Before
	public void initDb() {
		idOne = 1; 
		idTwo = 2; 

    }
	@Test
	public void create() {
		User newUser = new User();
		newUser.setId(3);
		newUser.setFirstName("testAdmin2");
		newUser.setLastName("123456");
		newUser.setEmail("testAdmin2@mail.com");
		userService.create(newUser); 
		assertEquals(3,userService.findAll().size());
		assertEquals(3,newUser.getId());
	}
	@Test
	public void findByCriteria() {
		assertEquals(2,userService.findByCriteria(new UserCriteria()).size());
		assertEquals(2,userService.findAll().size());
	}
	@Test
	public void findByCriteria3() {
		UserCriteria criteria = new UserCriteria();
		criteria.setId(1);
		criteria.setFirstName("test");
		criteria.setLastName("123456");
		criteria.setEmail("@mail.com");
		assertEquals(2,userService.findByCriteria(criteria).size());
		assertEquals(2,userService.findAll().size());
	}
	@Test
	public void findByCriteria2() {
		UserCriteria2 cr = new UserCriteria2();
		cr.setId(Arrays.asList(1,2));
		cr.setFirstName(Arrays.asList("testAdmin","testUser"));
		cr.setLastName(Arrays.asList("123456"));
		cr.setEmail(Arrays.asList("testAdmin@mail.com","testUser@mail.com"));
		assertEquals(2,userService.findByCriteria(cr).size());
		assertEquals(2,userService.findAll().size());
	}
	@Test
	public void groupFirst() {
		List<CountName> counts = userService.groupFirst(0L);
		assertEquals(2,counts.size());
		assertEquals(1L,(long)counts.get(0).getCount());
		assertEquals("testAdmin",counts.get(0).getName());
		assertEquals(1L,(long)counts.get(1).getCount());
		assertEquals("testUser",counts.get(1).getName());
		assertEquals(2,userService.groupFirst(1L).size());
		assertEquals(0,userService.groupFirst(2L).size());
	}
	@Test
	public void groupLast() {
		List<CountName> counts = userService.groupLast(0L);
		assertEquals(1,counts.size());
		assertEquals(2L,(long)counts.get(0).getCount());
		assertEquals("123456",counts.get(0).getName());
		assertEquals(1,userService.groupLast(1L).size());
		assertEquals(1,userService.groupLast(2L).size());
		assertEquals(0,userService.groupLast(3L).size());
	}
	@Test
	public void findById1Test() {
		User user=userService.findById(idOne);
        assertNotNull(user);
		assertEquals(2,userService.findAll().size());
	}
	@Test
	public void findById2Test() {
        User admin=userService.findById(idTwo);
        assertEquals(admin.getEmail(),"testAdmin@mail.com");
        assertEquals(admin.getFirstName(),"testAdmin");
        assertEquals(admin.getLastName(),"123456");
		assertEquals(2,userService.findAll().size());
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
