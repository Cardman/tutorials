package code.gui;

import code.stream.AbstractFile;
import code.stream.FileListInfo;
import code.stream.core.ContentTime;
import code.stream.core.TechStreams;
import code.threads.FileStruct;
import code.threads.ThState;
import org.junit.Test;

import static org.junit.Assert.*;

public class ThreadsTest {
    @Test
    public void alive1() {
        assertSame(ThState.ALIVE,ThState.of(true));
    }
    @Test
    public void alive2() {
        assertSame(ThState.ENDED,ThState.of(false));
    }
    @Test
    public void file1() {
        FileStruct f_ = new FileStruct(new byte[0],new ThreadFactorySample());
        assertEquals(0,f_.getContent().length);
        assertEquals(0,f_.getLastDate());
    }
    @Test
    public void file2() {
        FileStruct f_ = new FileStruct(new byte[0],0);
        f_.setContent(new byte[0]);
        assertEquals(0,f_.getContent().length);
        assertEquals(0,f_.getLastDate());
    }
    @Test
    public void ls() {
        FileListInfo f_ = new FileListInfo(null);
        assertTrue(f_.isNul());
        assertEquals(0,f_.getNames().length);
    }
    @Test
    public void ls2() {
        FileListInfo f_ = new FileListInfo(new AbstractFile[0]);
        assertFalse(f_.isNul());
        assertEquals(0,f_.getNames().length);
    }
    @Test
    public void ls3() {
        TechStreams t_ = new TechStreams(null,null,null);
        assertNull(t_.getBinFact());
        assertNull(t_.getTextFact());
        assertNull(t_.getZipFact());
    }
    @Test
    public void ls4() {
        ContentTime t_ = new ContentTime(new byte[0],0);
        assertEquals(0, t_.getLastModifTime());
        assertEquals(0, t_.getContent().length);
    }
}
