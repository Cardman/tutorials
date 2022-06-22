package code.mock;

import org.junit.Test;

import static org.junit.Assert.assertEquals;

public class MockZipStreamOutTest {
    @Test
    public void t1() {
        MockZipStreamOut mockZipStreamOut_ = new MockZipStreamOut();
        mockZipStreamOut_.putNextEmptyEntry("a/",1);
        assertEquals(13,mockZipStreamOut_.byteArray().length);
        mockZipStreamOut_.close();
    }
    @Test
    public void t2() {
        MockZipStreamOut mockZipStreamOut_ = new MockZipStreamOut();
        mockZipStreamOut_.putNextEntry("a/",1,new byte[2]);
        assertEquals(15,mockZipStreamOut_.byteArray().length);
        mockZipStreamOut_.close();
    }
}
