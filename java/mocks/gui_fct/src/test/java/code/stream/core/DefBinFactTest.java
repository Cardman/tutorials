package code.stream.core;

import code.expressionlanguage.filenames.DefaultNameValidating;
import code.mock.*;
import code.threads.FileStruct;
import code.util.StringList;
import code.util.StringMap;
import code.util.core.StringUtil;
import org.junit.Test;

import static org.junit.Assert.*;

public class DefBinFactTest {
    @Test
    public void t1() {
        StringMap<FileStruct> f = new StringMap<FileStruct>();
        f.put("abc",new FileStruct(StringUtil.encode("abc"),0));
        assertEquals(3,new DefBinFact(new MockBinFactory(new MockFileSet(f,new DefaultNameValidating(new StringList()),new MockMillis(0,new long[0])))).loadFile("abc").length);
    }
    @Test
    public void t2() {
        assertNull(new DefBinFact(new MockBinFactory(new MockFileSet(new StringMap<FileStruct>(),new DefaultNameValidating(new StringList()),new MockMillis(0,new long[0])))).loadFile("abc"));
    }
    @Test
    public void t3() {
        StringMap<FileStruct> f = new StringMap<FileStruct>();
        new DefBinFact(new MockBinFactory(new MockFileSet(f,new DefaultNameValidating(new StringList()),new MockMillis(0,new long[0])))).writeFile("abc", StringUtil.encode("abc"));
        assertEquals("abc",StringUtil.decode(f.getVal("abc").getContent()));
    }
}
