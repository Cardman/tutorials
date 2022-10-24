package sample;

import java.awt.*;
import java.awt.image.MemoryImageSource;
import java.io.*;
import javax.swing.*;

public final class FrameGenerator implements FrameGeneratorInt{
    private static final String SELECT = "select";
	public JFrame frame(){
		return new JFrame();
	}
	public JDialog dialog(){
		return new JDialog();
	}
//	public String readFile(Map<?,?> files, String _fake) throws IOException {
//		return readFile(new BufferedReader(new FileReader((File) files.get(_fake))));
//	}
	public String readFile(BufferedReader _fake) {
		try {
			StringBuilder str_ = new StringBuilder();
			String n_;
			while ((n_ = _fake.readLine()) != null) {
				str_.append(n_);
			}
			return str_.toString();
		} catch (Exception e) {
			return null;
		} finally {
			close(_fake);
		}
	}
	public boolean writeFile(BufferedWriter _fake, String _content) {
		try {
			_fake.write(_content);
			_fake.close();
			return true;
		} catch (Exception e) {
			return false;
		} finally {
			close(_fake);
		}
	}
	public static boolean close(Closeable _cl) {
		try {
			_cl.close();
			return true;
		} catch (Exception e) {
			return false;
		}
	}
	public Cursor cursor(int _wCurs, int _hCurs, int[] _pixels){
        Toolkit tool_ = Toolkit.getDefaultToolkit();
        Image b_ = tool_.createImage(new MemoryImageSource(_wCurs, _hCurs, _pixels, 0, _wCurs));
        return tool_.createCustomCursor(b_, new Point(0, 0),SELECT);
	}

	@Override
	public AbsCompo newCompo() {
		return new Real(lab());
	}
	public JLabel lab() {
		return new JLabel();
	}
}