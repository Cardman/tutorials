package code.music.impl;

import code.music.core.AbstractPhrase;
import code.music.core.MetaNote;
import code.music.core.MetaPhrase;
import code.music.enums.Gamme;
import code.util.IdMap;
import jm.music.data.Phrase;

public final class EvolvedPhrase implements AbstractPhrase {

    private final Phrase phrase;

    public EvolvedPhrase(MetaPhrase _phrase) {
        phrase = new Phrase();
        phrase.setNumerator(_phrase.getNumerator());
        phrase.setDenominator(_phrase.getDenominator());
    }
    public void add(MetaNote _e, IdMap<Gamme, Integer> _tr) {
        phrase.add(new EvolvedNote(_e,_tr).getNote());
    }

    public void add(MetaNote _e) {
        phrase.add(new EvolvedNote(_e).getNote());
    }

    public Phrase getPhrase() {
        return phrase;
    }
}
