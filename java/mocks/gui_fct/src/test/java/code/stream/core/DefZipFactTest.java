package code.stream.core;

import code.mock.MockNameFile;
import code.mock.MockZipFact;
import code.util.StringMap;
import code.util.core.StringUtil;
import org.junit.Test;

import static org.junit.Assert.*;

public class DefZipFactTest {
    @Test
    public void t1() {
        DefZipFact defZipFact_ = new DefZipFact(new MockZipFactory());
        StringMap<ContentTime> res_ = defZipFact_.zippedBinaryFiles(defZipFact_.zipBinFiles(MockZipFact.wrapText(wrap(new MockNameFile("1/",(byte[]) null,4),new MockNameFile("_", "___",5), new MockNameFile("0", "__",7)))));
        assertEquals(3,res_.size());
        assertEquals("",StringUtil.decode(res_.getVal("1/").getContent()));
        assertEquals(4, res_.getVal("1/").getLastModifTime());
        assertEquals("___", StringUtil.decode(res_.getVal("_").getContent()));
        assertEquals(5, res_.getVal("_").getLastModifTime());
        assertEquals("__", StringUtil.decode(res_.getVal("0").getContent()));
        assertEquals(7, res_.getVal("0").getLastModifTime());
    }
    @Test
    public void t2() {
        DefZipFact defZipFact_ = new DefZipFact(new MockZipFactory());
        StringMap<ContentTime> res_ = defZipFact_.zippedBinaryFiles(defZipFact_.zipBinFiles(MockZipFact.wrapText(wrap(new MockNameFile("1",(byte[]) null,4),new MockNameFile("_", "___",5), new MockNameFile("0", "__",7)))));
        assertEquals(3,res_.size());
        assertEquals("",StringUtil.decode(res_.getVal("1/").getContent()));
        assertEquals(4, res_.getVal("1/").getLastModifTime());
        assertEquals("___", StringUtil.decode(res_.getVal("_").getContent()));
        assertEquals(5, res_.getVal("_").getLastModifTime());
        assertEquals("__", StringUtil.decode(res_.getVal("0").getContent()));
        assertEquals(7, res_.getVal("0").getLastModifTime());
    }
    @Test
    public void t3() {
        DefZipFact defZipFact_ = new DefZipFact(new MockZipFactory());
        StringMap<ContentTime> res_ = defZipFact_.zippedBinaryFiles(defZipFact_.zipBinFiles(MockZipFact.wrapText(wrap(new MockNameFile("1/",new byte[0],4),new MockNameFile("_", "___",5), new MockNameFile("0", "__",7)))));
        assertEquals(3,res_.size());
        assertEquals("",StringUtil.decode(res_.getVal("1/").getContent()));
        assertEquals(4, res_.getVal("1/").getLastModifTime());
        assertEquals("___", StringUtil.decode(res_.getVal("_").getContent()));
        assertEquals(5, res_.getVal("_").getLastModifTime());
        assertEquals("__", StringUtil.decode(res_.getVal("0").getContent()));
        assertEquals(7, res_.getVal("0").getLastModifTime());
    }
    @Test
    public void t4() {
        AbstractZipFact defZipFact_ = new DefZipFact(new MockZipFactory());
        StringMap<ContentTime> res_ = defZipFact_.zippedBinaryFiles(null);
        assertNull(res_);
    }
    private static MockNameFile[] wrap(MockNameFile... _files) {
        return _files;
    }
}
