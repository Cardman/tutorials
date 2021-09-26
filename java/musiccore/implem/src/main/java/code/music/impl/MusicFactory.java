package code.music.impl;

import code.music.core.*;
import code.music.enums.Gamme;
import code.util.IdMap;
import jm.constants.Pitches;

public final class MusicFactory implements AbstractMusicFactory {
    public IdMap<Gamme, Integer> infos() {
        IdMap<Gamme, Integer> gamme_ = new IdMap<Gamme, Integer>();
        gamme_.addEntry(Gamme.DO, Pitches.C0);
        gamme_.addEntry(Gamme.RE, Pitches.D0);
        gamme_.addEntry(Gamme.MI, Pitches.E0);
        gamme_.addEntry(Gamme.FA, Pitches.F0);
        gamme_.addEntry(Gamme.SOL, Pitches.G0);
        gamme_.addEntry(Gamme.LA, Pitches.A0);
        gamme_.addEntry(Gamme.SI, Pitches.B0);
        return gamme_;
    }

    public AbstractNote newNote(MetaNote _from, IdMap<Gamme, Integer> _tr) {
        return new EvolvedNote(_from,_tr);
    }

    public AbstractPhrase newPhrase(MetaPhrase _from) {
        return new EvolvedPhrase(_from);
    }

    public AbstractPart newPart(MetaPart _from) {
        return new EvolvedPart(_from);
    }

    public AbstractScore newScore(MetaScore _from) {
        return new EvolvedScore(_from);
    }
}
