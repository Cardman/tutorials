package sample;

import java.awt.*;
import java.awt.image.MemoryImageSource;
import javax.swing.*;
import org.junit.*;
import org.junit.runner.RunWith;
import org.mockito.Mockito;
import org.powermock.core.classloader.annotations.*;
import org.powermock.modules.junit4.PowerMockRunner;

import static org.junit.Assert.assertEquals;
import static org.mockito.Mockito.times;
import static org.mockito.Mockito.verify;
import static org.powermock.api.mockito.PowerMockito.*;
import org.powermock.api.mockito.PowerMockito;

@RunWith(PowerMockRunner.class)
@PowerMockIgnore({"javax.swing.*","java.awt.*","java.awt.image.*"})
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
    public void cursor() throws Exception {
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

}