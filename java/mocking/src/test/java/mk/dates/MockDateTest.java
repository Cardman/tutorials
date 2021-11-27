package mk.dates;


import java.util.TimeZone;

import java.util.Date;

import org.junit.Test;
import static org.mockito.Mockito.*;
import static org.junit.Assert.*;

public class MockDateTest{

	@Test
	public void format(){
		Date date = new Date(-152000);
		TimeZone tz = TimeZone.getDefault();
		date = spy(date);
		doReturn(123456789123456L).when(date).getTime();
		MockDate mk = new MockDate(date,tz);
		assertEquals("58820311_013203",mk.format("yyyyMMdd_hhmmss"));
	}

	@Test
	public void timeZone(){
		Date date = mock(Date.class);
		TimeZone tz = TimeZone.getDefault();
		tz = spy(tz);
		doReturn(25*3600).doReturn(25*3600).doReturn(26*3600).doReturn(26*3600).when(tz).getOffset(anyLong());
		MockDate mk = new MockDate(date,tz);
		assertEquals(25*3600,mk.timeZone(0));
		assertEquals(25*3600,mk.timeZone(1));
		assertEquals(26*3600,mk.timeZone(2));
		assertEquals(26*3600,mk.timeZone(3));
	}
}