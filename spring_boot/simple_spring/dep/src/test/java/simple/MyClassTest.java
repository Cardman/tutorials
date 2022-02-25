package simple;

import org.junit.Test;
import static org.junit.Assert.*;

public final class MyClassTest{
	@Test
	public void db(){
		assertEquals(2,MyClass.db(1));
	}
}