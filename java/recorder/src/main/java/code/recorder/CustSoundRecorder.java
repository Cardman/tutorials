package code.recorder;

import javax.sound.sampled.*;
import java.io.*;
import javax.swing.*;
import java.awt.Component;
import java.awt.event.*;
import javax.swing.event.*;
 
/**
 * A sample program is to demonstrate how to record sound in Java
 * author: www.codejava.net
 */
public class CustSoundRecorder {
    // record duration, in milliseconds
    static final long RECORD_TIME = 60000;  // 1 minute
 
    // path of the wav file
    //File wavFile = new File("E:/Test/RecordAudio.wav");
 
    // format of audio file
    AudioFileFormat.Type fileType = AudioFileFormat.Type.WAVE;
 
    // the line from which audio data is captured
    TargetDataLine line;
 
    /**
     * Defines an audio format
     */
    AudioFormat getAudioFormat() {
        float sampleRate = 16000;
        int sampleSizeInBits = 8;
        int channels = 2;
        boolean signed = true;
        boolean bigEndian = true;
        AudioFormat format = new AudioFormat(sampleRate, sampleSizeInBits,
                                             channels, signed, bigEndian);
        return format;
    }
 
    /**
     * Captures the sound and record into a WAV file
     */
    int startRecord(String file, AudioFormat format, DataLine.Info info) {
        try {
            line = (TargetDataLine) AudioSystem.getLine(info);
            line.open(format);
            line.start();
            // start capturing
 
            System.out.println("Start capturing...");
 
            AudioInputStream ais = new AudioInputStream(line);
 
            System.out.println("Start recording...");
 
            // start recording
            AudioSystem.write(ais, fileType, new File(file));
            return 1;
        } catch (Exception ioe) {
            ioe.printStackTrace();
            return 0;
        }
    }
 
    /**
     * Closes the target data line to finish capturing and recording
     */
    void finish() {
        line.stop();
        line.close();
        System.out.println("Finished");
    }
 
    /**
     * Entry to run the program
     */
    public static void main(String[] args)throws Exception {
		SwingUtilities.invokeLater(new GrRecorderTache());
    }
	private static class GrRecorderTache implements Runnable{
		JSlider rate;
		JSlider size;
		JSlider channel;
		JCheckBox signed;
		JCheckBox bigEndian;
		JTextField fileSave;
		JButton recordSong;
		JButton stopSong;
		AudioFormat currentFormat;
		TargetDataLine currentLine;
		DataLine.Info currentInfo;
		JLabel status = new JLabel();
		AudioFileFormat.Type fileType = AudioFileFormat.Type.WAVE;
		JFrame frame;
		JPanel container;
		public void run(){
			frame = new JFrame("Recorder");
			container = new JPanel();
			container.setLayout(new BoxLayout(container,BoxLayout.PAGE_AXIS));
			JPanel group = new JPanel();
			alignTopLeft(group);
			group.setLayout(new BoxLayout(group,BoxLayout.LINE_AXIS));
			JPanel labels = new JPanel();
			labels.setLayout(new BoxLayout(labels,BoxLayout.PAGE_AXIS));
			alignTopLeft(labels);
			JPanel inputs = new JPanel();
			inputs.setLayout(new BoxLayout(inputs,BoxLayout.PAGE_AXIS));
			alignTopLeft(inputs);
			group.add(labels);
			group.add(inputs);
			alignAddedTopLeft(labels,new JLabel("rate"));
			rate = new JSlider(8000,32000,16000);
			rate.addChangeListener(new ChangeListener(){
				public void stateChanged(ChangeEvent e) {
					setState();
				}
			});
			alignTopLeft(rate);
			inputs.add(rate);
			alignAddedTopLeft(labels,new JLabel("size"));
			size = new JSlider(1,32,8);
			size.addChangeListener(new ChangeListener(){
				public void stateChanged(ChangeEvent e) {
					setState();
				}
			});
			alignTopLeft(size);
			inputs.add(size);
			alignAddedTopLeft(labels,new JLabel("channels"));
			channel = new JSlider(1,8,2);
			channel.addChangeListener(new ChangeListener(){
				public void stateChanged(ChangeEvent e) {
					setState();
				}
			});
			alignTopLeft(channel);
			inputs.add(channel);
			alignAddedTopLeft(labels,new JLabel("signed"));
			signed = new JCheckBox();
			signed.setSelected(true);
			signed.addActionListener(new ActionListener(){
				public void actionPerformed(ActionEvent a){
					setState();
				}
			});
			alignTopLeft(signed);
			inputs.add(signed);
			alignAddedTopLeft(labels,new JLabel("big endian"));
			bigEndian = new JCheckBox();
			bigEndian.setSelected(true);
			bigEndian.addActionListener(new ActionListener(){
				public void actionPerformed(ActionEvent a){
					setState();
				}
			});
			alignTopLeft(bigEndian);
			inputs.add(bigEndian);
			alignAddedTopLeft(labels,new JLabel("file save"));
			fileSave = new JTextField();
			alignTopLeft(fileSave);
			inputs.add(fileSave);
			JPanel buttons = new JPanel();
			buttons.setLayout(new BoxLayout(buttons,BoxLayout.LINE_AXIS));
			alignTopLeft(buttons);
			recordSong = new JButton("record");
			stopSong = new JButton("stop");
			setState();
			recordSong.addActionListener(new ActionListener(){
				public void actionPerformed(ActionEvent a){
					final String fileTxt = fileSave.getText().trim();
					if (fileTxt.isEmpty()){
						status.setText("Error");
						frame.pack();
						return;
					}
					status.setText("");
					frame.pack();
					new Thread(new Runnable(){
						public void run(){
							try {
								recordSong.setEnabled(false);
								stopSong.setEnabled(true);
								currentLine = (TargetDataLine)AudioSystem.getLine(currentInfo);
								currentLine.open(currentFormat);
								currentLine.start();
								// start capturing
								AudioInputStream ais = new AudioInputStream(currentLine);
								// start recording
								AudioSystem.write(ais, fileType, new File(fileTxt));
							} catch (Exception e) {
								SwingUtilities.invokeLater(new Runnable(){
									public void run(){
										currentLine = null;
										setState();
										status.setText("Error");
										frame.pack();
									}
								});
							}
						}
					}).start();
				}
			});
			stopSong.addActionListener(new ActionListener(){
				public void actionPerformed(ActionEvent a){
					currentLine.stop();
					currentLine.close();
					currentLine = null;
					setState();
					status.setText("");
					frame.pack();
				}
			});
			buttons.add(recordSong);
			buttons.add(stopSong);
			container.add(group);
			container.add(buttons);
			alignTopLeft(status);
			container.add(status);
			frame.setContentPane(container);
			frame.pack();
			frame.setVisible(true);
			frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		}
		void setState(){
			recordSong.setEnabled(okRecord());
			stopSong.setEnabled(okStop());
		}
		boolean okRecord(){
			AudioFormat format = new AudioFormat(rate.getValue(), size.getValue(),
                                             channel.getValue(), signed.isSelected(), bigEndian.isSelected());
			DataLine.Info info = new DataLine.Info(TargetDataLine.class, format);
			if (!AudioSystem.isLineSupported(info)) {
				return false;
			}
			if (currentLine != null && currentLine.isActive()){
				return false;
			}
			currentInfo = info;
			currentFormat = format;
			return true;
		}
		boolean okStop(){
			if (currentLine == null) {
				return false;
			}
			return currentLine.isActive();
		}
	}
	static void alignAddedTopLeft(JComponent par,JComponent compo){
		alignTopLeft(compo);
		par.add(compo);
	}
	static void alignTopLeft(JComponent compo){
		compo.setAlignmentX(Component.LEFT_ALIGNMENT);
		compo.setAlignmentY(Component.TOP_ALIGNMENT);
	}
    int launch(String[] args){
         AudioFormat format = getAudioFormat();
         DataLine.Info info = new DataLine.Info(TargetDataLine.class, format);
            // checks if system supports the data line
         if (!AudioSystem.isLineSupported(info)) {
                System.out.println("Line not supported");
                return -1;
         }
        // creates a new thread that waits for a specified
        // of time before stopping
        Thread stopper = new Thread(new WaitForEnd(this));
 
        stopper.start();
 
        // start recording
        return startRecord(args[0],format,info);
    }
    static Mixer.Info[] mixers()throws Exception {
		
		Mixer.Info[] mixerInfos = AudioSystem.getMixerInfo();
		 for (Mixer.Info info: mixerInfos){
			  Mixer m = AudioSystem.getMixer(info);
			  Line.Info[] lineInfos = m.getSourceLineInfo();
			  for (Line.Info lineInfo:lineInfos){
				   System.out.println (info.getName()+"-<=--"+lineInfo+":"+AudioSystem.isLineSupported(lineInfo));
				   Line line = m.getLine(lineInfo);
				   System.out.println("\t---<=--"+line);
			  }
			  lineInfos = m.getTargetLineInfo();
			  for (Line.Info lineInfo:lineInfos){
				   System.out.println (m+"-=>--"+lineInfo+":"+AudioSystem.isLineSupported(lineInfo));
				   Line line = m.getLine(lineInfo);
				   System.out.println("\t--=>---"+line);

			  }

		 }
		 AudioFormat format = new AudioFormat(8000.0f, 16, 1, true, true);
		TargetDataLine microphone = AudioSystem.getTargetDataLine(format);
		System.out.println("\t----%%%-"+microphone);
			return mixerInfos;
	}
}

class WaitForEnd implements Runnable {
    private final CustSoundRecorder recorder;
    WaitForEnd(CustSoundRecorder recorder){
        this.recorder = recorder;
    }
    public void run() {
        try {
            Thread.sleep(CustSoundRecorder.RECORD_TIME);
        } catch (InterruptedException ex) {
            Thread.currentThread().interrupt();
        }
        recorder.finish();
    }
}