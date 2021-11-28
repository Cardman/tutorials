package mk.dates;


import java.util.TimeZone;
import java.text.SimpleDateFormat;
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
	public void formatMock(){
		Date date = new Date(-152000);
		TimeZone tz = mock(TimeZone.class);
		MockDateDef mk = new MockDateDef(date,tz);
		mk = spy(mk);
		doReturn(25*3600*1000L).doReturn(25*3600*1000L).doReturn(26*3600*1000L).doReturn(26*3600*1000L).when(mk).timeZone(anyLong());
		assertEquals(25*3600*1000,mk.timeZone(0));
		assertEquals(25*3600*1000,mk.timeZone(1));
		assertEquals(26*3600*1000,mk.timeZone(2));
		assertEquals(26*3600*1000,mk.timeZone(3));
	}

	@Test
	public void timeZone(){
		Date date = mock(Date.class);
		TimeZone tz = TimeZone.getDefault();
		tz = spy(tz);
		doReturn(25*3600*1000).doReturn(25*3600*1000).doReturn(26*3600*1000).doReturn(26*3600*1000).when(tz).getOffset(anyLong());
		MockDate mk = new MockDate(date,tz);
		assertEquals(25*3600*1000,mk.timeZone(0));
		assertEquals(25*3600*1000,mk.timeZone(1));
		assertEquals(26*3600*1000,mk.timeZone(2));
		assertEquals(26*3600*1000,mk.timeZone(3));
	}
}


class MockDateDef implements AbsMockDate{
	private final Date date;
	private final TimeZone zone;
	public MockDateDef(Date date,TimeZone zone){
		this.date = date;
		this.zone = zone;
	}
	public String format(String _format) {
        return new SimpleDateFormat(_format).format(date);
    }
	public long timeZone(long _millis) {
        return zone.getOffset(_millis);
    }
}
