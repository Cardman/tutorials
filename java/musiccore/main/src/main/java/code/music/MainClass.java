package code.music;

import code.music.core.*;
import code.music.enums.Gamme;
import code.music.impl.EvolvedScore;
import code.music.impl.MusicFactory;
import code.music.sml.BuildingScore;
import jm.util.View;

public class MainClass {

	public static void main(String...args)throws Exception{
		MetaPhrase phrase = new MetaPhrase();
		MetaNote note = new MetaNote();
		note.setDiese(false);
		note.setValue(Gamme.DO);
		note.setDurationNum(1);
		note.setDurationDen(1);
		phrase.getNotes().add(note);
		note = new MetaNote();
		note.setDiese(true);
		note.setValue(Gamme.DO);
		note.setDurationNum(1);
		note.setDurationDen(1);
		phrase.getNotes().add(note);
		note = new MetaNote();
		note.setDiese(false);
		note.setValue(Gamme.RE);
		note.setDurationNum(1);
		note.setDurationDen(1);
		phrase.getNotes().add(note);
		note = new MetaNote();
		note.setDiese(true);
		note.setValue(Gamme.RE);
		note.setDurationNum(1);
		note.setDurationDen(1);
		phrase.getNotes().add(note);
		note = new MetaNote();
		note.setDiese(false);
		note.setValue(Gamme.MI);
		note.setDurationNum(1);
		note.setDurationDen(1);
		phrase.getNotes().add(note);
		note = new MetaNote();
		note.setPause(true);
		note.setDurationNum(1);
		note.setDurationDen(1);
		phrase.getNotes().add(note);
		note = new MetaNote();
		note.setDiese(false);
		note.setValue(Gamme.FA);
		note.setDurationNum(1);
		note.setDurationDen(1);
		phrase.getNotes().add(note);
		note = new MetaNote();
		note.setDiese(true);
		note.setValue(Gamme.FA);
		note.setDurationNum(1);
		note.setDurationDen(1);
		phrase.getNotes().add(note);
		note = new MetaNote();
		note.setDiese(false);
		note.setValue(Gamme.SOL);
		note.setDurationNum(1);
		note.setDurationDen(1);
		phrase.getNotes().add(note);
		note = new MetaNote();
		note.setDiese(true);
		note.setValue(Gamme.SOL);
		note.setDurationNum(1);
		note.setDurationDen(1);
		phrase.getNotes().add(note);
		note = new MetaNote();
		note.setDiese(false);
		note.setValue(Gamme.LA);
		note.setDurationNum(1);
		note.setDurationDen(1);
		phrase.getNotes().add(note);
		note = new MetaNote();
		note.setDiese(true);
		note.setValue(Gamme.LA);
		note.setDurationNum(1);
		note.setDurationDen(1);
		phrase.getNotes().add(note);
		note = new MetaNote();
		note.setDiese(false);
		note.setValue(Gamme.SI);
		note.setDurationNum(1);
		note.setDurationDen(1);
		phrase.getNotes().add(note);
		MetaPart part = new MetaPart();
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