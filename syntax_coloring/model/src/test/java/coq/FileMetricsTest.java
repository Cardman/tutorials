package coq;
import java.util.*;
import org.junit.*;
import static org.junit.Assert.*;

public final class FileMetricsTest {

	@Test
	public void r1(){
		FileMetrics m = FileMetricsCore.processLinesTabs("text",4);
		int i = 0;
		assertEquals(1,m.getRowFile(i));
	}
	@Test
	public void r2(){
		FileMetrics m = FileMetricsCore.processLinesTabs("text",4);
		int i = 2;
		assertEquals(1,m.getRowFile(i));
	}
	@Test
	public void r3(){
		FileMetrics m = FileMetricsCore.processLinesTabs("text\nline",4);
		int i = 5;
		assertEquals(2,m.getRowFile(i));
	}
	@Test
	public void r4(){
		FileMetrics m = FileMetricsCore.processLinesTabs("text\nline",4);
		int i = 4;
		assertEquals(1,m.getRowFile(i));
	}
	@Test
	public void r5(){
		FileMetrics m = FileMetricsCore.processLinesTabs("text\n\tline",4);
		int i = 6;
		assertEquals(2,m.getRowFile(i));
	}

	@Test
	public void c1(){
		FileMetrics m = FileMetricsCore.processLinesTabs("text",4);
		int i = 0;
		int r = m.getRowFile(i);
		assertEquals(1,m.getColFile(i,r));
	}
	@Test
	public void c2(){
		FileMetrics m = FileMetricsCore.processLinesTabs("text",4);
		int i = 2;
		int r = m.getRowFile(i);
		assertEquals(3,m.getColFile(i,r));
	}
	@Test
	public void c3(){
		FileMetrics m = FileMetricsCore.processLinesTabs("text\nline",4);
		int i = 5;
		int r = m.getRowFile(i);
		assertEquals(1,m.getColFile(i,r));
	}
	@Test
	public void c4(){
		FileMetrics m = FileMetricsCore.processLinesTabs("text\nline",4);
		int i = 4;
		int r = m.getRowFile(i);
		assertEquals(5,m.getColFile(i,r));
	}
	@Test
	public void c5(){
		FileMetrics m = FileMetricsCore.processLinesTabs("text\n\tline",4);
		int i = 6;
		int r = m.getRowFile(i);
		assertEquals(5,m.getColFile(i,r));
	}


}
