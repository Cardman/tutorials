package mp3;
import java.io.FileInputStream;
import javazoom.jl.player.advanced.*;
public class SampleMain implements Runnable {
	String fileName;
	public static void main(String...args)throws Exception{
		SampleMain s = new SampleMain();
		s.fileName=args[0];
		System.setProperty("java.awt.headless", "true");
		Thread th = new Thread(s);
		th.start();
		th.join();
	}
	public void run(){
		try {
			FileInputStream in = new FileInputStream(fileName);
			AdvancedPlayer adv = new AdvancedPlayer(in);
			adv.setPlayBackListener(new PlaybackListener() {
				@Override
				public void playbackFinished(PlaybackEvent event) {
					event.getFrame();
					System.out.println("End");
					//System.exit(0);
				}
			});
			adv.play();
		} catch(Exception e){
			e.printStackTrace();
		}
	}
}