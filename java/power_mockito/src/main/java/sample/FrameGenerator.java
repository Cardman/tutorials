package sample;

import java.awt.*;
import java.awt.image.MemoryImageSource;
import javax.swing.*;

public final class FrameGenerator{
    private static final String SELECT = "select";
	public JFrame frame(){
		return new JFrame();
	}
	public Cursor cursor(int _wCurs, int _hCurs, int[] _pixels){
        Toolkit tool_ = Toolkit.getDefaultToolkit();
        Image b_ = tool_.createImage(new MemoryImageSource(_wCurs, _hCurs, _pixels, 0, _wCurs));
        return tool_.createCustomCursor(b_, new Point(0, 0),SELECT);
	}
}