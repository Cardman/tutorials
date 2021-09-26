package code.music.impl;

import code.music.core.*;
import jm.music.data.Score;
import jm.util.Play;

public final class EvolvedScore implements AbstractScore {

    private final Score score;

    public EvolvedScore(MetaScore _score) {
        score = new Score(_score.getName());
    }
    public void add(AbstractPart _e) {
        score.add(((EvolvedPart)_e).getPart());
    }

    public void play() {
        Play.midi(score);
    }
    public Score getScore() {
        return score;
    }
}
