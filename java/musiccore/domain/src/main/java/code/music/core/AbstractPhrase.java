package code.music.core;

import code.music.enums.Gamme;
import code.util.IdMap;

public interface AbstractPhrase {
    void add(AbstractMusicFactory _fact, MetaNote _e, IdMap<Gamme,Integer> _tr);
}
