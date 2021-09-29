package code.music.core;

import code.music.enums.Gamme;
import code.util.IdMap;

public interface AbstractPhrase {
    void add(MetaNote _e, IdMap<Gamme, Integer> _tr);
    void add(MetaNote _e);
}
