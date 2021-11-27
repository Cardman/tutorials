package mk.files;

import java.io.File;
import java.util.TimeZone;

import java.util.Date;

import org.junit.Test;
import static org.mockito.Mockito.*;
import static org.junit.Assert.*;

public class MockFileTest{
	@Test
	public void method(){
		File sample = new File("______________");
		sample = spy(sample);
		MockFile mkfile = new MockFile(sample);
		doReturn(true).when(sample).exists();
		doReturn(true).when(sample).mkdirs();
		doReturn(true).when(sample).isDirectory();
		doReturn(false).when(sample).delete();
		doReturn(true).when(sample).renameTo(any(File.class));
		doReturn(false).when(sample).renameTo(null);
		doReturn(new String[]{"one","two"}).when(sample).list();
		doReturn(-123456789123456789L).when(sample).lastModified();
		doReturn(979999999999999999L).when(sample).length();
		doReturn("PC").when(sample).getParent();
		doReturn("_____").when(sample).getName();
		doReturn("PC:/______________").when(sample).getAbsolutePath();
		assertTrue(mkfile.exists());
		assertTrue(mkfile.mkdirs());
		assertTrue(mkfile.isDirectory());
		assertFalse(mkfile.delete());
		assertTrue(mkfile.renameTo(mkfile));
		assertFalse(mkfile.renameTo(new MockFile(null)));
		assertEquals(2, mkfile.list().length);
		assertEquals(-123456789123456789L, mkfile.lastModified());
		assertEquals(979999999999999999L, mkfile.length());
		assertEquals("PC", mkfile.getParent());
		assertEquals("PC:/______________", mkfile.getAbsolutePath());
		assertEquals("_____", mkfile.getName());
	}
}