package mp3;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;

import javazoom.jl.decoder.Bitstream;
import javazoom.jl.decoder.BitstreamException;
import javazoom.jl.decoder.Header;
import javazoom.jl.player.advanced.*;
public class SampleMain implements Runnable {
	String fileName;
	public static void main(String...args)throws Exception{
		SampleMain s = new SampleMain();
		s.fileName=args[0];
		System.setProperty("java.awt.headless", "true");
		System.out.println(s.m());
		Thread th = new Thread(s);
		th.start();
		th.join();
	}
	double m() {
		Header h = null;
		FileInputStream file = null;
		try {
			file = new FileInputStream(fileName);
		} catch (FileNotFoundException ex) {
//			Logger.getLogger(MP3.class.getName()).log(Level.SEVERE, null, ex);
			return -1.0;
		}
		Bitstream bitstream = new Bitstream(file);
		try {
			h = bitstream.readFrame();
		} catch (BitstreamException ex) {
//			Logger.getLogger(MP3.class.getName()).log(Level.SEVERE, null, ex);
			return -1.0;
		}
//		int size = h.calculate_framesize();
//		float ms_per_frame = h.ms_per_frame();
//		int maxSize = h.max_number_of_frames(10000);
//		int maxSize = h.max_number_of_frames((int) tn);
//		float t = h.total_ms(size);
		long tn = 0;
		try {
			tn = file.getChannel().size();
		} catch (IOException ex) {
			return -1.0;
//			Logger.getLogger(MP3.class.getName()).log(Level.SEVERE, null, ex);
		}
		System.out.println(tn);
		System.out.println(new java.io.File(fileName).length());
//System.out.println("Chanel: " + file.getChannel().size());
//		int min = h.min_number_of_frames(500);
		System.out.println(100*h.ms_per_frame());
		System.out.println(h.max_number_of_frames((int) tn));
		System.out.println(h.total_ms((int) tn));
		return h.total_ms((int) tn)/1000;
	}
	public void run(){
		try {
			FileInputStream in = new FileInputStream(fileName);
			AdvancedPlayer adv = new AdvancedPlayer(in);
			adv.setPlayBackListener(new PlaybackListener() {
				@Override
				public void playbackFinished(PlaybackEvent event) {
					System.out.println(event.getFrame());
					System.out.println("End");
					//System.exit(0);
				}
			});
			adv.play(100);
			//adv.play(Integer.MAX_VALUE-20210);
			//adv.play(100,Integer.MAX_VALUE);
		} catch(Exception e){
			e.printStackTrace();
		}
	}
}