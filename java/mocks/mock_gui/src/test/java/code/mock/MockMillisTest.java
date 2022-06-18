package code.mock;

import org.junit.Test;

import static org.junit.Assert.assertEquals;

public class MockMillisTest {
    @Test
    public void test1() {
        MockMillis mockMillis_ = new MockMillis(10,new long[0]);
        assertEquals(10, mockMillis_.millis());
    }
    @Test
    public void test2() {
        long[] incrs = new long[1];
        incrs[0] = 5;
        MockMillis mockMillis_ = new MockMillis(10, incrs);
        assertEquals(15, mockMillis_.millis());
    }
    @Test
    public void test3() {
        long[] incrs = new long[1];
        incrs[0] = 5;
        MockMillis mockMillis_ = new MockMillis(10, incrs);
        mockMillis_.millis();
        assertEquals(20, mockMillis_.millis());
    }
    @Test
    public void test4() {
        long[] incrs = new long[2];
        incrs[0] = 5;
        incrs[1] = 2;
        MockMillis mockMillis_ = new MockMillis(10, incrs);
        mockMillis_.millis();
        assertEquals(17, mockMillis_.millis());
    }
    @Test
    public void test5() {
        long[] incrs = new long[2];
        incrs[0] = 5;
        incrs[1] = 2;
        MockMillis mockMillis_ = new MockMillis(10, incrs);
        mockMillis_.millis();
        mockMillis_.millis();
        assertEquals(22, mockMillis_.millis());
    }
}
