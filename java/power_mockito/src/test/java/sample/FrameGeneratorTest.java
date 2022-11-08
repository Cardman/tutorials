package sample;

import java.awt.*;
import java.awt.image.MemoryImageSource;
import java.io.*;
import javax.sound.sampled.*;
import javax.swing.*;
import org.junit.*;
import org.junit.runner.RunWith;
import org.mockito.Mockito;
import org.powermock.core.classloader.annotations.*;
import org.powermock.modules.junit4.PowerMockRunner;

import static org.junit.Assert.*;
import static org.mockito.ArgumentMatchers.any;
import static org.mockito.ArgumentMatchers.eq;
import static org.mockito.Mockito.verify;
import static org.powermock.api.mockito.PowerMockito.*;

import org.powermock.api.mockito.PowerMockito;

@RunWith(PowerMockRunner.class)
@PrepareForTest({ AudioSystem.class})
@PowerMockIgnore({"javax.swing.*","java.awt.*","java.awt.image.*","javax.sound.sampled.*"})
public final class FrameGeneratorTest{


    @Test
    public void frame() throws Exception {
		PowerMockito.mockStatic(JFrame.class);
		JFrame mock = mock(JFrame.class);
        whenNew(JFrame.class).withNoArguments().thenReturn(mock);
		FrameGenerator frameGene = new FrameGenerator();
		Assert.assertNotNull(frameGene.frame());
    }

	@Test
	public void dialog() throws Exception {
		PowerMockito.mockStatic(JDialog.class);
		JDialog mock = mock(JDialog.class);
		whenNew(JDialog.class).withNoArguments().thenReturn(mock);
		FrameGenerator frameGene = new FrameGenerator();
		Assert.assertNotNull(frameGene.dialog());
	}
    @Test
    public void cursor1() throws Exception {
		PowerMockito.mockStatic(Toolkit.class);
		MemoryImageSource mockMemoryImageSource = mock(MemoryImageSource.class);
		Toolkit mock = mock(Toolkit.class);
		//
		//whenNew(MemoryImageSource.class).withNoArguments().thenReturn(mockMemoryImageSource);
		whenNew(MemoryImageSource.class).withAnyArguments().thenReturn(mockMemoryImageSource);
		when(Toolkit.getDefaultToolkit()).thenReturn(mock);
		doReturn(mock(Image.class)).when(mock).createImage(Mockito.any(MemoryImageSource.class));
		doReturn(mock(Cursor.class)).when(mock).createCustomCursor((Image)Mockito.any(),(Point)Mockito.any(),(String)Mockito.any());
        FrameGenerator frameGene = new FrameGenerator();
		Assert.assertNotNull(frameGene.cursor(0,0,new int[0]));
    }
	@Test
	public void cursor2() throws Exception {
		PowerMockito.mockStatic(Toolkit.class);
		MemoryImageSource mockMemoryImageSource = mock(MemoryImageSource.class);
		Toolkit mock = mock(Toolkit.class);
		//
		//whenNew(MemoryImageSource.class).withNoArguments().thenReturn(mockMemoryImageSource);
		int[] arr = new int[0];
		whenNew(MemoryImageSource.class).withArguments(0,0,arr,0,0).thenReturn(mockMemoryImageSource);
		when(Toolkit.getDefaultToolkit()).thenReturn(mock);
		doReturn(mock(Image.class)).when(mock).createImage(Mockito.any(MemoryImageSource.class));
		doReturn(mock(Cursor.class)).when(mock).createCustomCursor((Image)Mockito.any(),(Point)Mockito.any(),(String)Mockito.any());
		FrameGenerator frameGene = new FrameGenerator();
		Assert.assertNotNull(frameGene.cursor(0,0, arr));
	}
	@Test
	public void read1() throws Exception {
		BufferedReader bufferedReader = mock(BufferedReader.class);
		doReturn("HELLO").doReturn(" ").doReturn("WORLD").doReturn(null).when(bufferedReader).readLine();
		doNothing().when(bufferedReader).close();
		FrameGenerator frameGene = new FrameGenerator();
		Assert.assertEquals("HELLO WORLD",frameGene.readFile(bufferedReader));
	}

	@Test
	public void read2() throws Exception {
		BufferedReader bufferedReader = mock(BufferedReader.class);
		doThrow(new SomeException()).when(bufferedReader).readLine();
		doNothing().when(bufferedReader).close();
		FrameGenerator frameGene = new FrameGenerator();
		Assert.assertNull(frameGene.readFile(bufferedReader));
	}
//
//	@Test
//	public void read3() throws Exception {
//		Map<?,?> files = Mockito.mock(ConcurrentHashMap.class);
//		File file = Mockito.mock(File.class);
////		Mockito.when(files.get("__")).thenReturn(file);
//		doReturn(file).when(files).get(eq("__"));
//		FileReader fileReader = Mockito.mock(FileReader.class);
//		BufferedReader bufferedReader = Mockito.mock(BufferedReader.class);
//		PowerMockito.whenNew(FileReader.class).withArguments(file).thenReturn(fileReader);
//		PowerMockito.whenNew(BufferedReader.class).withArguments(fileReader).thenReturn(bufferedReader);
//		doReturn("HELLO").doReturn(" ").doReturn("WORLD").doReturn(null).when(bufferedReader).readLine();
//		doNothing().when(bufferedReader).close();
//		FrameGenerator frameGene = new FrameGenerator();
//		Assert.assertEquals("HELLO WORLD",frameGene.readFile(files,"__"));
//	}
	@Test
	public void write1() throws Exception {
		BufferedWriter bufferedReader = mock(BufferedWriter.class);
		doNothing().when(bufferedReader).write(eq(""));
		doNothing().when(bufferedReader).close();
		FrameGenerator frameGene = new FrameGenerator();
		Assert.assertTrue(frameGene.writeFile(bufferedReader,""));
	}

	@Test
	public void write2() throws Exception {
		BufferedWriter bufferedReader = mock(BufferedWriter.class);
		doThrow(new SomeException()).when(bufferedReader).write(eq(""));
		doNothing().when(bufferedReader).close();
		FrameGenerator frameGene = new FrameGenerator();
		Assert.assertFalse(frameGene.writeFile(bufferedReader,""));
	}
	@Test
	public void close1() throws Exception {
		Closeable bufferedReader = mock(Closeable.class);
		doNothing().when(bufferedReader).close();
		Assert.assertTrue(FrameGenerator.close(bufferedReader));
	}

	@Test
	public void close2() throws Exception {
		Closeable bufferedReader = mock(Closeable.class);
		doThrow(new SomeException()).when(bufferedReader).close();
		Assert.assertFalse(FrameGenerator.close(bufferedReader));
	}

	@Test
	public void act1() throws Exception {
		PowerMockito.mockStatic(JLabel.class);
		JLabel mock = mock(JLabel.class);
		whenNew(JLabel.class).withAnyArguments().thenReturn(mock);
//		whenNew(JLabel.class).withNoArguments().thenReturn(mock);
		FrameGenerator frameGene = new FrameGenerator();
		AbsCompo absCompo = frameGene.newCompo();
		Mocked m = new Mocked();
		m.setValue("_");
		doAnswer(new AnswerGetValue(m)).when(spy(((Real)absCompo).getLabel())).getText();
		absCompo.setValue("_");
		Assert.assertEquals("_",absCompo.getValue());
	}
	@Test
	public void act2() throws Exception {
		PowerMockito.mockStatic(JLabel.class);
		JLabel mock = mock(JLabel.class);
		whenNew(JLabel.class).withNoArguments().thenReturn(mock);
		FrameGenerator frameGene = new FrameGenerator();
		AbsCompo absCompo = spy(frameGene.newCompo());
		Mocked m = new Mocked();
		AnswerSetValue ans = new AnswerSetValue(m);
		doAnswer(ans).when(absCompo).setValue((String) any());
//		doAnswer(new AnswerSetValue(m)).when(mock(JLabel.class)).setText((String) any());
//		doAnswer(new AnswerSetValue(m)).when(spy(((Real)absCompo).getLabel())).setText((String) any());
		absCompo.setValue("_");
		Assert.assertEquals("_",m.getValue());
		Assert.assertEquals("_",ans.getAns());
	}
	@Test
	public void addLineListener1() throws Exception {
		PowerMockito.mockStatic(AudioSystem.class);
		Clip cl_ = mock(Clip.class);
		AudioInputStream ais_ = mock(AudioInputStream.class);
		when(AudioSystem.getAudioInputStream(any(InputStream.class))).thenReturn(ais_);
		when(AudioSystem.getClip()).thenReturn(cl_);
		doNothing().when(cl_).open(ais_);
		doNothing().when(cl_).start();
		doNothing().when(cl_).addLineListener((LineListener) any());
		FrameGenerator frameGene = new FrameGenerator();
		ClStream clp_ = frameGene.openClip(new byte[0]);
		assertNotNull(clp_);
		SoundList sl_ = mock(SoundList.class);
		clp_.addLineListener(sl_);
		clp_.resume();
		clp_.stop(0);
		clp_.closeClipStream();
		clp_.getMicrosecondLength();
		clp_.isRunning();
		LineEvent l_ = mock(LineEvent.class);
		whenNew(LineEvent.class).withAnyArguments().thenReturn(l_);
		doReturn(mock(LineEvent.Type.class)).when(l_).getType();
		new Speak(sl_).update(l_);
	}
	@Test
	public void addLineListener2() throws Exception {
		PowerMockito.mockStatic(AudioSystem.class);
		Clip cl_ = mock(Clip.class);
		AudioInputStream ais_ = mock(AudioInputStream.class);
		when(AudioSystem.getAudioInputStream(any(InputStream.class))).thenReturn(ais_);
		when(AudioSystem.getClip()).thenReturn(cl_);
		doThrow(new SomeException()).when(cl_).open(ais_);
		doNothing().when(cl_).start();
		doNothing().when(cl_).addLineListener((LineListener) any());
		FrameGenerator frameGene = new FrameGenerator();
		ClStream clp_ = frameGene.openClip(new byte[0]);
		assertNull(clp_);
	}
}

class SomeException extends RuntimeException{

}