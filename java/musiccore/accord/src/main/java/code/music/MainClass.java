package code.music;

import code.music.core.AbstractMusicFactory;
import code.music.core.MetaNote;
import code.music.enums.Gamme;
import code.music.impl.EvolvedNote;
import code.music.impl.MusicFactory;
import jm.music.data.CPhrase;
import jm.music.data.Note;
import jm.music.data.Part;
import jm.music.data.Phrase;
import jm.util.Play;

public class MainClass {

	public static void main(String...args){
		Part p = new Part();
		CPhrase cp = new CPhrase();
		MetaNote note1 = new MetaNote();
		note1.setDiese(false);
		note1.setValue(Gamme.SOL);
		note1.setDurationNum(2);
		note1.setDurationDen(1);
		note1.setLevel(2);
		MetaNote note2 = new MetaNote();
		note2.setDiese(false);
		note2.setValue(Gamme.SI);
		note2.setDurationNum(4);
		note2.setDurationDen(1);
		note2.setLevel(3);
		MetaNote note3 = new MetaNote();
		note3.setDiese(false);
		note3.setValue(Gamme.RE);
		note3.setDurationNum(3);
		note3.setDurationDen(1);
		note3.setLevel(4);
		AbstractMusicFactory factory = new MusicFactory();
		cp.addChord(new Note[]{
				((EvolvedNote)factory.newNote(note1,factory.infos())).getNote(),
		        ((EvolvedNote)factory.newNote(note2,factory.infos())).getNote(),
		        ((EvolvedNote)factory.newNote(note3,factory.infos())).getNote()

		});
		p.addCPhrase(cp);
		MetaNote note4 = new MetaNote();
		note4.setDiese(false);
		note4.setValue(Gamme.SI);
		note4.setDurationNum(3);
		note4.setDurationDen(1);
		note4.setLevel(5);
		Phrase phrase = new Phrase();
		phrase.setNumerator(4);
		phrase.setDenominator(4);
		phrase.add(((EvolvedNote)factory.newNote(note4,factory.infos())).getNote());
		p.add(phrase);
		Play.midi(p);
	}
}