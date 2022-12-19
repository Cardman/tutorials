package code.music;

import code.music.core.*;
import code.music.enums.Gamme;
import code.music.impl.EvolvedNote;
import code.music.impl.EvolvedPhrase;
import code.music.impl.EvolvedScore;
import code.music.impl.MusicFactory;
import code.music.sml.BuildingScore;
import code.util.CustList;
import code.util.IdMap;
import jm.JMC;
import jm.audio.Instrument;
import jm.audio.io.SampleOut;
import jm.audio.synth.Envelope;
import jm.audio.synth.Oscillator;
import jm.audio.synth.StereoPan;
import jm.audio.synth.Volume;
import jm.util.Read;
import jm.util.View;
import jm.util.Write;

import java.io.File;

public class MainClass {

	public static final class SineInst extends Instrument {
		private int channels;
		private int sampleRate;
		private float frequency;
		private double[] envPoints;
		private SampleOut sout;

		public SineInst() {
			this(44100, 2);
		}

		public SineInst(int sampleRate) {
			this(sampleRate, 2);
		}

		public SineInst(int sampleRate, int channels) {
			this(sampleRate, channels, new double[]{0.0D, 0.0D, 0.15D, 1.0D, 0.3D, 0.5D, 1.0D, 0.0D});
		}

		public SineInst(int sampleRate, int channels, double[] points) {
			this(sampleRate, channels, points, -1.0F);
		}

		public SineInst(int sampleRate, int channels, double[] points, float frequency) {
			this.frequency = -1.0F;
			this.sampleRate = sampleRate;
			this.channels = channels;
			this.frequency = frequency;
			this.envPoints = points;
		}

		public void setFrequency(float freq) {
			this.frequency = freq;
		}

		public void setEnvPoints(double[] newValues) {
			this.envPoints = newValues;
		}

		public void createChain() {
			Oscillator osc = new Oscillator(this, 0, this.sampleRate, this.channels);
			if (this.frequency != -1.0F) {
				osc.setChoice(0);
				osc.setFrq(this.frequency);
			}

			Envelope env = new Envelope(osc, this.envPoints);
			Volume vol = new Volume(env);
			StereoPan span = new StereoPan(vol);
			if (this.output == 0) {
				this.sout = new SampleOut(span);
			}

		}
	}
	public static void main(String...args)throws Exception {
		if (false){
		// 2 ** 1.0/12 1.0594630943592891448630189411239
		float[] audio2 = Read.audio("C:\\Users\\fdesr\\Music\\test2.wav");
		double o = 261.0;//440.0;
		double n = 440.0;//261.0;
		double rt = n / o;
		double qrt = Math.pow(rt, 0.3333333);
		rt = 1.1;
		float[] nd = new float[(int) (audio2.length / rt) + 1];
		int counter = 0;
		for (double i = 0.0; i < audio2.length; i += rt) {
			nd[counter++] = audio2[(int) i];
		}
		Write.audio(nd, "C:\\Users\\fdesr\\Music\\test4.wav", 2, 44100, 16);
	}
		{
			for (File f: new File("C:\\Users\\fdesr\\_git\\_tmp\\sounds").listFiles()) {
				if (f.isDirectory())continue;
				float[] audio = Read.audio(f.getAbsolutePath());
				//double o = 261.0;//440.0;
				//double n = 440.0;//261.0;
				double rt = 1.0594630943592891448630189411239;
				float[] nd = new float[(int) (audio.length / rt) + 1];
				int counter = 0;
				for (double i = 0.0; i < audio.length; i += rt) {
					nd[counter++] = audio[(int) i];
				}
				Write.audio(nd,f.getAbsolutePath().replace("\\sounds\\","\\sounds2\\"));
			}
		}
		//
		System.exit(0);
		for (File f: new File("C:\\Users\\fdesr\\_git\\_tmp\\sounds").listFiles()) {
			if (f.isDirectory())continue;
			float[] audio = Read.audio(f.getAbsolutePath());
			float[] r = new float[audio.length];
			for (int i = 0; i < audio.length; i++) {
				if (i % 2 == 0) {
					r[i] = audio[i];
				} else  {
					r[i] = audio[i]*2;
				}
			}
			Write.audio(r,f.getAbsolutePath().replace("\\sounds\\","\\sounds2\\"));
		}
		System.exit(0);
		IdMap<Gamme, Integer> infos = new MusicFactory().infos();
		CustList<MetaNote> ns = new CustList<MetaNote>();
		Instrument ins = new SineInst();
		for (int l = 2; l < 6; l++) {
			MetaNote note = new MetaNote();
			note.setDiese(false);
			note.setValue(Gamme.DO);
			note.setDurationNum(1);
			note.setDurationDen(1);
			note.setLevel(l);
			ns.add(note);
			//Write.midi(new EvolvedNote(note).getNote(),note.pitch(infos)+".wav");
			note = new MetaNote();
			note.setDiese(true);
			note.setValue(Gamme.DO);
			note.setDurationNum(1);
			note.setDurationDen(1);
			note.setLevel(l);
			ns.add(note);
			//Write.midi(new EvolvedNote(note).getNote(),note.pitch(infos)+".wav");
			note = new MetaNote();
			note.setDiese(false);
			note.setValue(Gamme.RE);
			note.setDurationNum(1);
			note.setDurationDen(1);
			note.setLevel(l);
			ns.add(note);
			//Write.midi(new EvolvedNote(note).getNote(),note.pitch(infos)+".wav");
			note = new MetaNote();
			note.setDiese(true);
			note.setValue(Gamme.RE);
			note.setDurationNum(1);
			note.setDurationDen(1);
			note.setLevel(l);
			ns.add(note);
			//Write.midi(new EvolvedNote(note).getNote(),note.pitch(infos)+".wav");
			note = new MetaNote();
			note.setDiese(false);
			note.setValue(Gamme.MI);
			note.setDurationNum(1);
			note.setDurationDen(1);
			note.setLevel(l);
			ns.add(note);
			//Write.midi(new EvolvedNote(note).getNote(),note.pitch(infos)+".wav");
			note = new MetaNote();
			note.setDiese(false);
			note.setValue(Gamme.FA);
			note.setDurationNum(1);
			note.setDurationDen(1);
			note.setLevel(l);
			ns.add(note);
			//Write.midi(new EvolvedNote(note).getNote(),note.pitch(infos)+".wav");
			note = new MetaNote();
			note.setDiese(true);
			note.setValue(Gamme.FA);
			note.setDurationNum(1);
			note.setDurationDen(1);
			note.setLevel(l);
			ns.add(note);
			//Write.midi(new EvolvedNote(note).getNote(),note.pitch(infos)+".wav");
			note = new MetaNote();
			note.setDiese(false);
			note.setValue(Gamme.SOL);
			note.setDurationNum(1);
			note.setDurationDen(1);
			note.setLevel(l);
			ns.add(note);
			//Write.midi(new EvolvedNote(note).getNote(),note.pitch(infos)+".wav");
			note = new MetaNote();
			note.setDiese(true);
			note.setValue(Gamme.SOL);
			note.setDurationNum(1);
			note.setDurationDen(1);
			note.setLevel(l);
			ns.add(note);
			//Write.midi(new EvolvedNote(note).getNote(),note.pitch(infos)+".wav");
			note = new MetaNote();
			note.setDiese(false);
			note.setValue(Gamme.LA);
			note.setDurationNum(1);
			note.setDurationDen(1);
			note.setLevel(l);
			ns.add(note);
			//Write.midi(new EvolvedNote(note).getNote(),note.pitch(infos)+".wav");
			note = new MetaNote();
			note.setDiese(true);
			note.setValue(Gamme.LA);
			note.setDurationNum(1);
			note.setDurationDen(1);
			note.setLevel(l);
			ns.add(note);
			//Write.midi(new EvolvedNote(note).getNote(),note.pitch(infos)+".wav");
			note = new MetaNote();
			note.setDiese(false);
			note.setValue(Gamme.SI);
			note.setDurationNum(1);
			note.setDurationDen(1);
			note.setLevel(l);
			ns.add(note);
			//Write.midi(new EvolvedNote(note).getNote(),note.pitch(infos)+".wav");
		}
		{
			MetaNote note = new MetaNote();
			note.setDiese(false);
			note.setValue(Gamme.DO);
			note.setDurationNum(1);
			note.setDurationDen(1);
			note.setLevel(6);
			ns.add(note);

			//Write.midi(new EvolvedNote(note).getNote(),note.pitch(infos)+".wav");
			for (MetaNote m: ns) {
				MetaPhrase phrase = new MetaPhrase();
				phrase.getNotes().add(m);
				Write.au(new EvolvedPhrase(phrase).getPhrase(),m.pitch(infos)+".wav",ins);
			}
		}
		System.exit(0);
		MetaPhrase phrase = new MetaPhrase();
		MetaNote note = new MetaNote();
		note.setDiese(false);
		note.setValue(Gamme.DO);
		note.setDurationNum(1);
		note.setDurationDen(1);
		int level = 5;
		note.setLevel(level);
		phrase.getNotes().add(note);
		note = new MetaNote();
		note.setDiese(true);
		note.setValue(Gamme.DO);
		note.setDurationNum(1);
		note.setDurationDen(1);
		note.setLevel(level);
		phrase.getNotes().add(note);
		note = new MetaNote();
		note.setDiese(false);
		note.setValue(Gamme.RE);
		note.setDurationNum(1);
		note.setDurationDen(1);
		note.setLevel(level);
		phrase.getNotes().add(note);
		note = new MetaNote();
		note.setDiese(true);
		note.setValue(Gamme.RE);
		note.setDurationNum(1);
		note.setDurationDen(1);
		note.setLevel(level);
		phrase.getNotes().add(note);
		note = new MetaNote();
		note.setDiese(false);
		note.setValue(Gamme.MI);
		note.setDurationNum(1);
		note.setDurationDen(1);
		note.setLevel(level);
		phrase.getNotes().add(note);
		note = new MetaNote();
		note.setPause(true);
		note.setDurationNum(1);
		note.setDurationDen(1);
		note.setLevel(level);
		phrase.getNotes().add(note);
		note = new MetaNote();
		note.setDiese(false);
		note.setValue(Gamme.FA);
		note.setDurationNum(1);
		note.setDurationDen(1);
		note.setLevel(level);
		phrase.getNotes().add(note);
		note = new MetaNote();
		note.setDiese(true);
		note.setValue(Gamme.FA);
		note.setDurationNum(1);
		note.setDurationDen(1);
		note.setLevel(level);
		phrase.getNotes().add(note);
		note = new MetaNote();
		note.setDiese(false);
		note.setValue(Gamme.SOL);
		note.setDurationNum(1);
		note.setDurationDen(1);
		note.setLevel(level);
		phrase.getNotes().add(note);
		note = new MetaNote();
		note.setDiese(true);
		note.setValue(Gamme.SOL);
		note.setDurationNum(1);
		note.setDurationDen(1);
		note.setLevel(level);
		phrase.getNotes().add(note);
		note = new MetaNote();
		note.setDiese(false);
		note.setValue(Gamme.LA);
		note.setDurationNum(1);
		note.setDurationDen(1);
		note.setLevel(level);
		phrase.getNotes().add(note);
		note = new MetaNote();
		note.setDiese(true);
		note.setValue(Gamme.LA);
		note.setDurationNum(1);
		note.setDurationDen(1);
		note.setLevel(level);
		phrase.getNotes().add(note);
		note = new MetaNote();
		note.setDiese(false);
		note.setValue(Gamme.SI);
		note.setDurationNum(1);
		note.setDurationDen(1);
		note.setLevel(level);
		phrase.getNotes().add(note);
		note = new MetaNote();
		note.setDiese(false);
		note.setValue(Gamme.DO);
		note.setDurationNum(1);
		note.setDurationDen(1);
		note.setLevel(level+1);
		phrase.getNotes().add(note);
		MetaPart part = new MetaPart();
		part.setInstrument(JMC.PIANO);
		part.getPhrases().add(phrase);
		MetaScore score = new MetaScore();
		score.getParts().add(part);
		AbstractMusicFactory factory = new MusicFactory();
		AbstractScore sc = BuildingScore.build(score, factory);
		//sc.play();
		Thread th = new Thread(new PlayingScore(sc));
		th.start();
		th.join();
		//View.notate(((EvolvedScore)sc).getScore());
	}
	static class PlayingScore implements Runnable{
		private AbstractScore sc;
		public PlayingScore(AbstractScore sc){
			this.sc=sc;
		}
		public void run(){
			sc.play();
		}
	}
}