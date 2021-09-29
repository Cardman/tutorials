package code.music.sml;

import code.music.core.*;
import code.music.enums.Gamme;
import code.util.IdMap;

public final class BuildingScore {
    private BuildingScore() {
    }
    public static AbstractScore build(MetaScore _score, AbstractMusicFactory _fact) {
        IdMap<Gamme, Integer> infos_ = _fact.infos();
        AbstractScore score_ = _fact.newScore(_score);
        for (MetaPart p:_score.getParts()) {
            AbstractPart part_ = _fact.newPart(p);
            for (MetaPhrase h: p.getPhrases()) {
                AbstractPhrase phrase_ = _fact.newPhrase(h);
                for (MetaNote n: h.getNotes()) {
                    if (n.isPause()) {
                        phrase_.add(n);
                    } else {
                        phrase_.add(n, infos_);
                    }
                }
                part_.add(phrase_);
            }
            score_.add(part_);
        }
        return score_;
    }
}
