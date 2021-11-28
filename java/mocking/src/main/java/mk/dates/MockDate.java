package mk.dates;

import java.util.TimeZone;
import java.text.SimpleDateFormat;

import java.util.Date;

public final class MockDate implements AbsMockDate{
	private final Date date;
	private final TimeZone zone;
	public MockDate(Date date,TimeZone zone){
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

interface AbsMockDate{
	public String format(String _format);
	public long timeZone(long _millis);
}