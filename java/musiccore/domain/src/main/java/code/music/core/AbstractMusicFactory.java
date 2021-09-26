package code.music.core;

import code.music.enums.Gamme;
import code.util.IdMap;

public interface AbstractMusicFactory {
    IdMap<Gamme,Integer> infos();
    AbstractNote newNote(MetaNote _from, IdMap<Gamme,Integer> _tr);
    AbstractPhrase newPhrase(MetaPhrase _from);
    AbstractPart newPart(MetaPart _from);
    AbstractScore newScore(MetaScore _from);

}
