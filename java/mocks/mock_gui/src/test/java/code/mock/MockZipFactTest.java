package code.mock;

import code.stream.core.ContentTime;
import code.util.StringMap;
import code.util.core.NumberUtil;
import code.util.core.StringUtil;
import org.junit.Test;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNull;

public class MockZipFactTest {
    @Test
    public void zipBinFiles1() {
        MockZipFact m_ = new MockZipFact();
        byte[] arr_ = m_.zipBinFiles(MockZipFact.wrapText(wrap()));
        assertEquals(8, arr_.length);
    }
    @Test
    public void zipBinFiles2() {
        MockZipFact m_ = new MockZipFact();
        byte[] arr_ = m_.zipBinFiles(MockZipFact.wrapText(wrap(new MockNameFile("_","-"),new MockNameFile("0", NumberUtil.wrapByteArray((byte)'+')))));
        assertEquals(21, arr_.length);
    }
    @Test
    public void zippedBinaryFiles1() {
        MockZipFact m_ = new MockZipFact();
        byte[] arr_ = m_.zipBinFiles(MockZipFact.wrapText(wrap()));
        assertEquals(0, m_.zippedBinaryFiles(arr_).size());
    }
    @Test
    public void zippedBinaryFiles2() {
        MockZipFact m_ = new MockZipFact();
        byte[] arr_ = m_.zipBinFiles(MockZipFact.wrapText(wrap(new MockNameFile("_","-"),new MockNameFile("0", NumberUtil.wrapByteArray((byte)'+')))));
        StringMap<ContentTime> cont_ = m_.zippedBinaryFiles(arr_);
        assertEquals(2, cont_.size());
        assertEquals("-", StringUtil.decode(cont_.getVal("_").getContent()));
        assertEquals("+", StringUtil.decode(cont_.getVal("0").getContent()));
    }
    @Test
    public void zippedBinaryFiles3() {
        MockZipFact m_ = new MockZipFact();
        byte[] arr_ = m_.zipBinFiles(MockZipFact.wrapText(wrap(new MockNameFile("_","-",5),new MockNameFile("0", NumberUtil.wrapByteArray((byte)'+'),7))));
        StringMap<ContentTime> cont_ = m_.zippedBinaryFiles(arr_);
        assertEquals(2, cont_.size());
        assertEquals(5, cont_.getVal("_").getLastModifTime());
        assertEquals(7, cont_.getVal("0").getLastModifTime());
    }
    @Test
    public void zippedBinaryFiles4() {
        MockZipFact m_ = new MockZipFact();
        byte[] arr_ = m_.zipBinFiles(MockZipFact.wrapText(wrap(new MockNameFile("_/",(byte[]) null,5))));
        StringMap<ContentTime> cont_ = m_.zippedBinaryFiles(arr_);
        assertEquals(1, cont_.size());
        assertNull(cont_.getVal("_/").getContent());
    }
    @Test
    public void zippedBinaryFiles5() {
        MockZipFact m_ = new MockZipFact();
        byte[] arr_ = m_.zipBinFiles(MockZipFact.wrapText(wrap(new MockNameFile("_",(byte[]) null,5))));
        StringMap<ContentTime> cont_ = m_.zippedBinaryFiles(arr_);
        assertEquals(1, cont_.size());
        assertNull(cont_.getVal("_/").getContent());
    }
    @Test
    public void zippedBinaryFiles6() {
        MockZipFact m_ = new MockZipFact();
        MockNameFile mockNameFile_ = new MockNameFile("_/", new byte[0], 5);
        mockNameFile_.setMillis(5);
        byte[] arr_ = m_.zipBinFiles(MockZipFact.wrapText(wrap(mockNameFile_)));
        StringMap<ContentTime> cont_ = m_.zippedBinaryFiles(arr_);
        assertEquals(1, cont_.size());
        assertNull(cont_.getVal("_/").getContent());
    }
    @Test
    public void zippedBinaryFiles7() {
        MockZipFact m_ = new MockZipFact();
        StringMap<ContentTime> cont_ = m_.zippedBinaryFiles(wrapInts(80, 75, 3, 4, 13, 49, 47, 47, 13, 48, 13, 47));
        assertEquals(0, cont_.size());
    }
    @Test
    public void zippedBinaryFiles8() {
        MockZipFact m_ = new MockZipFact();
        StringMap<ContentTime> cont_ = m_.zippedBinaryFiles(wrapInts(80, 75, 3, 4, 13, 49, 47, 47, 47, 97, 13, 48, 13, 48, 47));
        assertEquals(0, cont_.size());
    }
    @Test
    public void zippedBinaryFiles9() {
        MockZipFact m_ = new MockZipFact();
        StringMap<ContentTime> cont_ = m_.zippedBinaryFiles(wrapInts(80, 75, 3, 4, 13, 50, 47, 95, 13, 48, 13, 49, 47, 48, 13, 48, 13, 49, 47, 45));
        assertEquals(0, cont_.size());
    }
    @Test
    public void zipBinFiles10() {
        MockZipFact m_ = new MockZipFact();
        StringMap<ContentTime> cont_ = m_.zippedBinaryFiles(wrapInts(80, 75, 3, 4, 13, 50, 47, 95, 13, 48, 13, 49, 47, 48, 13, 48, 13, 34, 47, 45, 43));
        assertEquals(0, cont_.size());
    }
    @Test
    public void zipBinFiles11() {
        MockZipFact m_ = new MockZipFact();
        StringMap<ContentTime> cont_ = m_.zippedBinaryFiles(wrapInts(80, 75, 3, 4, 13, 50, 47, 95, 13, 48, 13, 49, 47, 48, 13, 48, 13, 60, 47, 45, 43));
        assertEquals(0, cont_.size());
    }
    @Test
    public void zipBinFiles12() {
        MockZipFact m_ = new MockZipFact();
        StringMap<ContentTime> cont_ = m_.zippedBinaryFiles(wrapInts(80, 75, 3, 4, 13, 50, 47, 95, 13, 48, 13, 49, 47, 48, 13, 48, 13, 50));
        assertEquals(0, cont_.size());
    }
    @Test
    public void zipBinFiles13() {
        MockZipFact m_ = new MockZipFact();
        StringMap<ContentTime> cont_ = m_.zippedBinaryFiles(wrapInts(80, 75, 3, 4, 13, 50, 47, 95, 13, 47, 13, 49, 47, 48, 13, 48, 13, 49, 47, 45, 43));
        assertEquals(0, cont_.size());
    }
    @Test
    public void zipBinFiles14() {
        MockZipFact m_ = new MockZipFact();
        StringMap<ContentTime> cont_ = m_.zippedBinaryFiles(wrapInts(80, 75, 3, 4, 13, 50, 47, 95, 13, 60, 13, 49, 47, 48, 13, 48, 13, 49, 47, 45, 43));
        assertEquals(0, cont_.size());
    }
    @Test
    public void zipBinFiles15() {
        MockZipFact m_ = new MockZipFact();
        StringMap<ContentTime> cont_ = m_.zippedBinaryFiles(wrapInts(80, 75, 3, 4, 13, 50, 47, 95, 13, 13, 49, 47, 48, 13, 48, 13, 49, 47, 45, 43));
        assertEquals(0, cont_.size());
    }
    @Test
    public void zipBinFiles16() {
        MockZipFact m_ = new MockZipFact();
        StringMap<ContentTime> cont_ = m_.zippedBinaryFiles(wrapInts(80, 75, 3, 4, 13, 50, 47, 95, 13, 48,13, 49, 47, 48, 13, 48, 49, 47, 45, 43));
        assertEquals(0, cont_.size());
    }
    @Test
    public void zipBinFiles17() {
        MockZipFact m_ = new MockZipFact();
        StringMap<ContentTime> cont_ = m_.zippedBinaryFiles(wrapInts(80, 75, 3, 4, 13, 50, 47, 95, 13, 48,13, 49, 47, 48, 48, 49, 47, 45, 43));
        assertEquals(0, cont_.size());
    }
    @Test
    public void zipBinFiles18() {
        MockZipFact m_ = new MockZipFact();
        StringMap<ContentTime> cont_ = m_.zippedBinaryFiles(wrapInts(80, 75, 3, 4, 13, 47, 47, 95, 13, 60, 13, 49, 47, 48, 13, 48, 13, 49, 47, 45, 43));
        assertEquals(0, cont_.size());
    }
    @Test
    public void zipBinFiles19() {
        MockZipFact m_ = new MockZipFact();
        StringMap<ContentTime> cont_ = m_.zippedBinaryFiles(wrapInts(80, 75, 3, 4, 13, 47));
        assertEquals(0, cont_.size());
    }
    @Test
    public void zipBinFiles20() {
        MockZipFact m_ = new MockZipFact();
        StringMap<ContentTime> cont_ = m_.zippedBinaryFiles(wrapInts(80, 75, 3, 4, 13, 46, 47, 95, 13, 60, 13, 49, 47, 48, 13, 48, 13, 49, 47, 45, 43));
        assertEquals(0, cont_.size());
    }
    @Test
    public void zipBinFiles21() {
        MockZipFact m_ = new MockZipFact();
        StringMap<ContentTime> cont_ = m_.zippedBinaryFiles(wrapInts(80, 75, 3, 4, 14));
        assertEquals(0, cont_.size());
    }
    @Test
    public void zipBinFiles22() {
        MockZipFact m_ = new MockZipFact();
        StringMap<ContentTime> cont_ = m_.zippedBinaryFiles(wrapInts(80, 75, 3, 4));
        assertEquals(0, cont_.size());
    }
    @Test
    public void zipBinFiles23() {
        MockZipFact m_ = new MockZipFact();
        StringMap<ContentTime> cont_ = m_.zippedBinaryFiles(wrapInts(80, 75, 3));
        assertEquals(0, cont_.size());
    }
    @Test
    public void zipBinFiles24() {
        MockZipFact m_ = new MockZipFact();
        assertNull(m_.zippedBinaryFiles(null));
    }
    private static byte[] wrapInts(int... _files) {
        return NumberUtil.wrapByteArray(MockZipFact.wrapInts(_files));
    }
    private static MockNameFile[] wrap(MockNameFile... _files) {
        return _files;
    }
}
