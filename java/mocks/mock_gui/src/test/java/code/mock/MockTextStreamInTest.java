package code.mock;

import org.junit.Test;

import static org.junit.Assert.assertEquals;

public class MockTextStreamInTest {
    @Test
    public void t1() {
        MockTextStreamIn mockTextStreamIn = new MockTextStreamIn("_");
        assertEquals('_',mockTextStreamIn.read());
    }
    @Test
    public void t2() {
        MockTextStreamIn mockTextStreamIn = new MockTextStreamIn("_-");
        mockTextStreamIn.read();
        assertEquals('-',mockTextStreamIn.read());
    }
    @Test
    public void t3() {
        MockTextStreamIn mockTextStreamIn = new MockTextStreamIn("_-");
        mockTextStreamIn.read();
        mockTextStreamIn.read();
        assertEquals(-1,mockTextStreamIn.read());
        mockTextStreamIn.close();
    }
    @Test
    public void t4() {
        MockTextStreamIn mockTextStreamIn = new MockTextStreamIn(null);
        assertEquals(-2,mockTextStreamIn.read());
    }
}
