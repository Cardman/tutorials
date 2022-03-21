package com.devglan.userportal;

import java.util.Date;
import java.text.SimpleDateFormat;
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
@Sql(scripts={"/insert_data_date.sql","/insert_data_date2.sql"})
public class UserPortalApplicationFourTests {

	@Autowired
	private UserController userController;


	@Test
	public void findByCriteriaBet1() {
		assertEquals(8,userController.findByCriteriaBet(new UserCriteria3()).size());
		assertEquals(8,userController.findAll().size());
	}
	@Test
	public void findByCriteriaBet2() throws Exception {
		UserCriteria3 us = new UserCriteria3();
		SimpleDateFormat format = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
		us.setBegin(format.parse("2021-08-14 13:10:11"));
		List<User> u = userController.findByCriteriaBet(us);
		assertEquals(4,u.size());
		assertEquals("2021-08-14 13:10:11",format.format(u.get(0).getLast()));
		assertEquals("2021-08-14 13:10:11",format.format(u.get(1).getLast()));
		assertEquals("2021-08-15 13:10:11",format.format(u.get(2).getLast()));
		assertEquals("2021-08-15 13:10:11",format.format(u.get(3).getLast()));
		assertEquals(8,userController.findAll().size());
	}
	@Test
	public void findByCriteriaBet3() throws Exception {
		UserCriteria3 us = new UserCriteria3();
		SimpleDateFormat format = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
		us.setEnd(format.parse("2021-08-14 13:10:11"));
		List<User> u = userController.findByCriteriaBet(us);
		assertEquals(4,u.size());
		assertEquals("2021-08-13 13:10:11",format.format(u.get(0).getLast()));
		assertEquals("2021-08-13 13:10:11",format.format(u.get(1).getLast()));
		assertEquals("2021-08-14 13:10:11",format.format(u.get(2).getLast()));
		assertEquals("2021-08-14 13:10:11",format.format(u.get(3).getLast()));
		assertEquals(8,userController.findAll().size());
	}
	@Test
	public void findByCriteriaBet4() throws Exception {
		UserCriteria3 us = new UserCriteria3();
		SimpleDateFormat format = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
		us.setBegin(format.parse("2021-08-14 13:10:11"));
		us.setEnd(format.parse("2021-08-14 13:10:11"));
		List<User> u = userController.findByCriteriaBet(us);
		assertEquals(2,u.size());
		assertEquals("2021-08-14 13:10:11",format.format(u.get(0).getLast()));
		assertEquals("2021-08-14 13:10:11",format.format(u.get(1).getLast()));
		assertEquals(8,userController.findAll().size());
	}
	@Test
	public void findByCriteriaBet5() throws Exception {
		UserCriteria3 us = new UserCriteria3();
		SimpleDateFormat format = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
		us.setOnlyNullFlag(true);
		List<User> u = userController.findByCriteriaBet(us);
		assertEquals(2,u.size());
		assertNull(u.get(0).getLast());
		assertNull(u.get(1).getLast());
		assertEquals(8,userController.findAll().size());
	}
}
