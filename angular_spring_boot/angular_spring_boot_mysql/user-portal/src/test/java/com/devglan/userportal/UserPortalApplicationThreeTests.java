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
@Sql(scripts={"/insert_data_date.sql"})
public class UserPortalApplicationThreeTests {

	@Autowired
	private UserService userService;


	@Test
	public void findByCriteria3() throws Exception {
		UserCriteria criteria = new UserCriteria();
		criteria.setId(1);
		SimpleDateFormat format = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
		criteria.setLast(format.parse("2021-08-13 13:10:11"));
		criteria.setFirstName("test");
		criteria.setLastName("123456");
		criteria.setEmail("@mail.com");
		assertEquals(2,userService.findByCriteria(criteria).size());
		assertEquals(2,userService.findAll().size());
		assertEquals(format.parse("2021-08-13 13:10:11"),userService.findAll().get(0).getLast());
	}
	@Test
	public void update1Test() throws Exception {
        User admin=userService.findById(1);
		SimpleDateFormat format = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
		admin.setLast(format.parse("2021-08-14 13:10:11"));
		userService.update(admin);
        User adminMod=userService.findById(admin.getId());
		assertEquals(format.parse("2021-08-14 13:10:11"),adminMod.getLast());
		assertEquals(2,userService.findAll().size());
	}
}
