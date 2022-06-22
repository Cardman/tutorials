package code.mock;

import org.junit.Test;

import static org.junit.Assert.*;

public class MockZipStreamInTest {
    @Test
    public void t1() {
        MockZipStreamIn mockZipStreamIn_ = new MockZipStreamIn(new MockZipFact().zipBinFiles(MockZipFact.wrapText(wrap(new MockNameFile("_","---")))));
        assertTrue(mockZipStreamIn_.hasNextEntry());
        assertEquals("_",mockZipStreamIn_.getName());
        assertEquals(0,mockZipStreamIn_.getTime());
        assertEquals(3,mockZipStreamIn_.getSize());
        assertFalse(mockZipStreamIn_.isDirectory());
        assertEquals(2,mockZipStreamIn_.read(new byte[0],0,0));
        assertEquals(1,mockZipStreamIn_.read(new byte[0],0,0));
        assertEquals(0,mockZipStreamIn_.read(new byte[0],0,0));
        byte[] readBytes_ = mockZipStreamIn_.getReadBytes();
        assertEquals(3, readBytes_.length);
        mockZipStreamIn_.closeEntry();
        mockZipStreamIn_.close();
        assertFalse(mockZipStreamIn_.hasNextEntry());
    }
    @Test
    public void t2() {
        MockZipStreamIn mockZipStreamIn_ = new MockZipStreamIn(new MockZipFact().zipBinFiles(MockZipFact.wrapText(wrap(new MockNameFile("_/","---")))));
        assertTrue(mockZipStreamIn_.hasNextEntry());
        assertEquals("_/",mockZipStreamIn_.getName());
        assertEquals(0,mockZipStreamIn_.getTime());
        assertTrue(mockZipStreamIn_.isDirectory());
        mockZipStreamIn_.closeEntry();
        mockZipStreamIn_.close();
    }
    private static MockNameFile[] wrap(MockNameFile... _files) {
        return _files;
    }
}
