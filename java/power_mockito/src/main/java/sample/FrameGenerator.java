package sample;

import javazoom.jl.decoder.*;
import javazoom.jl.player.advanced.*;

import java.awt.*;
import java.awt.image.MemoryImageSource;
import java.io.*;
import javax.sound.sampled.*;
import javax.swing.*;

public final class FrameGenerator implements FrameGeneratorInt{
    private static final String SELECT = "select";
	private final AbstractThreadFactory fact;
	public FrameGenerator() {
		this(new DefThreadFactory());
	}
	public FrameGenerator(AbstractThreadFactory th) {
		fact = th;
	}

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

	@Override
	public ClStream openClip(byte[] _file) {
		ByteArrayInputStream bis_ = new ByteArrayInputStream(_file);
		return openClip(bis_);
	}

	public ClStream openClip(InputStream _file) {
		try {
			AudioInputStream audioIn_ = AudioSystem.getAudioInputStream(_file);
			Clip clip_ = AudioSystem.getClip();
			clip_.open(audioIn_);
			return new ClImpl(clip_,audioIn_);
		} catch (Exception e) {
			return null;
		}
	}
	@Override
	public ClStream openMp3(byte[] _file) {
		ByteArrayInputStream bis_ = new ByteArrayInputStream(_file);
		try {
			Bitstream bitstream_ = bitStream(bis_);
			Header header_ = bitstream_.readFrame();
			double millis_ = header_.total_ms(_file.length);
			long ratio_ = (long) header_.ms_per_frame();
			long micros_ = (long)millis_;
			micros_ *= 1000;
			AdvancedPlayer player_ = ClMp3Impl.player(_file);
			return ret(micros_,ratio_, player_,_file);
		} catch (Exception e) {
			return null;
		}
	}

	Bitstream bitStream(InputStream _bis) {
		return new Bitstream(_bis);
	}

	private ClMp3Impl ret(long _micros, long _ratio, AdvancedPlayer _pl, byte[] _bytes) {
		close(_pl);
		return new ClMp3Impl(_bytes, fact, _micros,_ratio);
	}

	private void close(AdvancedPlayer _pl) {
		_pl.close();
	}

	public JLabel lab() {
		return new JLabel();
	}
}