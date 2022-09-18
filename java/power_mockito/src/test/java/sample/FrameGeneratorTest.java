package sample;

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
@PowerMockIgnore("javax.swing.*")
public final class FrameGeneratorTest{


    @Test
    public void frame() throws Exception {
		PowerMockito.mockStatic(JFrame.class);
		JFrame mock = mock(JFrame.class);
        whenNew(JFrame.class).withNoArguments().thenReturn(mock);
		FrameGenerator frameGene = new FrameGenerator();
		Assert.assertNotNull(frameGene.frame());
    }

}