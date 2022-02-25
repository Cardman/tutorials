package coq;
import java.util.*;
import org.junit.*;
import static org.junit.Assert.*;

public class SplitTest {

	@Test
	public void s1(){
		Split s = new SplitImpl();
		List<SegmentPart> l = s.dels("text");
		assertEquals(0, l.size());
	}

	@Test
	public void s2(){
		Split s = new SplitImpl();
		List<SegmentPart> l = s.dels("\\\\single comment\n");
		assertEquals(1, l.size());
		assertEquals(0, l.get(0).begin);
		assertEquals(17, l.get(0).end);
		assertEquals(Delimiters.TYPE_SIN_CMT, l.get(0).type);
	}

	@Test
	public void s3(){
		Split s = new SplitImpl();
		List<SegmentPart> l = s.dels("\\*multi\ncomment*\\");
		assertEquals(1, l.size());
		assertEquals(0, l.get(0).begin);
		assertEquals(17, l.get(0).end);
		assertEquals(Delimiters.TYPE_MUL_CMT, l.get(0).type);
	}
	@Test
	public void s4(){
		Split s = new SplitImpl();
		List<SegmentPart> l = s.dels("\\*multi\n*comment*\\");
		assertEquals(1, l.size());
		assertEquals(0, l.get(0).begin);
		assertEquals(18, l.get(0).end);
		assertEquals(Delimiters.TYPE_MUL_CMT, l.get(0).type);
	}
	
	@Test
	public void s5(){
		Split s = new SplitImpl();
		List<SegmentPart> l = s.dels("text\\after");
		assertEquals(0, l.size());
	}

	@Test
	public void s6(){
		Split s = new SplitImpl();
		List<SegmentPart> l = s.dels("\\*multi\ncomment*");
		assertEquals(1, l.size());
		assertEquals(0, l.get(0).begin);
		assertEquals(16, l.get(0).end);
		assertEquals(Delimiters.TYPE_MUL_CMT, l.get(0).type);
	}
	
	@Test
	public void s7(){
		Split s = new SplitImpl();
		List<SegmentPart> l = s.dels("text\\");
		assertEquals(0, l.size());
	}

	@Test
	public void s8(){
		Split s = new SplitImpl();
		List<SegmentPart> l = s.dels("'chars\\'after'");
		assertEquals(1, l.size());
		assertEquals(0, l.get(0).begin);
		assertEquals(14, l.get(0).end);
		assertEquals(Delimiters.TYPE_CHAR, l.get(0).type);
	}

	@Test
	public void s9(){
		Split s = new SplitImpl();
		List<SegmentPart> l = s.dels("\"chars\\\"after\"");
		assertEquals(1, l.size());
		assertEquals(0, l.get(0).begin);
		assertEquals(14, l.get(0).end);
		assertEquals(Delimiters.TYPE_STRING, l.get(0).type);
	}

	@Test
	public void s10(){
		Split s = new SplitImpl();
		List<SegmentPart> l = s.dels("\\\\single comment");
		assertEquals(1, l.size());
		assertEquals(0, l.get(0).begin);
		assertEquals(16, l.get(0).end);
		assertEquals(Delimiters.TYPE_SIN_CMT, l.get(0).type);
	}

	@Test
	public void s11(){
		Split s = new SplitImpl();
		List<SegmentPart> l = s.dels("'chars\\'after");
		assertEquals(1, l.size());
		assertEquals(0, l.get(0).begin);
		assertEquals(13, l.get(0).end);
		assertEquals(Delimiters.TYPE_CHAR, l.get(0).type);
	}

	@Test
	public void s12(){
		Split s = new SplitImpl();
		List<SegmentPart> l = s.dels("\"chars\\\"after");
		assertEquals(1, l.size());
		assertEquals(0, l.get(0).begin);
		assertEquals(13, l.get(0).end);
		assertEquals(Delimiters.TYPE_STRING, l.get(0).type);
	}


	@Test
	public void s13(){
		Split s = new SplitImpl();
		List<SegmentPart> l = s.dels("one'esc\\'ape'two\"esc1\\\"ape2\"three\\\\comment\nfour\\*multi*comment*\\five'char\"char'six\"string'string\"seven");
		assertEquals(6, l.size());
		assertEquals(3, l.get(0).begin);
		assertEquals(13, l.get(0).end);
		assertEquals(Delimiters.TYPE_CHAR, l.get(0).type);
		assertEquals(16, l.get(1).begin);
		assertEquals(28, l.get(1).end);
		assertEquals(Delimiters.TYPE_STRING, l.get(1).type);
		assertEquals(33, l.get(2).begin);
		assertEquals(43, l.get(2).end);
		assertEquals(Delimiters.TYPE_SIN_CMT, l.get(2).type);
		assertEquals(47, l.get(3).begin);
		assertEquals(64, l.get(3).end);
		assertEquals(Delimiters.TYPE_MUL_CMT, l.get(3).type);
		assertEquals(68, l.get(4).begin);
		assertEquals(79, l.get(4).end);
		assertEquals(Delimiters.TYPE_CHAR, l.get(4).type);
		assertEquals(82, l.get(5).begin);
		assertEquals(97, l.get(5).end);
		assertEquals(Delimiters.TYPE_STRING, l.get(5).type);
	}

}